#include "il_factor_logic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/type_impl.h"

static opcode operator_to_iopcode(operator_type type);
static opcode operator_to_bopcode(operator_type type);

il_factor_logic_op* il_factor_logic_op_new(operator_type type) {
	il_factor_logic_op* ret = (il_factor_logic_op*)MEM_MALLOC(sizeof(il_factor_logic_op));
	ret->type = type;
	ret->parent = NULL;
	ret->operator_index = -1;
	return ret;
}

void il_factor_logic_op_dump(il_factor_logic_op* self, int depth) {
	io_printi(depth);
	operator_fprintf(stdout, self->type);
	io_println();
}

generic_type* il_factor_logic_op_eval(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_INT);
	} else if(il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
		return TYPE2GENERIC(TYPE_BOOL);
	} else {
		generic_type* lgtype = il_factor_eval(self->parent->left, env, cctx);
		//プリミティブ型同士でないのに
		//演算子オーバーロードもない
		if(self->operator_index == -1) {
			bc_error_throw(
				bcerror_undefined_logic_operator_T,
				operator_tostring(self->type)
			);
			return NULL;
		}
		operator_overload* operator_ov = class_get_operator_overload(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->operator_index);
		return il_factor_binary_op_apply(self->parent, operator_ov->return_gtype, env, cctx);
	}
}

void il_factor_logic_op_generate(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(self->operator_index == -1) {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		if(il_factor_binary_op_int_int(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_iopcode(self->type));
		} else if(il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
			opcode_buf_add(env->buf, (vector_item)operator_to_bopcode(self->type));
		} else {
			assert(false);
		}
	} else {
		il_factor_generate(self->parent->right, env, cctx);
		il_factor_generate(self->parent->left, env, cctx);
		opcode_buf_add(env->buf, op_invokeoperator);
		opcode_buf_add(env->buf, self->operator_index);
	}
}

void il_factor_logic_op_load(il_factor_logic_op* self, enviroment* env, call_context* cctx) {
	if(!il_factor_binary_op_int_int(self->parent, env, cctx) &&
	   !il_factor_binary_op_bool_bool(self->parent, env, cctx)) {
	self->operator_index = il_factor_binary_op_index(self->parent, env, cctx);
	}
}

void il_factor_logic_op_delete(il_factor_logic_op* self) {
	MEM_FREE(self);
}

char* il_factor_logic_op_tostr(il_factor_logic_op* self, enviroment* env) {
	return il_factor_binary_op_tostr_simple(self->parent, env);
}
//static
static opcode operator_to_iopcode(operator_type type) {
	switch(type) {
		case operator_bit_or_T: return op_ibit_or;
		case operator_bit_and_T: return op_ibit_and;
		case operator_logic_or_T: return op_ilogic_or;
		case operator_logic_and_T: return op_ilogic_and;
	}
	assert(false);
}

static opcode operator_to_bopcode(operator_type type) {
	switch(type) {
		case operator_bit_or_T: return op_bbit_or;
		case operator_bit_and_T: return op_bbit_and;
		case operator_logic_or_T: return op_blogic_or;
		case operator_logic_and_T: return op_blogic_and;
	}
	assert(false);
}