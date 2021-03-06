#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../il_type_argument.h"

static void il_factor_static_delete_typeargs(vector_item item);

il_factor_variable_static* il_factor_variable_static_new() {
	il_factor_variable_static* ret = (il_factor_variable_static*)MEM_MALLOC(sizeof(il_factor_variable_static));
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_variable_static_generate(il_factor_variable_static* self, enviroment* env, call_context* cctx) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void il_factor_variable_static_load(il_factor_variable_static * self, enviroment * env, call_context* cctx) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

generic_type* il_factor_variable_static_eval(il_factor_variable_static * self, enviroment * env, call_context* cctx) {
	return NULL;
}

char* il_factor_variable_static_tostr(il_factor_variable_static * self, enviroment * env) {
	return NULL;
}

void il_factor_variable_static_delete(il_factor_variable_static* self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, il_factor_static_delete_typeargs);
	MEM_FREE(self);
}
//private
static void il_factor_static_delete_typeargs(vector_item item) {
	il_type_argument* e = (il_type_argument*)item;
	il_type_argument_delete(e);
}