#include "ast_new_factor.h"
#include "ast.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/text.h"

ast * ast_new_true() {
	return ast_new(ast_true);
}

ast * ast_new_false() {
	return ast_new(ast_false);
}

ast * ast_new_null() {
	return ast_new(ast_null);
}

ast * ast_new_as(ast * afact, ast * atypename) {
	ast* ret = ast_new(ast_as);
	ast_push(ret, afact);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_cast(ast * atypename, ast * afact) {
	ast* ret = ast_new(ast_cast);
	ast_push(ret, atypename);
	ast_push(ret, afact);
	return ret;
}

ast * ast_new_pre_inc(ast * a) {
	ast* ret = ast_new(ast_pre_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_pre_dec(ast * a) {
	ast* ret = ast_new(ast_pre_dec);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_inc(ast * a) {
	ast* ret = ast_new(ast_post_inc);
	ast_push(ret, a);
	return ret;
}

ast * ast_new_post_dec(ast * a) {
	ast* ret = ast_new(ast_post_dec);
	ast_push(ret, a);
	return ret;
}

ast* ast_new_name_reference(ast* atypename) {
	ast* ret = ast_new(ast_name_reference);
	ast_push(ret, atypename);
	return ret;
}

ast * ast_new_variable(ast* a, ast* atype_args) {
	assert(a->tag == ast_fqcn_class_name);
	ast* ret = ast_new(ast_variable);
	ret->u.string_value = text_strdup(a->u.string_value);
	ast_push(ret, a);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_variable_fromstr(char * str, ast* atype_args) {
	ast* ret = ast_new(ast_variable);
	ret->u.string_value = (str);
	ast_push(ret, atype_args);
	//ast_push(ret, a);
	return ret;
}

ast* ast_new_op_call(ast* areceiver, ast* aargs) {
	ast* ret = ast_new(ast_op_call);
	ast_push(ret, areceiver);
	ast_push(ret, aargs);
	return ret;
}

ast * ast_new_call(const char * name, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_call);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_invoke(ast * receiver, const char* name, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, receiver);
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_static_invoke(ast * fqcn, const char * name, ast* atype_args, ast * argument_list) {
	ast* ret = ast_new(ast_static_invoke);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, fqcn);
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	ast_push(ret, argument_list);
	return ret;
}

ast * ast_new_this() {
	return ast_new(ast_this);
}

ast * ast_new_super() {
	return ast_new(ast_super);
}

ast * ast_new_field_access(ast * afact, char * name, ast* atype_args) {
	ast* ret = ast_new(ast_field_access);
	ast* aname = ast_new(ast_identifier);
	aname->u.string_value = name;
	ast_push(ret, afact);
	ast_push(ret, aname);
	ast_push(ret, atype_args);
	return ret;
}

ast * ast_new_field_access_fqcn(ast * fqcn, char * name, ast* atype_args) {
	//	assert(fqcn->tag != ast_fqcn_part_list);
	if (fqcn->tag == ast_fqcn_part ||
		fqcn->tag == ast_fqcn_class_name) {
		//この時点では point.a のようなアクセスを
		//インスタンス point のフィールド a へのアクセスなのか
		//クラス Point の静的フィールド a へのアクセスなのか判別出来ない
		//なので、とりあえずフィールドアクセスとして扱う
		//この判別は il_factor_field_access で行う。
		ast* ret = ast_new(ast_field_access);
		ast* avar = ast_new(ast_variable);
		ast* aname = ast_new(ast_identifier);
		avar->u.string_value = text_strdup(fqcn->u.string_value);
		aname->u.string_value = name;
		ast_push(ret, avar);
		ast_push(ret, aname);
		ast_push(ret, atype_args);
		ast_push(ret, fqcn);
		return ret;
	} else if (fqcn->tag == ast_fqcn || fqcn->tag == ast_fqcn_part_list) {
		//こっちの場合は静的フィールドへのアクセスと断定できる
		ast* ret = ast_new(ast_static_field_access);
		ast* aname = ast_new(ast_identifier);
		aname->u.string_value = name;
		ast_push(ret, fqcn);
		ast_push(ret, aname);
		ast_push(ret, atype_args);
		return ret;
	}
	return NULL;
}

ast * ast_new_new_instance(ast * afqcn, ast * argument_list) {
	ast* ret = ast_new(ast_new_instance);
	ast_push(ret, afqcn);
	ast_push(ret, argument_list);
	return ret;
}