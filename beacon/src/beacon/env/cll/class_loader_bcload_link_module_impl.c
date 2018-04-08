#include "class_loader_bcload_link_module_impl.h"
#include "../type_cache.h"
#include "../type_impl.h"
#include "../../il/il_type_impl.h"
#include "../../util/logger.h"
#include "class_loader_bcload_member_module_impl.h"
#include "class_loader_bcload_import_module_impl.h"
#include "class_loader_bcload_impl.h"
#include <assert.h>

//proto

static void CLBC_class_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_class_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

static void CLBC_interface_decl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);
static void CLBC_interface_impl(class_loader* self, il_type* iltype, type* tp, namespace_* scope);

void CLBC_excec_class_decl(class_loader* self) {
	int count = 0;
	//text_printfln("CLASS_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_decl(e->context, e->iltype, e->tp, e->scope);
	}
	if (count > 0) {
		logger_info(__FILE__, __LINE__, "loaded class decl %s", self->filename);
	}
}

void CLBC_excec_class_impl(class_loader* self) {
	int count = 0;
	//text_printfln("CLASS_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_class_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_class_impl(e->context, e->iltype, e->tp, e->scope);
	}
	if (count > 0) {
		logger_info(__FILE__, __LINE__, "loaded class impl %s", self->filename);
	}
}

void CLBC_excec_interface_decl(class_loader* self) {
	int count = 0;
	//text_printfln("INTERFACE_DECL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_decl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_decl(e->context, e->iltype, e->tp, e->scope);
	}
	if(count > 0) {
		logger_info(__FILE__, __LINE__, "loaded interface decl %s", self->filename);
	}
}

void CLBC_excec_interface_impl(class_loader* self) {
	int count = 0;
	//text_printfln("INTERFACE_IMPL %s ==", self->filename);
	for (int i = 0; i < self->type_cache_vec->length; i++) {
		type_cache* e = (type_cache*)vector_at(self->type_cache_vec, i);
		if (e->kind != cachekind_interface_impl || e->consume) {
			continue;
		}
		count++;
		e->consume = true;
		CLBC_interface_impl(e->context, e->iltype, e->tp, e->scope);
	}
	if(count > 0) {
		logger_info(__FILE__, __LINE__, "loaded interface impl %s", self->filename);
	}
}

void CLBC_yield(class_loader* parent, class_loader* target) {
	assert(target->source_code != NULL);
	CLBC_import(target, target->il_code->import_list);
	CLBC_namespace_tree(target);

	CLBC_excec_class_decl(target);
	CLBC_excec_interface_decl(target);
}
//private
static void CLBC_class_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	//TEST((!strcmp(tp->u.class_->name, "Array") && self->a == 0));
	//printf("aaa");
	//TEST((!strcmp(tp->u.class_->name, "Array") && self->a == 1));
	assert(tp->u.class_->method_list->length == 0);
	assert(tp->u.class_->smethod_list->length == 0);
	//type_init_generic(tp, tp->u.class_->type_parameter_list->length);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->field_list, scope);
	CLBC_fields_decl(self, iltype, tp, iltype->u.class_->sfield_list, scope);

	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->method_list, scope);
	CLBC_methods_decl(self, iltype, tp, iltype->u.class_->smethod_list, scope);

	//class_loader_sgload_fields(self, iltype, tp);
	//class_loader_sgload_methods(self, iltype, tp, scope);
	CLBC_ctor_decl(self, iltype, tp, scope);
	class_create_vtable(tp->u.class_);	
}

static void CLBC_class_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	CLBC_fields_impl(self, scope, iltype->u.class_->field_list, (TYPE2CLASS(tp))->field_list);
	CLBC_fields_impl(self, scope, iltype->u.class_->sfield_list, (TYPE2CLASS(tp))->sfield_list);
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->method_list, ((TYPE2CLASS(tp))->method_list));
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.class_->smethod_list, ((TYPE2CLASS(tp))->smethod_list));
	CLBC_ctor_impl(self, iltype, tp);
}

static void CLBC_interface_decl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	assert(tp->u.interface_->method_list->length == 0);
//	class_loader_sgload_methods(self, iltype, tp, scope);
//ArrayIterator<T>の時、中のTが考慮されていない
	//XSTREQ(iltype->u.interface_->name, "Iterator");
//	type_init_generic(tp, tp->u.interface_->type_parameter_list->length);
	CLBC_methods_decl(self, iltype, tp, iltype->u.interface_->method_list, scope);
}

static void CLBC_interface_impl(class_loader * self, il_type * iltype, type * tp, namespace_ * scope) {
	CLBC_methods_impl(self, scope, iltype, tp, iltype->u.interface_->method_list, tp->u.interface_->method_list);
	interface_create_vtable(tp->u.interface_);
}