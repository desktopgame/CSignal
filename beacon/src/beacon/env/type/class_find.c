#include "class_find.h"
#include "meta_impl.h"
#include "../object.h"
#include "interface_impl.h"
#include "../field.h"
#include "../property.h"
#include "../property_body.h"
#include "../parameter.h"
#include "../generic_type.h"
#include "../../il/il_argument.h"
#include "../../il/il_factor_impl.h"
#include "../../util/vector.h"

static bool class_contains_fieldImpl(vector* fields, field* f);
static bool class_contains_propertyImpl(vector* props, property* p);

field * class_find_field(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->field_list->length; i++) {
		vector_item e = vector_at(self->field_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_fieldall(self) - self->field_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_field_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_field(pointee, namev, outIndex);
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

field * class_find_sfield(class_ * self, string_view namev, int * outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sfield_list->length; i++) {
		vector_item e = vector_at(self->sfield_list, i);
		field* f = (field*)e;
		if (namev == f->namev) {
			(*outIndex) = (class_count_sfieldall(self) - self->sfield_list->length) + i;
			return f;
		}
	}
	return NULL;
}

field * class_find_sfield_tree(class_ * self, string_view namev, int * outIndex) {
	class_* pointee = self;
	do {
		field* f = class_find_sfield(pointee, namev, outIndex);
		if (f != NULL) {
			return f;
		}
		if(pointee->super_class == NULL) {
			break;
		}
		pointee = pointee->super_class->core_type->u.class_;
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
		return vector_at(self->sfield_list, self->sfield_list->length - (all - index));
	}
	return class_get_sfield(self->super_class->core_type->u.class_, index);
}

bool class_contains_field(class_* self, field* f) {
	return class_contains_fieldImpl(self->field_list, f);
}

bool class_contains_sfield(class_* self, field* f) {
	return class_contains_fieldImpl(self->sfield_list, f);
}

bool class_accessible_field(class_* self, field* f) {
	assert(f != NULL);
	if(f->access == access_public_T) {
		return true;
	}
	if(f->access == access_private_T) {
		return self == TYPE2CLASS(f->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(f->parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}



bool class_contains_property(class_* self, property* p) {
	return class_contains_propertyImpl(self->prop_list, p);
}

bool class_contains_sproperty(class_* self, property* p) {
	return class_contains_propertyImpl(self->sprop_list, p);
}

bool class_accessible_property(class_* self, property* p) {
	assert(p != NULL);
	if(p->access == access_public_T) {
		return true;
	}
	if(p->access == access_private_T) {
		return self == TYPE2CLASS(p->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(p->parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}

bool class_accessible_property_accessor(class_* self, property_body* pb) {
	assert(pb != NULL);
	if(pb->access == access_public_T) {
		return true;
	}
	if(pb->access == access_private_T) {
		return self == TYPE2CLASS(pb->parent->parent);
	}
	type* ty = self->parent;
	class_* fcl = TYPE2CLASS(pb->parent->parent);
	while(true) {
		class_* c = TYPE2CLASS(ty);
		if(c == fcl) {
			return true;
		}
		//次へ
		if(c->super_class == NULL) {
			break;
		}
		ty = c->super_class->core_type;
	}
	return false;
}

int class_get_field_by_property(class_* self, property* p) {
	int temp = -1;
	assert(p->source_ref != NULL);
	if(modifier_is_static(p->modifier)) {
		class_find_sfield(self, p->source_ref->namev, &temp);
	} else {
		class_find_field(self, p->source_ref->namev, &temp);
	}
	return temp;
}

property* class_get_property(class_* self, int index) {
	assert(index >= 0);
	int all = class_count_propertyall(self);
	if (index >= (all - self->prop_list->length) &&
		index < all) {
		return vector_at(self->prop_list, self->prop_list->length - (all - index));
	}
	return class_get_property(self->super_class->core_type->u.class_, index);
}

property* class_get_sproperty(class_* self, int index) {
	assert(index >= 0);
	int all = class_count_spropertyall(self);
	if (index >= (all - self->sprop_list->length) &&
		index < all) {
		return vector_at(self->sprop_list, self->sprop_list->length - (all - index));
	}
	return class_get_property(self->super_class->core_type->u.class_, index);
}

property* class_find_property(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->prop_list->length; i++) {
		vector_item e = vector_at(self->prop_list, i);
		property* p = (property*)e;
		if (namev == p->namev) {
			(*outIndex) = (class_count_propertyall(self) - self->prop_list->length) + i;
			return p;
		}
	}
	return NULL;
}

property* class_find_property_tree(class_* self, string_view namev, int* outIndex) {
	class_* pointee = self;
	do {
		property* p = class_find_property(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}

property* class_find_sproperty(class_* self, string_view namev, int* outIndex) {
	(*outIndex) = -1;
	for (int i = 0; i < self->sprop_list->length; i++) {
		vector_item e = vector_at(self->sprop_list, i);
		property* p = (property*)e;
		if (namev == p->namev) {
			(*outIndex) = (class_count_spropertyall(self) - self->sprop_list->length) + i;
			return p;
		}
	}
	return NULL;
}

property* class_find_sproperty_tree(class_* self, string_view namev, int* outIndex) {
	class_* pointee = self;
	do {
		property* p = class_find_sproperty(pointee, namev, outIndex);
		if (p != NULL) {
			return p;
		}
		generic_type* supergtype = pointee->super_class;
		if(supergtype == NULL) {
			break;
		}
		pointee = supergtype->core_type->u.class_;
	} while (pointee != NULL);
	return NULL;
}



constructor * class_rfind_constructor(class_ * self, vector * args, vector* typeargs, frame* fr, int* outIndex) {
	return meta_scoped_rfind_ctor(self, self->constructor_list, args, typeargs, fr, outIndex);
}

constructor * class_ilfind_constructor(class_ * self, vector * args, enviroment * env, call_context* cctx, int* outIndex) {
	//	vector* v = meta_find_constructors(self, args, env, ilctx);
	//	(*outIndex) = -1;
	//	return class_find_constructor_impl(v, args, env, ilctx, outIndex);
	constructor* ctor = meta_scoped_ilfind_ctor(self, self->constructor_list, args, env, cctx, outIndex);
	return ctor;
}

constructor * class_ilfind_empty_constructor(class_ * self, enviroment * env, call_context* cctx, int * outIndex) {
	vector* emptyArgs = vector_new();
	constructor* ret = class_ilfind_constructor(self, emptyArgs, env, cctx, outIndex);
	vector_delete(emptyArgs, vector_deleter_null);
	return ret;
}



method * class_ilfind_method(class_ * self, string_view namev, vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	#if defined(DEBUG)
	const char* str = string_pool_ref2str(self->namev);
	#endif
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_ilfind_method(self, self->vt->elements, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->method_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_ilfind_method(self, self->smethod_list, namev, args, env, cctx, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method* class_gfind_method(class_* self, string_view namev, vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	//assert(self->vt->elements->length > 0);
	method* ret = NULL;
	if((ret = meta_scoped_gfind_method(self, self->vt->elements, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->method_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	if((ret = meta_scoped_gfind_method(self, self->smethod_list, namev, gargs, outIndex))
	   != NULL) {
		   return ret;
	}
	return NULL;
}

method* class_gfind_eqmethod(class_* self, int* outIndex) {
	vector* gargs = vector_new();
	vector_push(gargs, TYPE_OBJECT->generic_self);
	method* ret = class_gfind_method(self, string_pool_intern("equals"), gargs, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

method * class_ilfind_smethod(class_ * self, string_view namev, vector * args, enviroment * env, call_context* cctx, int * outIndex) {
	#if defined(DEBUG)
	const char* str = string_pool_ref2str(namev);
	#endif
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_ilfind_method(self->smethod_list, namev, args, env, cctx, &temp);
//	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method* class_gfind_smethod(class_* self, string_view namev, vector* gargs, int* outIndex) {
	(*outIndex) = -1;
	class_create_vtable(self);
	int temp = 0;
	method* ret = meta_gfind_method(self->smethod_list, namev, gargs, &temp);
//	temp += (class_count_smethodall(self) - self->smethod_list->length);
	(*outIndex) = temp;
	return ret;
}

method * class_get_method(object * o, int index) {
	assert(index >= 0);
	#if defined(DEBUG)
	const char* name = object_name(o);
	#endif
	if(o->tag == object_null_T) {
		o->vptr = TYPE2CLASS(TYPE_OBJECT)->vt;
	}
	vtable* vx = (o->vptr);
	return (method*)vector_at(vx->elements, index);
}

method * class_get_smethod(class_* self, int index) {
	assert(index >= 0);
	/*
	//class_* self = o->classz;
	int all = class_count_smethodall(self);
	if (index >= (all - self->smethod_list->length) &&
		index < all) {
		return vector_at(self->smethod_list, self->smethod_list->length - (all - index));
	}
	return class_get_smethod(self->super_class->core_type->u.class_, index);
	//*/
	return vector_at(self->smethod_list, index);
}

method * class_get_impl_method(class_ * self, type * interType, int interMIndex) {
	#if defined(DEBUG)
	const char* str = string_pool_ref2str(self->namev);
	#endif
	assert(self->vt_vec->length > 0);
	vector* tbl = class_get_generic_interface_tree(self);
	//指定のインターフェイスが
	//このクラスにおいて何番目かを調べる
	int declIndex = -1;
	for (int i = 0; i < tbl->length; i++) {
		generic_type* e = vector_at(tbl, i);
		interface_* inter = e->core_type->u.interface_;
		if (inter == interType->u.interface_) {
			declIndex = i;
			break;
		}
	}
	//仮想関数テーブルの一覧から引く
	assert(declIndex != -1);
	vector_delete(tbl, vector_deleter_null);
	vtable* vtAt = vector_at(self->vt_vec, declIndex);
	return vector_at(vtAt->elements, interMIndex);
}




operator_overload* class_gfind_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	(*outIndex) = -1;
	operator_overload* ret = NULL;
	class_create_operator_vt(self);
	for(int i=0; i<self->ovt->vec->length; i++) {
		operator_overload* operator_ov = vector_at(self->ovt->vec, i);
		if(operator_ov->type != type) {
			continue;
		}
		bool nomatch = false;
		int score = 1024;
		int sum = 0;
		vector* params = operator_ov->parameter_list;
		for(int j=0; j<params->length; j++) {
			parameter* param = vector_at(params, j);
			generic_type* arg = vector_at(args, j);
			int dist = generic_type_distance(param->gtype, arg, cctx);
			if(dist == -1) {
				nomatch = true;
				break;
			}
			sum += dist;
		}
		if(nomatch) {
			continue;
		}
		if(sum < score) {
			score = sum;
			(*outIndex) = i;
			ret = operator_ov;
		}
	}
	return ret;
}

operator_overload* class_ilfind_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	vector* gargs =vector_new();
	for(int i=0; i<args->length; i++) {
		il_factor* ilfact = (il_factor*)vector_at(args,i);
		generic_type* g = il_factor_eval(ilfact, env, cctx);
		vector_push(gargs, g);
	}
	operator_overload* ret = class_gfind_operator_overload(self, type, gargs, env, cctx, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

operator_overload* class_argfind_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, call_context* cctx, int* outIndex) {
	vector* gargs =vector_new();
	for(int i=0; i<args->length; i++) {
		//il_factor* ilfact = (il_factor*)vector_at(args,i);
		il_argument* ilarg = (il_argument*)vector_at(args, i);
		il_factor* ilfact = ilarg->factor;
		generic_type* g = il_factor_eval(ilfact, env, cctx);
		vector_push(gargs, g);
	}
	operator_overload* ret = class_gfind_operator_overload(self, type, gargs, env, cctx, outIndex);
	vector_delete(gargs, vector_deleter_null);
	return ret;
}

operator_overload* class_get_operator_overload(class_* self, int index) {
	return vector_at(self->ovt->vec, index);
}

vector* class_find_methods_tree(class_* self, method* m) {
	assert(self != NULL);
	assert(m != NULL);
	class_* ptr = self;
	vector* ret = vector_new();
	#if defined(DEBUG)
	const char* ptrname = string_pool_ref2str(ptr->namev);
	#endif
	do {
		method* tmp = NULL;
		if(class_contains_method(ptr->method_list, m, &tmp)) {
			vector_push(ret, tmp);
		}
		//親クラスへ
		if(ptr->super_class != NULL) {
			ptr = ptr->super_class->core_type->u.class_;
		} else {
			ptr = NULL;
		}
	} while(ptr != NULL);
	return ret;
}

bool class_contains_method(vector* method_list, method* m, method** outM) {
	assert(!modifier_is_static(m->modifier));
	(*outM) = NULL;
	bool ret = false;
	call_context* cctx = call_context_new(call_decl_T);
	cctx->scope = m->parent->location;
	cctx->ty = m->parent;
	for(int i=0; i<method_list->length; i++) {
		method* mE = vector_at(method_list, i);
		if(method_override(m, mE, cctx)) {
			(*outM) = mE;
			ret = true;
			break;
		}
	}
	call_context_delete(cctx);
	return ret;
}

vector* class_get_generic_interface_list(class_* self) {
	vector* ret = vector_new();
	for(int i=0; i<self->impl_list->length; i++) {
		generic_type* ginter = vector_at(self->impl_list, i);
		vector* inner = interface_get_generic_interface_tree(TYPE2INTERFACE(GENERIC2TYPE(ginter)));
		vector_merge(ret, inner);
		vector_push(ret, ginter);
		vector_delete(inner, vector_deleter_null);
	}
	return ret;
}

vector* class_get_generic_interface_tree(class_* self) {
	class_* ptr = self;
	vector* ret = vector_new();
	do {
		vector* v = class_get_generic_interface_list(ptr);
		vector_merge(v, ret);
		vector_delete(v, vector_deleter_null);
		if(ptr->super_class == NULL) {
			break;
		}
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->super_class));
	} while(ptr != NULL);
	return ret;
}

vector* class_get_interface_list(class_* self) {
	vector* ret = vector_new();
	vector* c = class_get_generic_interface_list(self);
	for(int i=0; i<c->length; i++) {
		generic_type* gt = vector_at(c, i);
		vector_push(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	vector_delete(c, vector_deleter_null);
	return ret;
}

vector* class_get_interface_tree(class_* self) {
	vector* ret = vector_new();
	vector* c = class_get_generic_interface_tree(self);
	for(int i=0; i<c->length; i++) {
		generic_type* gt = vector_at(c, i);
		vector_push(ret, TYPE2INTERFACE(GENERIC2TYPE(gt)));
	}
	vector_delete(c, vector_deleter_null);
	return ret;
}

generic_type* class_find_interface_type(class_* self, type* tinter, generic_type** out_baseline) {
	assert(tinter->tag == type_interface_T);
	(*out_baseline) = NULL;
	//実装インターフェイス一覧から同じのを探す
	generic_type* ret = NULL;
	generic_type* out = NULL;
	class_* ptr = self;
	do {
		if (ptr->super_class == NULL) {
			break;
		}
		bool found = false;
		//vector* gimpl_list = class_get_generic_interface_list(ptr);
		vector* gimpl_list = ptr->impl_list;
		for (int i = 0; i < gimpl_list->length; i++) {
			generic_type* gimpl = vector_at(gimpl_list, i);
			if (gimpl->core_type == tinter) {
				found = true;
				ret = gimpl;
				break;
			}
		}
		//vector_delete(gimpl_list, vector_deleter_null);
		if (found) {
			(*out_baseline) = out;
			break;
		}
		out = ptr->super_class;
		ptr = TYPE2CLASS(GENERIC2TYPE(ptr->super_class));
	} while (ptr != NULL);
	return ret;
}

//private
static bool class_contains_fieldImpl(vector* fields, field* f) {
	for(int i=0; i<fields->length; i++) {
		field* e = (field*)vector_at(fields, i);
		if(e == f) {
			return true;
		}
	}
	return false;
}

static bool class_contains_propertyImpl(vector* props, property* p) {
	for(int i=0; i<props->length; i++) {
		property* e = (property*)vector_at(props, i);
		if(e == p) {
			return true;
		}
	}
	return false;
}