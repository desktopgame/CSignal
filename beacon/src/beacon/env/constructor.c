#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../vm/vm.h"
#include "../vm/frame.h"
#include "parameter.h"
#include "type_interface.h"
#include "object.h"
#include "generic_type.h"

//proto
static void constructor_parameter_delete(vector_item item);

constructor * constructor_new() {
	constructor* ret = (constructor*)MEM_MALLOC(sizeof(constructor));
	ret->parent = NULL;
	ret->env = NULL;
	ret->parameter_list = vector_new();
	ret->access = access_public_T;
	return ret;
}

object * constructor_new_instance(constructor * self, vector * args, frame * parent) {
	frame* sub = frame_sub(parent);
	for (int i = 0; i < args->length; i++) {
		vector_push(sub->value_stack, vector_at(args, i));
	}
	vm_execute(sub, self->env);
	object* ret = vector_pop(sub->value_stack);
	frame_delete(sub);
	return ret;
}

void constructor_delete(constructor * self) {
	enviroment_delete(self->env);
	vector_delete(self->parameter_list, constructor_parameter_delete);
	MEM_FREE(self);
}

//private
static void constructor_parameter_delete(vector_item item) {
	parameter* e = (parameter*)item;
	parameter_delete(e);
}