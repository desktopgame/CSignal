#include "il_factor_bool_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include "../../env/type_impl.h"

il_factor * il_factor_wrap_bool(il_factor_bool * self) {
	il_factor* ret = il_factor_new(ilfactor_bool_T);
	ret->u.bool_ = self;
	return ret;
}

il_factor_bool * il_factor_bool_new(bool b) {
	il_factor_bool* ret = (il_factor_bool*)MEM_MALLOC(sizeof(il_factor_bool));
	ret->a = b;
	return ret;
}

void il_factor_bool_dump(il_factor_bool * self, int depth) {
	io_printi(depth);
	printf(self->a ? "true" : "false");
	io_println();
}

void il_factor_bool_generate(il_factor_bool * self, enviroment * env, call_context* cctx) {
	if (self->a) {
		opcode_buf_add(env->buf, op_true);
	} else {
		opcode_buf_add(env->buf, op_false);
	}
}

generic_type* il_factor_bool_eval(il_factor_bool * self, enviroment * env, call_context* cctx) {
	return GENERIC_BOOL;
}

char* il_factor_bool_tostr(il_factor_bool* self, enviroment* env) {
	return text_strdup(self->a ? "true" : "false");
}

void il_factor_bool_delete(il_factor_bool * self) {
	MEM_FREE(self);
}

il_factor_bool* il_factor_cast_bool(il_factor* fact) {
	assert(fact->type == ilfactor_bool_T);
	return fact->u.bool_;
}