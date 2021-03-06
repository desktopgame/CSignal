#include "il_factor_char_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/namespace.h"
#include "../../env/type_impl.h"
#include "../../util/mem.h"

il_factor * il_factor_wrap_char(il_factor_char * self) {
	il_factor* ret = il_factor_new(ilfactor_char_T);
	ret->u.char_ = self;
	return ret;
}

il_factor_char * il_factor_char_new(char c) {
	il_factor_char* ret = (il_factor_char*)MEM_MALLOC(sizeof(il_factor_char));
	ret->value = c;
	return ret;
}

void il_factor_char_dump(il_factor_char * self, int depth) {
	io_printi(depth);
	printf("Char %c", self->value);
	io_println();
}

void il_factor_char_generate(il_factor_char * self, enviroment * env, call_context* cctx) {
	int index = enviroment_add_constant_char(env, self->value);
	opcode_buf_add(env->buf, op_cconst);
	opcode_buf_add(env->buf, index);
}

void il_factor_char_load(il_factor_char * self, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_char_eval(il_factor_char * self, enviroment * env, call_context* cctx) {
	return GENERIC_CHAR;
}

char* il_factor_char_tostr(il_factor_char* self, enviroment* env) {
	string_buffer* sb = string_buffer_new();
	string_buffer_append(sb, '\'');
	string_buffer_append(sb, self->value);
	string_buffer_append(sb, '\'');
	return string_buffer_release(sb);
}

void il_factor_char_delete(il_factor_char * self) {
	MEM_FREE(self);
}

il_factor_char* il_factor_cast_char_T(il_factor* fact) {
	assert(fact->type == ilfactor_char_T);
	return fact->u.char_;
}