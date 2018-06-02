#include "il_factor_variable_static_impl.h"
#include "../../../util/mem.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"

il_factor_variable_static* il_factor_variable_static_new() {
	il_factor_variable_static* ret = (il_factor_variable_static*)MEM_MALLOC(sizeof(il_factor_variable_static));
	ret->fqcn = NULL;
	ret->type_args = NULL;
	return ret;
}

void il_factor_variable_static_generate(il_factor_variable_static* self, enviroment* env) {
	//FATAL("not implemented, because must be wrapped by call operator");
}

void il_factor_variable_static_load(il_factor_variable_static * self, enviroment * env) {
//	FATAL("not implemented, because must be wrapped by call operator");
}

generic_type* il_factor_variable_static_eval(il_factor_variable_static * self, enviroment * env) {
	//FATAL("not implemented, because must be wrapped by call operator");
	return NULL;
}

char* il_factor_variable_static_tostr(il_factor_variable_static * self, enviroment * env) {
	return NULL;
}

void il_factor_variable_static_delete(il_factor_variable_static* self) {
	fqcn_cache_delete(self->fqcn);
	vector_delete(self->type_args, vector_deleter_null);
	MEM_FREE(self);
}