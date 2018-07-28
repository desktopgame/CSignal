#include "class_loader_ilload_factor_module_impl.h"
#include "../../il/il_factor_impl.h"
#include "../../util/mem.h"
#include "../class_loader.h"
#include "class_loader_ilload_type_module_impl.h"
#include <stdio.h>
//proto
static il_factor* CLIL_factorImpl(class_loader* self, ast* source);
static il_factor_bool* CLIL_true(class_loader* self, ast* source);
static il_factor_bool* CLIL_false(class_loader* self, ast* source);
static il_factor_cast* CLIL_cast(class_loader* self, ast* source);
static il_factor_unary_op* CLIL_unary(class_loader* self, ast* source, operator_type type);
static il_factor_binary_op* CLIL_binary(class_loader* self, ast* source, operator_type type);
static il_factor_explicit_unary_op* CLIL_explicit_unary(class_loader* self, ast* source, operator_type type);
static il_factor_explicit_binary_op* CLIL_explicit_binary(class_loader* self, ast* source, operator_type type);
static il_factor_assign_op* CLIL_assign(class_loader* self, ast* source);
static il_factor_assign_op* CLIL_assign_arithmetic(class_loader* self, ast* source, operator_type type);
static il_factor_variable* CLIL_variable(class_loader* self, ast* source);
static il_factor_new_instance* CLIL_new_instance(class_loader* self, ast* source);
static il_factor_as* CLIL_as(class_loader* self, ast* source);
static il_factor_inc* CLIL_inc(class_loader* self, ast* source);
static il_factor_dec* CLIL_dec(class_loader* self, ast* source);
static il_factor_call_op* CLIL_call_op(class_loader* self, ast* source);
static il_factor_member_op* CLIL_member_op(class_loader* self, ast* source);
static il_factor_instanceof* CLIL_instanceof(class_loader* self, ast* source);

il_factor* CLIL_factor(class_loader* self, ast* source) {
	il_factor* ret = CLIL_factorImpl(self, source);
	assert(source->lineno >= 0);
	ret->lineno = source->lineno;
	return ret;
}


//private
static il_factor* CLIL_factorImpl(class_loader* self, ast* source) {
	if (source->tag == ast_int) {
		return il_factor_wrap_int(il_factor_int_new(source->u.int_value));
	} else if (source->tag == ast_double) {
		return il_factor_wrap_double(il_factor_double_new(source->u.double_value));
	} else if (source->tag == ast_char) {
		return il_factor_wrap_char(il_factor_char_new(source->u.char_value));
	} else if (source->tag == ast_string) {
		return il_factor_wrap_string(il_factor_string_new(source->u.stringv_value));
	} else if (source->tag == ast_variable) {
		return il_factor_wrap_variable(CLIL_variable(self, source));
		//operator(+ - * / %)
	} else if (source->tag == ast_add) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_add));
	} else if (source->tag == ast_sub) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_sub));
	} else if (source->tag == ast_mul) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_mul));
	} else if (source->tag == ast_div) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_div));
	} else if (source->tag == ast_mod) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_mod));
		//operator(| || & &&)
	} else if (source->tag == ast_bit_or) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_bit_or));
	} else if (source->tag == ast_logic_or) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_logic_or));
	} else if (source->tag == ast_bit_and) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_bit_and));
	} else if (source->tag == ast_logic_and) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_logic_and));
	//^
	} else if(source->tag == ast_exc_or) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_excor));
	} else if(source->tag == ast_childa) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_childa));
	//<< >>
	} else if(source->tag == ast_lshift) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_lshift));
	} else if(source->tag == ast_rshift) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_rshift));
	//operator(== != > >= < <=)
	} else if (source->tag == ast_equal) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_eq));
	} else if (source->tag == ast_notequal) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_noteq));
	} else if (source->tag == ast_gt) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_gt));
	} else if (source->tag == ast_ge) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_ge));
	} else if (source->tag == ast_lt) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_lt));
	} else if (source->tag == ast_le) {
		return il_factor_wrap_binary(CLIL_binary(self, source, operator_le));
		//operator(= += -= *= /= %=)
	} else if (source->tag == ast_assign) {
		return il_factor_wrap_assign(CLIL_assign(self, source));
	} else if (source->tag == ast_add_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_add));
	} else if (source->tag == ast_sub_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_sub));
	} else if (source->tag == ast_mul_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_mul));
	} else if (source->tag == ast_div_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_div));
	} else if (source->tag == ast_mod_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_mod));
	//instanceof
	} else if(source->tag == ast_instanceof) {
		return il_factor_wrap_instanceof(CLIL_instanceof(self, source));
	//|= &=
	} else if(source->tag == ast_or_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_bit_or));
	} else if(source->tag == ast_and_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_bit_and));
	//<<= >>=
	} else if(source->tag == ast_lshift_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_lshift));
	} else if(source->tag == ast_rshift_assign) {
		return il_factor_wrap_assign(CLIL_assign_arithmetic(self, source, operator_rshift));
	//!-
	} else if (source->tag == ast_not) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_not));
	} else if (source->tag == ast_neg) {
		return il_factor_wrap_unary(CLIL_unary(self, source, operator_negative));
	} else if(source->tag == ast_explicit_uoperator) {
		return il_factor_wrap_explicit_unary_op(CLIL_explicit_unary(self, source, source->u.operator_value));
	} else if(source->tag == ast_explicit_bioperator) {
		return il_factor_wrap_explicit_binary_op(CLIL_explicit_binary(self, source, source->u.operator_value));
		//this super
	} else if (source->tag == ast_this) {
		il_factor* ret = il_factor_new(ilfactor_this);
		il_factor_this* th = il_factor_this_new();
		ret->u.this_ = th;
		return ret;
	} else if (source->tag == ast_super) {
		il_factor* ret = il_factor_new(ilfactor_super);
		il_factor_super* sp = il_factor_super_new();
		ret->u.super_ = sp;
		return ret;
	} else if (source->tag == ast_new_instance) {
		return il_factor_wrap_new_instance(CLIL_new_instance(self, source));
	} else if (source->tag == ast_cast) {
		return il_factor_wrap_cast(CLIL_cast(self, source));
	} else if (source->tag == ast_true) {
		return il_factor_wrap_bool(CLIL_true(self, source));
	} else if (source->tag == ast_false) {
		return il_factor_wrap_bool(CLIL_false(self, source));
	} else if (source->tag == ast_null) {
		il_factor* ret = il_factor_new(ilfactor_null);
		ret->u.null_ = NULL;
		return ret;
	} else if (source->tag == ast_as) {
		return il_factor_wrap_as(CLIL_as(self, source));
	} else if (source->tag == ast_pre_inc ||
			   source->tag == ast_post_inc) {
		return il_factor_wrap_inc(CLIL_inc(self, source));
	} else if (source->tag == ast_pre_dec ||
			   source->tag == ast_post_dec) {
		return il_factor_wrap_dec(CLIL_dec(self, source));
	} else if(source->tag == ast_op_call) {
		return il_factor_wrap_call_op(CLIL_call_op(self, source));
	} else if(source->tag == ast_field_access) {
		return il_factor_wrap_member_op(CLIL_member_op(self, source));
	}
	il_factor* fact = il_factor_new(ilfactor_unary_op);
	return fact;
}

static il_factor_bool * CLIL_true(class_loader * self, ast * source) {
	return il_factor_bool_new(true);
}

static il_factor_bool * CLIL_false(class_loader * self, ast * source) {
	return il_factor_bool_new(false);
}

static il_factor_cast * CLIL_cast(class_loader * self, ast * source) {
	ast* atypename = ast_first(source);
	ast* afact = ast_second(source);
	il_factor_cast* ret = il_factor_cast_new(CLIL_factor(self, afact));
	CLIL_generic_cache(ast_first(atypename), ret->fqcn);
	return ret;
}

static il_factor_unary_op* CLIL_unary(class_loader* self, ast* source, operator_type type) {
	il_factor_unary_op* ret = il_factor_unary_op_new(type);
	ast* a = ast_first(source);
	ret->a = CLIL_factor(self, a);
	return ret;
}

static il_factor_binary_op* CLIL_binary(class_loader* self, ast* source, operator_type type) {
	il_factor_binary_op* ret = il_factor_binary_op_new(type);
	ast* aleft = ast_first(source);
	ast* aright = ast_second(source);
	ret->left = CLIL_factor(self, aleft);
	ret->right = CLIL_factor(self, aright);
	return ret;
}

static il_factor_explicit_unary_op* CLIL_explicit_unary(class_loader* self, ast* source, operator_type type) {
	il_factor_explicit_unary_op* ret = il_factor_explicit_unary_op_new(type);
	ret->receiver = CLIL_factor(self, ast_first(source));
	return ret;
}

static il_factor_explicit_binary_op* CLIL_explicit_binary(class_loader* self, ast* source, operator_type type) {
	il_factor_explicit_binary_op* ret = il_factor_explicit_binary_op_new(type);
	ret->receiver = CLIL_factor(self, ast_first(source));
	ret->arg = CLIL_factor(self, ast_second(source));
	return ret;
}

static il_factor_assign_op* CLIL_assign(class_loader* self, ast* source) {
	il_factor_assign_op* ret = il_factor_assign_op_new();
	ast* aleft = ast_first(source);
	ast* aright = ast_second(source);
	ret->left = CLIL_factor(self, aleft);
	ret->right = CLIL_factor(self, aright);
	return ret;
}

static il_factor_assign_op* CLIL_assign_arithmetic(class_loader* self, ast* source, operator_type type) {
	//a += b
	il_factor_assign_op* ret = il_factor_assign_op_new();
	il_factor_binary_op* bin = il_factor_binary_op_new(type);
	ast* aleft = ast_first(source);
	ast* aright = ast_second(source);
	bin->left = CLIL_factor(self, aleft);
	bin->right = CLIL_factor(self, aright);
	ret->left = CLIL_factor(self, aleft);
	ret->right = il_factor_wrap_binary(bin);
	ret->right->lineno = aright->lineno;
	return ret;
}

static il_factor_variable* CLIL_variable(class_loader* self, ast* source) {
	ast* afqcn = ast_first(source);
	ast* atype_args = ast_second(source);

	il_factor_variable* ilvar = il_factor_variable_new();
	CLIL_fqcn_cache(afqcn, ilvar->fqcn);
	CLIL_type_argument(self, atype_args, ilvar->type_args);
	return ilvar;
}

static il_factor_new_instance* CLIL_new_instance(class_loader* self, ast* source) {
	assert(source->tag == ast_new_instance);
	ast* afqcn = ast_first(source);
	ast* atype_args = ast_second(source);
	ast* aargs = ast_at(source, 2);
	il_factor_new_instance* ret = il_factor_new_instance_new();
	CLIL_fqcn_cache(afqcn, ret->fqcnc);
	CLIL_type_argument(self, atype_args, ret->type_args);
	CLIL_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_as* CLIL_as(class_loader* self, ast* source) {
	il_factor_as* ret = il_factor_as_new();
	ret->fact = CLIL_factor(self, ast_first(source));
	CLIL_generic_cache(ast_second(source), ret->fqcn);
	return ret;
}

static il_factor_inc * CLIL_inc(class_loader * self, ast * source) {
	assert(source->tag == ast_pre_inc ||
		   source->tag == ast_post_inc);
	fix_type type = (source->tag == ast_pre_inc) ? fixtype_pre : fixtype_post;
	il_factor_inc* ret = il_factor_inc_new(type);
	ast* afact = ast_first(source);
	ret->fact = CLIL_factor(self, afact);
	ret->type = type;
	return ret;
}

static il_factor_dec * CLIL_dec(class_loader * self, ast * source) {
	assert(source->tag == ast_pre_dec ||
		   source->tag == ast_post_dec);
	fix_type type = (source->tag == ast_pre_dec) ? fixtype_pre : fixtype_post;
	il_factor_dec* ret = il_factor_dec_new(type);
	ast* afact = ast_first(source);
	ret->fact = CLIL_factor(self, afact);
	ret->type = type;
	return ret;
}

static il_factor_call_op* CLIL_call_op(class_loader* self, ast* source) {
	assert(source->tag == ast_op_call);
	il_factor_call_op* ret = il_factor_call_op_new();
	ast* afact = ast_first(source);
	ast* aargs = ast_second(source);
	ret->receiver = CLIL_factor(self, afact);
	CLIL_argument_list(self, ret->argument_list, aargs);
	return ret;
}

static il_factor_member_op* CLIL_member_op(class_loader* self, ast* source) {
	assert(source->tag == ast_field_access);
	ast* afact = ast_first(source);
	ast* aname = ast_second(source);
	ast* atype_args = ast_at(source, 2);
	il_factor_member_op* ret = il_factor_member_op_new(aname->u.stringv_value);
	ret->fact = CLIL_factor(self, afact);
	CLIL_type_argument(self, atype_args, ret->type_args);
	return ret;
}

static il_factor_instanceof* CLIL_instanceof(class_loader* self, ast* source) {
	assert(source->tag == ast_instanceof);
	ast* afact = ast_first(source);
	ast* atype = ast_second(source);
	il_factor_instanceof* ret = il_factor_instanceof_new();
	ret->fact = CLIL_factor(self, afact);
	CLIL_generic_cache(atype, ret->gcache);
	return ret;
}