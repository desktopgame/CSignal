#include "il_factor_null_impl.h"
#include "../../util/text.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static generic_type* gSelf = NULL;

void il_factor_null_dump(void * empty, int depth) {
	io_printi(depth);
	printf("null");
	io_println();
}

void il_factor_null_generate(void * empty, enviroment * env, call_context* cctx) {
	opcode_buf_add(env->buf, op_null);
}

void il_factor_null_load(void * empty, enviroment * env, call_context* cctx) {
}

generic_type* il_factor_null_eval(void * empty, enviroment * env, call_context* cctx) {
	if(gSelf == NULL) {
		gSelf =  generic_type_new(TYPE_NULL);
	}
	return gSelf;
}

char* il_factor_null_tostr(void* empty, enviroment* env) {
	return text_strdup("null");
}