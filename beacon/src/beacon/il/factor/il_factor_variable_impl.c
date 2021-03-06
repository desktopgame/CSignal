#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../il_type_argument.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/type_impl.h"
#include "../../env/field.h"
#include "../../util/mem.h"
#include "../../vm/symbol_entry.h"
#include <assert.h>
#include <string.h>

//proto
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, call_context* cctx);
static void il_factor_variable_check_instance(il_factor_variable* self, enviroment* env, call_context* cctx);
static void il_factor_variable_check_static(il_factor_variable* self, enviroment* env, call_context* cctx);
static void il_factor_delete_typeargs(vector_item item);

il_factor * il_factor_wrap_variable(il_factor_variable * self) {
	il_factor* ret = il_factor_new(ilfactor_variable_T);
	ret->u.variable_ = self;
	return ret;
}

il_factor_variable * il_factor_variable_malloc(const char* filename, int lineno) {
	il_factor_variable* ret = (il_factor_variable*)mem_malloc(sizeof(il_factor_variable), filename, lineno);
	ret->fqcn = fqcn_cache_malloc(filename, lineno);
	ret->type_args = vector_malloc(filename, lineno);
	ret->type = ilvariable_type_undefined_T;
	return ret;
}

void il_factor_variable_dump(il_factor_variable * self, int depth) {
	io_printi(depth);
	printf("variable ");
	fqcn_cache_print(self->fqcn);
	io_println();
}

void il_factor_variable_generate(il_factor_variable * self, enviroment* env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	if(self->type == ilvariable_type_local_T) {
		il_factor_variable_local_generate(self->u.local_, env, cctx);
	} else if(self->type == ilvariable_type_static_T) {
		il_factor_variable_static_generate(self->u.static_, env, cctx);
	}
}

void il_factor_variable_load(il_factor_variable * self, enviroment * env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	if(self->type == ilvariable_type_local_T) {
		il_factor_variable_local_load(self->u.local_, env, cctx);
	} else if(self->type == ilvariable_type_static_T) {
		il_factor_variable_static_load(self->u.static_, env, cctx);
	}
}

generic_type* il_factor_variable_eval(il_factor_variable * self, enviroment * env, call_context* cctx) {
	il_factor_variable_check(self, env, cctx);
	generic_type* ret = NULL;
	if(self->type == ilvariable_type_local_T) {
		ret = il_factor_variable_local_eval(self->u.local_, env, cctx);
	} else if(self->type == ilvariable_type_static_T) {
		ret = il_factor_variable_static_eval(self->u.static_, env, cctx);
	}
	return ret;
}

char* il_factor_variable_tostr(il_factor_variable* self, enviroment* env) {
	if(self->type == ilvariable_type_local_T) {
		return il_factor_variable_local_tostr(self->u.local_, env);
	} else if(self->type == ilvariable_type_static_T) {
		return il_factor_variable_static_tostr(self->u.static_, env);
	}
	return NULL;
}

void il_factor_variable_delete(il_factor_variable * self) {
	//MEM_FREE(self->name);
	if(self->type == ilvariable_type_local_T) {
		il_factor_variable_local_delete(self->u.local_);
	} else if(self->type == ilvariable_type_static_T) {
		il_factor_variable_static_delete(self->u.static_);
	}
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, il_factor_delete_typeargs);
	MEM_FREE(self);
}

//private
static void il_factor_variable_check(il_factor_variable* self, enviroment* env, call_context* cctx) {
	if(self->type != ilvariable_type_undefined_T) {
		return;
	}
	assert(self->fqcn != NULL);
	//hoge, foo のような文字列の場合
	if(self->fqcn->scope_vec->length == 0) {
		il_factor_variable_check_instance(self, env, cctx);
	//Namespace::Hoge Namespace::Foo のような文字列の場合.
	} else if(self->fqcn->scope_vec->length > 0) {
		il_factor_variable_check_static(self, env, cctx);
	}
}

static void il_factor_variable_check_instance(il_factor_variable* self, enviroment* env, call_context* cctx) {
	namespace_* cur = call_context_namespace(cctx);
	class_* ctype = namespace_get_class(cur, self->fqcn->namev);
	if(ctype == NULL) {
		ctype = namespace_get_class(namespace_lang(), self->fqcn->namev);
	}
	//現在の名前空間から参照できるクラスがある場合
	if(ctype != NULL) {
		il_factor_variable_check_static(self, env, cctx);
	//ただのローカル変数の場合
	} else {
		il_factor_variable_local* lc = il_factor_variable_local_new(self->fqcn->namev);
		self->type = ilvariable_type_local_T;
		//値を入れ替え
		lc->type_args = self->type_args;
		self->type_args = NULL;
		self->u.local_ = lc;
	}
}

static void il_factor_variable_check_static(il_factor_variable* self, enviroment* env, call_context* cctx) {
	il_factor_variable_static* st = il_factor_variable_static_new();
	self->type = ilvariable_type_static_T;
	//値を入れ替え
	st->fqcn = self->fqcn;
	st->type_args = self->type_args;
	self->fqcn = NULL;
	self->type_args = NULL;
	self->u.static_ = st;
}

static void il_factor_delete_typeargs(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}

il_factor_variable* il_factor_cast_variable_T(il_factor* fact) {
	assert(fact->type == ilfactor_variable_T);
	return fact->u.variable_;
}