#include "class_loader_link_impl.h"
#include "../type_cache.h"
#include "../../error.h"
#include "../type_impl.h"
#include "../field.h"
#include "../../il/il_type_impl.h"
#include "../../error.h"
#include "../../env/constructor.h"
#include "../../env/object.h"
#include "../../env/property.h"
#include "../../util/text.h"
#include "class_loader_bcload_member_module_impl.h"
#include "class_loader_bcload_import_module_impl.h"
#include "class_loader_bcload_impl.h"
#include <assert.h>

static void CLBC_class_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_class_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

static void CLBC_interface_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_interface_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

static void CLBC_enum_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);
static void CLBC_enum_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);

static void CLBC_excec_class_decl(class_loader* self);
static void CLBC_excec_class_impl(class_loader* self);
static void CLBC_excec_interface_decl(class_loader* self);
static void CLBC_excec_interface_impl(class_loader* self);
static void CLBC_excec_enum_decl(class_loader* self);
static void CLBC_excec_enum_impl(class_loader* self);
static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);
static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope);

void class_loader_link(class_loader* self, link_type type) {
	CL_ERROR(self);
	bc_error_file(self->filename);
	if(type == link_decl_T) {
		CLBC_excec_class_decl(self);
		CL_ERROR(self);
		CLBC_excec_interface_decl(self);
		CL_ERROR(self);
		CLBC_excec_enum_decl(self);
	} else if(type == link_impl_T) {
		CLBC_excec_class_impl(self);
		CL_ERROR(self);
		CLBC_excec_interface_impl(self);
		CL_ERROR(self);
		CLBC_excec_enum_impl(self);
	} else assert(false);
}

//private
static void CLBC_class_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	#if defined(DEBUG)
	const char* name = string_pool_ref2str(type_name(tp));
	#endif
	CL_ERROR(self);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);
	CL_ERROR(self);
	CLBC_properties_decl(self, iltype, tp, iltype->u.class_->prop_list, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->method_list, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->smethod_list, scope);
	CL_ERROR(self);

	CLBC_ctors_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CLBC_operator_overloads_decl(self, iltype, tp, scope);
	CL_ERROR(self);

	CL_ERROR(self);
	tp->state = tp->state | type_decl;
}

static void CLBC_class_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	#if defined(DEBUG) || defined(_DEBUG)
	const char* tyname = string_pool_ref2str(type_name(tp));
	#endif
	class_create_vtable(tp->u.class_);
	class_create_operator_vt(tp->u.class_);
	CL_ERROR(self);
	CLBC_fields_impl(self, scope, tp, iltype->u.class_->field_list, (TYPE2CLASS(tp))->field_list);
	CLBC_fields_impl(self, scope, tp, iltype->u.class_->sfield_list, (TYPE2CLASS(tp))->sfield_list);
	CL_ERROR(self);
	CLBC_properties_impl(self, iltype, tp, iltype->u.class_->prop_list, tp->u.class_->prop_list, scope);
	CLBC_properties_impl(self, iltype, tp, iltype->u.class_->sprop_list, tp->u.class_->sprop_list, scope);
	CL_ERROR(self);

	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->method_list, ((TYPE2CLASS(tp))->method_list));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->smethod_list, ((TYPE2CLASS(tp))->smethod_list));
	CL_ERROR(self);

	CLBC_ctors_impl(self, iltype, tp);
	CL_ERROR(self);

	CLBC_operator_overloads_impl(self, iltype, tp, scope);
	CL_ERROR(self);
	tp->state = tp->state | type_impl;
	CLBC_check_class(self, iltype, tp, scope);
}

static void CLBC_interface_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	assert(tp->u.interface_->method_list->length == 0);
	CL_ERROR(self);
	CLBC_methods_decl(self, iltype, tp, iltype->u.interface_->method_list, scope);
	CLBC_properties_decl(self, iltype, tp, iltype->u.interface_->prop_list, scope);
	//privateなメンバーは定義できない
	for(int i=0; i<tp->u.interface_->method_list->length; i++) {
		method* e = vector_at(tp->u.interface_->method_list, i);
		if(e->access == access_private_T) {
			bc_error_throw(
				bcerror_interface_has_private_member_T,
				string_pool_ref2str(type_name(tp)),
				string_pool_ref2str(e->namev)
			);
		}
	}
	for(int i=0; i<tp->u.interface_->prop_list->length; i++) {
		property* e = vector_at(tp->u.interface_->prop_list, i);
		if(e->access == access_private_T) {
			bc_error_throw(
				bcerror_interface_has_private_member_T,
				string_pool_ref2str(type_name(tp)),
				string_pool_ref2str(e->namev)
			);
		}
	}
	CL_ERROR(self);
	interface_create_vtable(tp->u.interface_);
	tp->state = tp->state | type_decl;
	CLBC_check_interface(self, iltype, tp, scope);
}

static void CLBC_interface_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	CL_ERROR(self);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
	tp->state = tp->state | type_impl;
}

static void CLBC_enum_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_decl) > 0) {
		return;
	}
	//重複するフィールドを確認する
	field* outField = NULL;
	if((tp->tag == type_enum_T ||
	   tp->tag == type_class_T) &&
	   !class_field_valid(tp->u.class_, &outField)) {
		bc_error_throw(bcerror_overwrap_field_name_T, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outField->namev));
	}
	tp->state = tp->state | type_decl;
}

static void CLBC_enum_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	if((tp->state & type_impl) > 0) {
		return;
	}
	for(int i=0; i<tp->u.class_->sfield_list->length; i++) {
		field* f = vector_at(tp->u.class_->sfield_list, i);
		f->static_value = object_int_get(i);
	}
	tp->state = tp->state | type_impl;
}

static void CLBC_excec_class_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_decl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_class_impl(class_loader* self) {
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_impl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_interface_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_decl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_interface_impl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_impl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_enum_decl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_enum_decl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_enum_decl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_excec_enum_impl(class_loader* self) {
	CL_ERROR(self);
	int count = 0;
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_enum_impl_T || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_enum_impl(e->context, e->iltype, e->tp, e->scope);
	}
}

static void CLBC_check_class(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//実装されていないインターフェイスを確認する
	method* outiMethod = NULL;
	if(tp->tag == type_class_T &&
	  !class_interface_method_implement_valid(TYPE2CLASS(tp), &outiMethod)) {
		bc_error_throw(bcerror_not_implement_interface_T, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outiMethod->namev));
		return;
	}
	//実装されていないプロパティを確認する
	property* outiProperty = NULL;
	if(tp->tag == type_class_T &&
	  !class_interface_property_implement_valid(TYPE2CLASS(tp), &outiProperty)) {
		bc_error_throw(bcerror_not_implement_abstract_method_T, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outiProperty->namev));
		return;
	}
	//実装されていない抽象メソッドを確認する
	method* outaMethod = NULL;
	if(tp->tag == type_class_T &&
	   !class_abstract_class_implement_valid(TYPE2CLASS(tp), &outaMethod)) {
		bc_error_throw(bcerror_not_implement_abstract_method_T, string_pool_ref2str(tp->u.class_->namev), string_pool_ref2str(outaMethod->namev));
		return;
	   }
	//重複するプロパティを確認する
	property* outProp = NULL;
	if(!class_property_valid(tp->u.class_, &outProp)) {
		bc_error_throw(bcerror_overwrap_property_name_T,
			string_pool_ref2str(tp->u.class_->namev),
			string_pool_ref2str(outProp->namev)
		);
		return;
	}
	//重複するフィールドを確認する
	field* outField = NULL;
	if(!class_field_valid(tp->u.class_, &outField)) {
		bc_error_throw(bcerror_overwrap_field_name_T,
			string_pool_ref2str(tp->u.class_->namev),
			string_pool_ref2str(outField->namev)
		);
		return;
	}
	//メソッドの重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_mname;
	if(!class_method_parameter_valid(tp->u.class_, &out_overwrap_m, &out_overwrap_mname)) {
		bc_error_throw(bcerror_overwrap_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_m->namev),
			string_pool_ref2str(out_overwrap_mname)
		);
		return;
	}
	//コンストラクタの重複するパラメータ名を検出する
	constructor* out_overwrap_c = NULL;
	string_view out_overwrap_cname;
	if(!class_ctor_parameter_valid(tp->u.class_, &out_overwrap_c, &out_overwrap_cname)) {
		bc_error_throw(bcerror_overwrap_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			"new",
			string_pool_ref2str(out_overwrap_cname)
		);
		return;
	}
	//クラスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!class_type_type_parameter_valid(tp->u.class_, &out_overwrap_tpname)) {
		bc_error_throw(bcerror_overwrap_type_type_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpname)
		);
		return;
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!class_method_type_parameter_valid(tp->u.class_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_error_throw(bcerror_overwrap_method_type_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpm->namev),
			string_pool_ref2str(out_overwrap_tpmname)
		);
		return;
	}
	//コンストラクタで初期化されていない final フィールドの確認
	//これはコンストラクタが生成されてからでないといけない
	class_* cls = TYPE2CLASS(tp);
	for(int i=0; i<cls->field_list->length; i++) {
		field* fi = vector_at(cls->field_list, i);
		//インスタンス定数が
		//フィールドでもコンストラクタでも初期化されない
		if(!modifier_is_static(fi->modifier) &&
			modifier_is_final(fi->modifier) &&
			!fi->not_initialized_at_ctor) {
			bc_error_throw(bcerror_not_initial_field_not_initialized_at_ctor_T,
				string_pool_ref2str(type_name(tp)),
				string_pool_ref2str(fi->namev)
			);
			return;
		}
	}
}

static void CLBC_check_interface(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//重複するパラメータ名を検出する
	method* out_overwrap_m = NULL;
	string_view out_overwrap_name;
	if(!interface_method_parameter_valid(tp->u.interface_, &out_overwrap_m, &out_overwrap_name)) {
		bc_error_throw(bcerror_overwrap_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_m->namev),
			string_pool_ref2str(out_overwrap_name)
		);
	}
	//インターフェイスの重複する型パラメータ名を検出する
	string_view out_overwrap_tpname;
	if(!interface_type_type_parameter_valid(tp->u.interface_, &out_overwrap_tpname)) {
		bc_error_throw(bcerror_overwrap_type_type_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpname)
		);
	}
	//メソッドの重複する型パラメータ名を検出する
	method* out_overwrap_tpm = NULL;
	string_view out_overwrap_tpmname;
	if(!interface_method_type_parameter_valid(tp->u.interface_, &out_overwrap_tpm, &out_overwrap_tpmname)) {
		bc_error_throw(bcerror_overwrap_method_type_parameter_name_T,
			string_pool_ref2str(type_name(tp)),
			string_pool_ref2str(out_overwrap_tpm->namev),
			string_pool_ref2str(out_overwrap_tpmname)
		);
	}
}