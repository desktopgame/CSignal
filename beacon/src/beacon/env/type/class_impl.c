#include "class_impl.h"
#include "../../util/text.h"
#include "../../util/xassert.h"
#include "../parameter.h"
#include "../../il/il_argument.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../util/mem.h"
#include "../object.h"
#include "../../vm/enviroment.h"
#include "../../util/text.h"
#include "../field.h"
#include "../method.h"
#include "../constructor.h"
#include "../type_impl.h"
#include "../../env/vtable.h"
#include "../../env/heap.h"
#include "meta_impl.h"
#include "../type_parameter.h"
#include "../generic_type.h"
#include "../generic_type.h"

//http://jumble-note.blogspot.jp/2012/09/c-vacopy.html
#ifndef va_copy
#    define va_copy(dest, src) ((dest) = (src))
#endif

//private
static void class_create_vtable_top(class_* self);
static void class_create_vtable_ov(class_* self);
static void class_create_vtable_interface(class_* self);
static void class_impl_delete(vector_item item);
static void class_field_delete(vector_item item);
static void class_method_delete(vector_item item);
static void class_ctor_delete(vector_item item);
static void class_native_method_ref_delete(vector_item item);
static method* class_find_impl_method(class_* self, method* virtualMethod);
static void class_vtable_vec_delete(vector_item item);
static void class_type_parameter_delete(vector_item item);
static void class_generic_type_list_delete(vector_item item);

type * type_wrap_class(class_ * self) {
	type* ret = type_new();
	ret->tag = type_class;
	ret->u.class_ = self;
	self->parent = ret;
	return ret;
}

class_ * class_new(const char * name) {
	assert(name != NULL);
	class_* ret = (class_*)MEM_MALLOC(sizeof(class_));
	ret->name = text_strdup(name);
	ret->parent = NULL;
	ret->location = NULL;
	ret->state = class_none;
	ret->ref_count = 0;
	ret->super_class = NULL;
	ret->impl_list = vector_new();
	ret->field_list = vector_new();
	ret->sfield_list = vector_new();
	ret->method_list = vector_new();
	ret->smethod_list = vector_new();
	ret->constructor_list = vector_new();
	ret->native_method_ref_map = tree_map_new();
	ret->vt_vec = vector_new();
	ret->type_parameter_list = vector_new();
	//FIXME:ここで持つ必要はない
	ret->classIndex = -1;
	//ret->absoluteIndex = -1;
	ret->vt = NULL;
	return ret;
}

class_ * class_new_preload(const char * name) {
	class_* cl = class_new(name);
	cl->state = class_pending;
	if (CL_OBJECT == NULL) {
		return cl;
	}
	class_* objCls = CL_OBJECT->u.class_;
	if (cl != objCls) {
		type_init_generic(objCls->parent, 0);
		cl->super_class = objCls->parent->generic_self;
	}
	return cl;
}

void class_alloc_fields(class_ * self, object * o) {
	assert(o->tag == object_ref);
	for (int i = 0; i < self->field_list->length; i++) {
		//*
		field* f = (field*)vector_at(self->field_list, i);
		object* a = object_get_null();
		//プリミティブ型のときはデフォルト値を入れておく
		if (f->gtype == CL_INT->generic_self) {
			a = object_int_new(0);
		} else if (f->gtype == CL_DOUBLE->generic_self) {
			a = object_double_new(0.0);
		} else if (f->gtype == CL_BOOL->generic_self) {
			a = object_bool_get(false);
		} else if (f->gtype == CL_CHAR->generic_self) {
			a = object_char_new('\0');
		}
		//静的フィールドは別の場所に確保
		if (modifier_is_static(f->modifier)) {
			continue;
		}
		vector_push(o->u.field_vec, a);
		//*/
	}
	class_create_vtable(self);
	o->gtype = generic_type_ref(self->parent);
	o->vptr = self->vt;
}

void class_free_fields(class_ * self, object * o) {
}

void class_add_field(class_ * self, field * f) {
	if (modifier_is_static(f->modifier)) {
		vector_push(self->sfield_list, f);
	} else {
		vector_push(self->field_list, f);
	}
}

void class_add_method(class_ * self, method * m) {
	if (modifier_is_static(m->modifier)) {
		vector_push(self->smethod_list, m);
	} else {
		vector_push(self->method_list, m);
	}
}

void class_add_constructor(class_ * self, constructor * c) {
	vector_push(self->constructor_list, c);
}

void class_dump(class_ * self, int depth) {
	text_putindent(depth);
	text_printf("class %s", self->name);
	type_parameter_print(self->type_parameter_list);
	text_putline();
	//親クラスがあるなら表示
	if (self->super_class != NULL) {
		text_putindent(depth + 1);
		text_printf("super ");
		text_printf("%s", type_name(self->super_class->core_type));
//		generic_type_print(self->super_class->);
		text_putline();
	}
	//実装インターフェースがあるなら表示
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = (generic_type*)vector_at(self->impl_list, i);
		interface_* inter = e->core_type->u.interface_;
		text_putindent(depth + 1);
		text_printf("impl %s", inter->name);
		text_putline();
	}
	//フィールドの一覧をダンプ
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		field_dump(f, depth + 1);
	}
	//メソッドの一覧をダンプ
	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
	for (int i = 0; i < self->smethod_list->length; i++) {
		vector_item e = vector_at(self->smethod_list, i);
		method* m = (method*)e;
		method_dump(m, depth + 1);
	}
	//コンストラクタの一覧をダンプ
	for (int i = 0; i < self->constructor_list->length; i++) {
		vector_item e = vector_at(self->constructor_list, i);
		constructor* c = (constructor*)e;
		constructor_dump(c, depth + 1);
	}
}

void class_define_native_method(class_ * self, const char * name, native_impl impl) {
	native_method_ref* ref = native_method_ref_new(impl);
	tree_map_put(self->native_method_ref_map, name, ref);
}

field * class_find_field(class_* self, const char * name, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			(*outIndex) = (class_count_fieldall(self) - self->field_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, const char * name, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, name, outIndex);
		if (f != NULL) {
			return f;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

field * class_find_sfield(class_ * self, const char * name, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		if (!strcmp(name, f->name)) {
			(*outIndex) = (class_count_sfieldall(self) - self->sfield_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_sfield_tree(class_ * self, const char * name, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_sfield(pointee, name, outIndex);
		if (f != NULL) {
			return f;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return NULL;
}

field * class_get_field(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_fieldall(self);
	if (index >= (all - self->field_list->length) &&
		index < all) {
		return vector_at(self->field_list, self->field_list->length - (all - index));
	}
	return class_get_field(self->super_class->core_type->u.class_, index);
}

field * class_get_sfield(class_ * self, int index) {
	assert(index >= 0);
	int all = class_count_sfieldall(self);
	if (index >= (all - self->sfield_list->length) &&
		index < all) {
//		return vector_at(self->sfield_list, all - index);
		return vector_at(self->sfield_list, self->sfield_list->length - (all - index));
	}
	return class_get_sfield(self->super_class, index);
}

constructor * class_find_rconstructor(class_ * self, vector * args, int* outIndex) {
//	vector* v = meta_find_rconstructors(self, args);
//	(*outIndex) = -1;
//	return class_find_rconstructor_impl(v, args, outIndex);
	return meta_find_rctor(self->constructor_list, args, outIndex);
}

constructor * class_find_constructor(class_ * self, vector * args, enviroment * env, il_context* ilctx, int* outIndex) {
	//	vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	return meta_find_ctor(self->constructor_list, args, env, ilctx, outIndex);
}

constructor * class_find_empty_constructor(class_ * self, enviroment * env, il_context* ilctx, int * outIndex) {
	vector* emptyArgs = vector_new();
	constructor* ret = class_find_constructor(self, emptyArgs, env, ilctx, outIndex);
	vector_delete(emptyArgs, vector_deleter_null);
	return ret;
}

method * class_find_method(class_ * self, const char * name, vector * args, enviroment * env, il_context* ilctx, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_find_method(self->vt->elements, name, args, env, ilctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_find_method(self->method_list, name, args, env, ilctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_find_method(self->smethod_list, name, args, env, ilctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method * class_find_smethod(class_ * self, const char * name, vector * args, enviroment * env, il_context* ilctx, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_find_method(self->smethod_list, name, args, env, ilctx, &temp);
	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method * class_get_method(object * o, int index) {
	assert(index >= 0);
	vtable* vx = (o->vptr);
	return (method*)vector_at(vx->elements, index);
}

method * class_get_smethod(class_* self, int index) {
	assert(index >= 0);
	//class_* self = o->classz;
	int all = class_count_smethodall(self);
	if (index >= (all - self->smethod_list->length) &&
		index < all) {
//		return vector_at(self->smethod_list, all - index);
		return vector_at(self->smethod_list, self->smethod_list->length - (all - index));
	}
	return class_get_smethod(self->super_class->core_type->u.class_, index);
}

method * class_get_impl_method(class_ * self, type * interType, int interMIndex) {
	assert(self->vt_vec->length > 0);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* e = vector_at(self->impl_list, i);
		interface_* inter = e->core_type->u.interface_;
		if (inter == interType->u.interface_) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	vtable* vtAt = vector_at(self->vt_vec, declIndex);
	return vector_at(vtAt->elements, interMIndex);
}

bool class_castable(class_ * self, class_ * other) {
	assert(self != NULL && other != NULL);
	if (self == other) {
		return true;
	}
	class_* pointee = self;
	do {
		if (pointee == other) {
			return true;
		}
		pointee = pointee->super_class;
	} while (pointee != NULL);
	return false;
}

int class_distance(class_ * self, class_ * other) {
	if (self == other) {
		return 0;
	}
	int depth = 0;
	class_* pointee = other;
	do {
		if (pointee == self) {
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

void class_create_vtable(class_ * self) {
	//TEST(!strcmp(self->name, "Int"));
	assert(self != NULL);
	//初期化済み
	if (self->vt != NULL) {
		return;
	}
	//XSTREQ(self->name, "Int");
	self->vt = vtable_new();
	//トップレベルではメソッドの一覧を配列に入れるだけ
	if (self->super_class == NULL) {
		class_create_vtable_top(self);
	//あるクラスを継承する場合には、
	//重複するメソッドを上書きするように
	} else {
		class_create_vtable_ov(self);
	}
	class_create_vtable_interface(self);
}

int class_count_fieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->field_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

int class_count_sfieldall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->sfield_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

int class_count_methodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->method_list->length);
		pt = pt->super_class;
	} while (pt != NULL);
	return sum;
}

int class_count_smethodall(class_ * self) {
	class_* pt = self;
	int sum = 0;
	do {
		sum += (pt->smethod_list->length);
		if(pt->super_class == NULL) {
			break;
		}
		pt = pt->super_class->core_type->u.class_;
	} while (pt != NULL);
	return sum;
}

object * class_new_rinstance(class_ * self, vm* vmc, int count, ...) {
	va_list ap;
	va_start(ap, count);
	//可変長引数をベクターへ
	vector* args = vector_new();
	for (int i = 0; i < count; i++) {
		object* o = va_arg(ap, object*);
		vector_push(args, o);
	}
	//コンストラクタを検索
	int temp = 0;
	constructor* ctor = class_find_rconstructor(self, args, &temp);
	assert(temp != -1);
	//コンストラクタを実行
	vm* sub = vm_sub(vmc);
	heap* h = heap_get();
	for (int i = args->length-1; i>=0; i--) {
		object* o = vector_at(args, i);
		vector_push(sub->value_stack, o);
	}
	vm_execute(sub, ctor->env);
	object* inst = vector_pop(sub->value_stack);
	h->collect_blocking++;
	vm_delete(sub);
	vector_delete(args, vector_deleter_null);
	h->collect_blocking--;
	va_end(ap);
	return inst;
}

void class_linkall(class_ * self) {
	for (int i = 0; i < self->field_list->length; i++) {
		field* f = (field*)vector_at(self->field_list, i);
		f->parent = self->parent;
	}
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		m->parent = self->parent;
	}
	for (int i = 0; i < self->constructor_list->length; i++) {
		constructor* ctor = (constructor*)vector_at(self->constructor_list, i);
		ctor->parent = self->parent;
	}
}

void class_unlink(class_ * self) {
	if (self->super_class != NULL) {
		self->super_class->core_type->u.class_->ref_count--;
	}
	//XSTREQ(self->name, "Object");
	//generic_type_delete(self->super_class);
	//text_printf("unlink %s\n", self->name);
	tree_map_delete(self->native_method_ref_map, class_native_method_ref_delete);
	vector_delete(self->impl_list, class_impl_delete);
	vector_delete(self->field_list, class_field_delete);
	vector_delete(self->sfield_list, class_field_delete);
	vector_delete(self->method_list, class_method_delete);
	vector_delete(self->smethod_list, class_method_delete);
	vector_delete(self->constructor_list, class_ctor_delete);
	vtable_delete(self->vt);
	vector_delete(self->vt_vec, class_vtable_vec_delete);
}

void class_delete(class_ * self) {
//	assert(self->ref_count == 0);
//	MEM_FREE(self->name);
	//text_printf("delete %s\n", self->name);
	vector_delete(self->type_parameter_list, class_type_parameter_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void class_create_vtable_top(class_* self) {
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private &&
		   !modifier_is_static(m->modifier)) {
			vtable_add(self->vt, m);
		}
	}
}

static void class_create_vtable_ov(class_* self) {
	class_create_vtable(self->super_class->core_type->u.class_);
	vtable_copy(self->super_class->core_type->u.class_->vt, self->vt);
	for (int i = 0; i < self->method_list->length; i++) {
		method* m = (method*)vector_at(self->method_list, i);
		if(m->access != access_private &&
		   !modifier_is_static(m->modifier)) {
			vtable_replace(self->vt, m);
		}
	}
}

static void class_create_vtable_interface(class_* self) {
	//もしインターフェースを実装しているなら、
	//インターフェースに対応する同じ並びのメソッドテーブルも作る
	for (int i = 0; i < self->impl_list->length; i++) {
		generic_type* gtp = (generic_type*)vector_at(self->impl_list, i);
		interface_* inter = (interface_*)gtp->core_type->u.interface_;
		vtable* interVT = inter->vt;
		vtable* newVT = vtable_new();
		assert(interVT != NULL);
		//そのインターフェースに定義されたテーブルの一覧
		//これはスーパーインターフェースも含む。
		for (int j = 0; j < interVT->elements->length; j++) {
			//実装クラスの中の、
			//シグネチャが同じメソッドをテーブルへ。
			method* interVTM = vector_at(interVT->elements, j);
			method* classVTM = class_find_impl_method(self, interVTM);
			assert(classVTM != NULL);
			vtable_add(newVT, classVTM);
		}
		vector_push(self->vt_vec, newVT);
	}
}

static void class_impl_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	//generic_type_delete(e);
}

static void class_field_delete(vector_item item) {
	field* e = (field*)item;
	field_delete(e);
}

static void class_method_delete(vector_item item) {
	method* e = (method*)item;
	method_delete(e);
}

static void class_ctor_delete(vector_item item) {
	constructor* e = (constructor*)item;
	constructor_delete(e);
}

static void class_native_method_ref_delete(vector_item item) {
	native_method_ref* e = (native_method_ref*)item;
	native_method_ref_delete(e);
}

static method* class_find_impl_method(class_* self, method* virtualMethod) {
	method* ret = NULL;
	vtable* clVT = self->vt;
	for (int i = 0; i < clVT->elements->length; i++) {
		method* clM = vector_at(clVT->elements, i);
		if (method_override(virtualMethod, clM)) {
			ret = clM;
			break;
		}
	}
	return ret;
}

static void class_vtable_vec_delete(vector_item item) {
	vtable* e = (vtable*)item;
	vtable_delete(e);
}

static void class_type_parameter_delete(vector_item item) {
	type_parameter* e = (type_parameter*)item;
	type_parameter_delete(e);
}

static void class_generic_type_list_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
//	generic_type_delete(e);
}
