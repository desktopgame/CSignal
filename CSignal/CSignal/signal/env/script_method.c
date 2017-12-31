#include "script_method.h"
#include <stdlib.h>
#include "../vm/vm.h"
#include "method.h"
#include "../util/mem.h"

script_method * script_method_new() {
	script_method* ret = (script_method*)MEM_MALLOC(sizeof(script_method));
	//ret->source = vector_new();
	ret->env = NULL;
	return ret;
}

void script_method_execute(script_method * self, method* parent, vm * vm, enviroment* env) {
}

void script_method_delete(script_method * self) {
	enviroment_delete(self->env);
//	vector_delete(self->source, vector_deleter_null);
	MEM_FREE(self);
}
