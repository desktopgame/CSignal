#include "class_impl.h"
#include "../../util/text.h"
#include "../parameter.h"
#include "../../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../util/mem.h"
#include "../object.h"
#include "../../vm/enviroment.h"
#include "../../vm/frame.h"
#include "../../util/text.h"
#include "../field.h"
#include "../property.h"
#include "../method.h"
#include "../constructor.h"
#include "../TYPE_IMPL.h"
#include "../../env/vtable.h"
#include "../../env/heap.h"
#include "../../env/operator_overload.h"
#include "meta_impl.h"
#include "class_find.h"
#include "../type_parameter.h"
#include "../generic_type.h"
#include "../generic_type.h"
#include "../operator_overload.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static void CreateVTableClass_top(class_* self);
static void CreateVTableClass_override(class_* self);
static void CreateVTableClass_interface(class_* self);
static void class_impl_delete(VectorItem item);
static void class_DeleteField(VectorItem item);
static void class_DeleteMethod(VectorItem item);
static void class_ctor_delete(VectorItem item);
static void class_DeleteNativeMethodRef(NumericMapKey key, NumericMapItem item);
static Method* class_find_impl_method(class_* self, Method* virtualMethod);
static void class_VTable_vec_delete(VectorItem item);
static void class_DeleteTypeParameter(VectorItem item);
static void class_generic_type_list_delete(VectorItem item);
static void DeleteClass_OperatorOverload(VectorItem item);
static void DeleteClass_Property(VectorItem item);

type * WrapClass(class_ * self) {
	type* ret = NewType();
	ret->tag = TYPE_CLASS_T;
	ret->u.class_ = self;
	self->parent = ret;
	return ret;
}

class_ * NewClass(StringView namev) {
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->namev = namev;
	ret->parent = NULL;
	ret->location = NULL;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->impl_list = NewVector();
	ret->field_list = NewVector();
	ret->sfield_list = NewVector();
	ret->prop_list = NewVector();
	ret->sprop_list = NewVector();
	ret->method_list = NewVector();
	ret->smethod_list = NewVector();
	ret->constructor_list = NewVector();
	ret->NativeMethodRef_nmap = NewNumericMap();
	ret->vt_vec = NewVector();
	ret->GetParameterListType = NewVector();
	ret->vt = NULL;
	ret->ovt = NULL;
	ret->is_abstract = false;
	ret->operator_overload_list = NewVector();
	return ret;
}

class_* NewClassProxy(generic_type* gt, StringView namev) {
	assert(gt->core_type->tag == TYPE_INTERFACE_T);
	class_* ret = NewClass(namev);
	ret->super_class = GENERIC_OBJECT;
	PushVector(ret->impl_list, gt);
	return ret;
}

type* NewPreloadClass(StringView namev) {
	class_* cl = NewClass(namev);
	type* tp = WrapClass(cl);
	tp->state = TYPE_PENDING;
	if (TYPE_OBJECT == NULL) {
		return tp;
	}
	class_* objCls = TYPE_OBJECT->u.class_;
	if (cl != objCls) {
		InitGenericSelf(objCls->parent, 0);
		cl->super_class = objCls->parent->generic_self;
	}
	return tp;
}

void AllocFieldsClass(class_ * self, object * o, Frame* fr) {
	assert(o->tag == OBJECT_REF_T);
	Heap* he = GetHeap();
	for (int i = 0; i < self->field_list->Length; i++) {
		Field* f = (Field*)AtVector(self->field_list, i);
		object* a = GetDefaultObject(f->gtype);
		//静的フィールドは別の場所に確保
		if (IsStaticModifier(f->modifier)) {
			continue;
		}
		he->CollectBlocking++;
		if(f->initial_value != NULL) {
			Frame* sub = SubFrame(fr);
			for(int i=0; i<fr->TypeArgs->Length; i++) {
				PushVector(sub->TypeArgs, AtVector(fr->TypeArgs, i));
			}
			sub->Receiver = self->parent;
			CopyVector(fr->VariableTable, sub->VariableTable);
			ExecuteVM(sub, f->initial_value_env);
			a = PopVector(sub->ValueStack);
			DeleteFrame(sub);
		}
		PushVector(o->u.field_vec, a);
		he->CollectBlocking--;
	}
}

void FreeClassFields(class_ * self, object * o) {
}

void AddFieldClass(class_ * self, Field* f) {
	assert(f != NULL);
	if (IsStaticModifier(f->modifier)) {
		PushVector(self->sfield_list, f);
	} else {
		PushVector(self->field_list, f);
	}
}

void AddPropertyClass(class_* self, Property* p) {
	if (IsStaticModifier(p->Modifier)) {
		PushVector(self->sprop_list, p);
	} else {
		PushVector(self->prop_list, p);
	}
	//プロパティが単純な省略形として記述されているなら、
	//それはフィールドと同じなのでフィールドも定義する
	#if defined(DEBUG)
	const char* name = Ref2Str(p->Name);
	#endif
	if(p->IsShort) {
		Field* f = NewField(ConcatIntern("$propery.", p->Name));
		f->access = ACCESS_PRIVATE_T;
		f->gtype = p->GType;
		f->modifier = p->Modifier;
		f->parent = self->parent;
		f->static_value = GetNullObject();
		p->SourceRef = f;
		AddFieldClass(self, f);
	}
}

void AddMethodClass(class_ * self, Method * m) {
	assert(m != NULL);
	if (IsStaticModifier(m->Modifier)) {
		PushVector(self->smethod_list, m);
	} else {
		PushVector(self->method_list, m);
	}
}

void AddConstructorClass(class_ * self, Constructor* c) {
	PushVector(self->constructor_list, c);
}

void DefineNativeMethodClass(class_* self, const char* name, NativeImpl impl) {
	DefineNativeMethodByRefClass(self, InternString(name), impl);
}

void DefineNativeMethodByRefClass(class_ * self, StringView namev, NativeImpl impl) {
	NativeMethodRef* ref = NewNativeMethodRef(impl);
	PutNumericMap(self->NativeMethodRef_nmap, namev, ref);
}

int DistanceClass(class_ * super, class_ * sub) {
	if (super == sub) {
		return 0;
	}
	int depth = 0;
	class_* pointee = sub;
	do {
		if (pointee == super) {
			return depth;
		}
		generic_type* super_gtype = pointee->super_class;
		if(super_gtype == NULL) {
			depth = -1;
			break;
		}
		pointee = super_gtype->core_type->u.class_;
		depth++;
		if (pointee == NULL) {
			depth = -1;
			break;
		}
	} while (1);
	return depth;
}

void CreateVTableClass(class_ * self) {
	//TEST(!strcmp(self->name, "Int"));
	#if defined(DEBUG)
	const char* str = Ref2Str(self->namev);
	#endif
	assert(self != NULL);
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	self->vt = NewVTable();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->super_class == NULL) {
		CreateVTableClass_top(self);
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		CreateVTableClass_override(self);
	}
	CreateVTableClass_interface(self);
	assert(self->vt->Elements->Length != 0);
}

void CreateOperatorVTClass(class_* self) {
	if(self->ovt != NULL) {
		return;
	}
	if(self->super_class != NULL) {
		CreateOperatorVTClass(TYPE2CLASS(GENERIC2TYPE(self->super_class)));
	}
	self->ovt = NewOperatorVt();
	if(self->super_class == NULL) {
		for(int i=0; i<self->operator_overload_list->Length; i++) {
			OperatorOverload* opov = AtVector(self->operator_overload_list, i);
			PushVector(self->ovt->vec, opov);
		}
	} else {
		OperatorVT* super_vt = TYPE2CLASS(GENERIC2TYPE(self->super_class))->ovt;
		for(int i=0; i<super_vt->vec->Length; i++) {
			OperatorOverload* opov = AtVector(super_vt->vec, i);
			PushVector(self->ovt->vec, opov);
		}
		for(int i=0; i<self->operator_overload_list->Length; i++) {
			OperatorOverload* opov = AtVector(self->operator_overload_list, i);
			ReplaceOperatorVt(self->ovt, opov);
		}
	}
}

int CountAllFieldClass(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->field_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int CountAllSFieldClass(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sfield_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int CountAllPropertyClass(class_* self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->prop_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int CountAllSPropertyClass(class_* self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sprop_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int CountAllMethodClass(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->method_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int CountAllSMethodClass(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->smethod_list->Length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

object * NewInstanceClass(class_* self, Frame* fr, Vector* args, Vector* type_args) {
	//コンストラクタを検索
	int temp = 0;
	Constructor* ctor = RFindConstructorClass(self, args, NULL, fr, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	Frame* sub = SubFrame(fr);
	Heap* h = GetHeap();
	if(args != NULL) {
		for (int i = args->Length-1; i>=0; i--) {
			object* o = AtVector(args, i);
			PushVector(sub->ValueStack, o);
		}
	}
	if(type_args != NULL) {
		for(int i = 0; i<type_args->Length; i++) {
			PushVector(sub->TypeArgs, AtVector(type_args, i));
		}
	}
	ExecuteVM(sub, ctor->Env);
	object* inst = PopVector(sub->ValueStack);
	h->CollectBlocking++;
	DeleteFrame(sub);
	h->CollectBlocking--;
	return inst;
}

void LinkAllClass(class_ * self) {
	for (int i = 0; i < self->field_list->Length; i++) {
		Field* f = (Field*)AtVector(self->field_list, i);
		f->parent = self->parent;
	}
	for (int i = 0; i < self->method_list->Length; i++) {
		Method* m = (Method*)AtVector(self->method_list, i);
		m->Parent = self->parent;
	}
	for (int i = 0; i < self->constructor_list->Length; i++) {
		Constructor* ctor = (Constructor*)AtVector(self->constructor_list, i);
		ctor->Parent = self->parent;
	}
}

void UnlinkClass(class_ * self) {
	if (self->super_class != NULL) {
		self->super_class->core_type->u.class_->ref_count--;
	}
	//XSTREQ(self->name, "Object");
	//generic_DeleteType(self->super_class);
	DeleteNumericMap(self->NativeMethodRef_nmap, class_DeleteNativeMethodRef);
	DeleteVector(self->impl_list, class_impl_delete);
	DeleteVector(self->field_list, class_DeleteField);
	DeleteVector(self->sfield_list, class_DeleteField);
	DeleteVector(self->method_list, class_DeleteMethod);
	DeleteVector(self->smethod_list, class_DeleteMethod);
	DeleteVector(self->constructor_list, class_ctor_delete);
	DeleteVector(self->operator_overload_list, DeleteClass_OperatorOverload);
	DeleteVector(self->prop_list, DeleteClass_Property);
	DeleteVector(self->sprop_list, DeleteClass_Property);
	DeleteVTable(self->vt);
	DeleteOperatorVt(self->ovt);
	DeleteVector(self->vt_vec, class_VTable_vec_delete);
}

void DeleteClass(class_ * self) {
//	printf("unlink %s\n", Ref2Str(self->namev));
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	//printf("delete %s\n", self->name);
	DeleteVector(self->GetParameterListType, class_DeleteTypeParameter);
	MEM_FREE(self);
}

//private
static void CreateVTableClass_top(class_* self) {
	for (int i = 0; i < self->method_list->Length; i++) {
		Method* m = (Method*)AtVector(self->method_list, i);
		if(m->Access != ACCESS_PRIVATE_T &&
		   !IsStaticModifier(m->Modifier)) {
			AddVTable(self->vt, m);
		}
	}
}

static void CreateVTableClass_override(class_* self) {
	#if defined(DEBUG)
	const char* clname = Ref2Str(self->namev);
	#endif
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = self->parent->location;
	cctx->Ty = self->super_class->core_type;
	CreateVTableClass(self->super_class->core_type->u.class_);
	CopyVTable(self->super_class->core_type->u.class_->vt, self->vt);
	for (int i = 0; i < self->method_list->Length; i++) {
		Method* m = (Method*)AtVector(self->method_list, i);
		if(m->Access != ACCESS_PRIVATE_T &&
		   !IsStaticModifier(m->Modifier)) {
			ReplaceVTable(self->vt, m, cctx);
		}
	}
	DeleteCallContext(cctx);
}

static void CreateVTableClass_interface(class_* self) {
	#if defined(DEBUG) || defined(_DEBUG)
	const char* clname = Ref2Str(GetTypeName(self->parent));
	#endif
	Vector* tbl = GetInterfaceTreeClass(self);
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < tbl->Length; i++) {
		//generic_type* gtp = (generic_type*)AtVector(tbl, i);
		interface_* inter = (interface_*)AtVector(tbl, i);
		VTable* interVT = inter->vt;
		VTable* newVT = NewVTable();
		assert(interVT != NULL);
		//そのインターフェースに定義されたテーブルの一覧
		//これはスーパーインターフェースも含む。
		for (int j = 0; j < interVT->Elements->Length; j++) {
			//実装クラスの中の、
			//シグネチャが同じメソッドをテーブルへ。
			Method* interVTM = AtVector(interVT->Elements, j);
			Method* classVTM = class_find_impl_method(self, interVTM);
			if(!self->is_abstract && classVTM == NULL) {
				PushVector(self->vt_vec, newVT);
				ThrowBCError(BCERROR_NOT_IMPLEMENT_INTERFACE_T,
					Ref2Str(GetTypeName(interVTM->Parent)),
					Ref2Str(interVTM->Name)
				);
				DeleteVector(tbl, VectorDeleterOfNull);
				return;
			}
			//assert(self->is_abstract || classVTM != NULL);
			//例えば抽象クラスがインターフェイスを実装していない場合
			//空っぽの実装を持たせる
			if(self->is_abstract && classVTM == NULL) {
				classVTM = interVTM;
			}
			AddVTable(newVT, classVTM);
		}
		PushVector(self->vt_vec, newVT);
	}
	DeleteVector(tbl, VectorDeleterOfNull);
}

static void class_impl_delete(VectorItem item) {
	generic_type* e = (generic_type*)item;
	//generic_DeleteType(e);
}

static void class_DeleteField(VectorItem item) {
	Field* e = (Field*)item;
	DeleteField(e);
}

static void class_DeleteMethod(VectorItem item) {
	Method* e = (Method*)item;
	DeleteMethod(e);
}

static void class_ctor_delete(VectorItem item) {
	Constructor* e = (Constructor*)item;
	DeleteConstructor(e);
}

static void class_DeleteNativeMethodRef(NumericMapKey key, NumericMapItem item) {
	NativeMethodRef* e = (NativeMethodRef*)item;
	DeleteNativeMethodRef(e);
}

static Method* class_find_impl_method(class_* self, Method* virtualMethod) {
	CallContext* cctx = NewCallContext(CALL_DECL_T);
	cctx->Scope = self->parent->location;
	cctx->Ty = self->parent;
	Method* ret = NULL;
	VTable* clVT = self->vt;
	for (int i = 0; i < clVT->Elements->Length; i++) {
		Method* clM = AtVector(clVT->Elements, i);
		if (IsOverridedMethod(virtualMethod, clM, cctx)) {
			ret = clM;
			break;
		}
	}
	DeleteCallContext(cctx);
	return ret;
}

static void class_VTable_vec_delete(VectorItem item) {
	VTable* e = (VTable*)item;
	DeleteVTable(e);
}

static void class_DeleteTypeParameter(VectorItem item) {
	TypeParameter* e = (TypeParameter*)item;
	DeleteTypeParameter(e);
}

static void class_generic_type_list_delete(VectorItem item) {
	generic_type* e = (generic_type*)item;
//	generic_DeleteType(e);
}

static void DeleteClass_OperatorOverload(VectorItem item) {
	OperatorOverload* e = (OperatorOverload*)item;
	DeleteOperatorOverload(e);
}

static void DeleteClass_Property(VectorItem item) {
	Property* e = (Property*)item;
	DeleteProperty(e);
}