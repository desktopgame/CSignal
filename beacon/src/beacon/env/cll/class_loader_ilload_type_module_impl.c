#include "class_loader_ilload_type_module_impl.h"
#include "../../ast/ast.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../../util/text.h"

#include "../class_loader.h"
#include "../../il/il_type_parameter_rule.h"
#include "../../il/il_type_parameter.h"
#include "../../il/il_type_argument.h"
#include "../../il/il_argument.h"
#include "class_loader_ilload_impl.h"
#include <assert.h>

//proto
static void CLIL_generic_cache_impl(ast* fqcn, generic_cache* dest);
static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest);
static void CLIL_type_parameter_rule(struct class_loader* self, struct ast* source, vector* dest);

void CLIL_fqcn_cache(ast* afqcn, fqcn_cache* fqcn) {
if(afqcn->tag == ast_fqcn_class_name) {
		fqcn->name = text_strdup(afqcn->u.string_value);
		return;
	}
	if(afqcn->tag == ast_fqcn ||
	   afqcn->tag == ast_fqcn_part_list) {
		if (afqcn->tag == ast_fqcn_part_list &&
			afqcn->child_count == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			afqcn->tag = ast_fqcn_class_name;
			fqcn->name = text_strdup(afqcn->u.string_value);
			return;
		}
		for(int i=0; i<afqcn->child_count; i++) {
			CLIL_fqcn_cache(ast_at(afqcn, i), fqcn);
		}
	} else {
		char* name = text_strdup(afqcn->u.string_value);
		vector_push(fqcn->scope_vec, name);
		afqcn->tag = ast_fqcn_part;
	}
}

void CLIL_generic_cache(ast* fqcn, generic_cache* dest) {
//assert(fqcn->tag == ast_typename);
	if(fqcn->tag == ast_fqcn_class_name) {
		dest->fqcn->name = text_strdup(fqcn->u.string_value);
		return;
	}
	CLIL_generic_cache_impl(fqcn, dest);
	fqcn_cache* body = dest->fqcn;
	//FIXME: Int のような文字パースで失敗してしまうので対策
	if (body->name == NULL &&
		body->scope_vec->length > 0) {
		body->name = (char*)vector_pop(body->scope_vec);
	}
}

void CLIL_type_parameter(class_loader* self, ast* source, vector* dest) {
	if (ast_is_blank(source)) {
		return;
	}
	if (source->tag == ast_type_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter(self, ast_at(source, i), dest);
		}
		return;
	}
	assert(source->tag == ast_type_parameter ||
		   source->tag == ast_type_in_parameter ||
		   source->tag == ast_type_out_parameter);
	ast* arule_list = ast_first(source);
	il_type_parameter* iltypeparam = il_type_parameter_new(source->u.string_value);
	if (source->tag == ast_type_in_parameter) iltypeparam->kind = il_type_parameter_kind_in;
	if (source->tag == ast_type_out_parameter) iltypeparam->kind = il_type_parameter_kind_out;
	vector_push(dest, iltypeparam);
	//制約があるならそれも設定
	if (!ast_is_blank(arule_list) &&
		arule_list->tag == ast_type_parameter_rule_list) {
		CLIL_type_parameter_rule(self, ast_first(arule_list), iltypeparam->rule_vec);
	}
}

void CLIL_type_argument(class_loader* self, ast* atype_args, vector* dest) {
	if(ast_is_blank(atype_args)) {
		return;
	}
	if(atype_args->tag == ast_typename_list) {
		for(int i=0; i<atype_args->child_count; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_type_argument(self, e, dest);
		}
	} else if(atype_args->tag == ast_typename) {
		il_type_argument* iltype_arg = il_type_argument_new();
		vector_push(dest, iltype_arg);
		CLIL_generic_cache(atype_args, iltype_arg->gcache);
	} else assert(false);
}


void CLIL_argument_list(class_loader* self, vector* list, ast* source) {
	if (source->tag == ast_argument_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_argument_list(self, list, ast_at(source, i));
		}
	} else if (source->tag == ast_argument) {
		ast* primary = ast_first(source);
		il_argument* ilarg = il_argument_new();
		ilarg->factor = class_loader_ilload_factor(self, primary);
		//il_argument_list_push(list, ilarg);
		vector_push(list, ilarg);
	}
}


static void CLIL_generic_cache_impl(ast* fqcn, generic_cache* dest) {
	fqcn_cache* body = dest->fqcn;
	//型引数を解析する
	if (fqcn->tag == ast_typename) {
		ast* atype_args = ast_second(fqcn);
		if (!ast_is_blank(atype_args)) {
			CLIL_generic_cache_inner(atype_args, dest);
		}
	}
	if (fqcn->tag == ast_typename) {
		CLIL_generic_cache_impl(ast_first(fqcn), dest);
		return;
	}
	if (fqcn->tag == ast_fqcn ||
		fqcn->tag == ast_fqcn_part_list) {
		if (fqcn->tag == ast_fqcn_part_list &&
			fqcn->child_count == 0) {
			//FIXME:もうちょっと高速に出来る
			//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
			fqcn->tag = ast_fqcn_class_name;
			body->name = text_strdup(fqcn->u.string_value);
			return;
		}
		for (int i = 0; i < fqcn->child_count; i++) {
			ast* c = ast_at(fqcn, i);
			CLIL_generic_cache_impl(c, dest);
		}
	} else {
		//FIXME:とりあえずここでタグを直してるけどast.cの時点でどうにかするべき
		vector_push(body->scope_vec, text_strdup(fqcn->u.string_value));
		fqcn->tag = ast_fqcn_part;
	}
}

static void CLIL_generic_cache_inner(ast* atype_args, generic_cache* dest) {
	if (atype_args->tag == ast_typename_list) {
		for (int i = 0; i < atype_args->child_count; i++) {
			ast* e = ast_at(atype_args, i);
			CLIL_generic_cache_inner(e, dest);
		}
	} else {
		generic_cache* newCache = generic_cache_new();
		CLIL_generic_cache(atype_args, newCache);
		vector_push(dest->type_args, newCache);
	}
}

static void CLIL_type_parameter_rule(class_loader* self, ast* source, vector* dest) {
	if (source->tag == ast_type_parameter_list) {
		for (int i = 0; i < source->child_count; i++) {
			CLIL_type_parameter_rule(self, ast_at(source, i), dest);
		}
	} else {
		if (source->tag == ast_typename) {
			il_type_parameter_rule* rule = il_type_parameter_rule_new();
			rule->tag = il_type_parameter_rule_polymorphic;
			rule->u.fqcn_ = generic_cache_new();
			CLIL_generic_cache(source, rule->u.fqcn_);
			vector_push(dest, rule);
		}
	}
}