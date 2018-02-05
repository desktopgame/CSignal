#include "constructor.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../vm/enviroment.h"
#include "../vm/vm.h"
#include "parameter.h"
#include "type_interface.h"
#include "object.h"

constructor * constructor_new() {
	constructor* ret = (constructor*)MEM_MALLOC(sizeof(constructor));
	ret->parent = NULL;
	ret->env = NULL;
	ret->parameter_list = vector_new();
	ret->access = access_public;
	return ret;
}

void constructor_dump(constructor * self, int depth) {
	text_putindent(depth);
	access_print(self->access);
	printf(" constructor");
	printf("(");
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		parameter* p = (parameter*)e;
		printf("%s %s", type_name(p->type), p->name);
		if ((i + 1) < self->parameter_list->length) {
			printf(" ");
		}
	}
	printf(")");
	text_putline();
	opcode_buf_dump(self->env->buf, depth + 1);
}

object * constructor_new_instance(constructor * self, vector * args, vm * parent) {
	vm* sub = vm_sub(parent);
	for (int i = 0; i < args->length; i++) {
		vector_push(sub->value_stack, vector_at(args, i));
	}
	vm_execute(sub, self->env);
	object* ret = vector_pop(sub->value_stack);
	vm_delete(sub);
	return ret;
}

void constructor_delete(constructor * self) {
}
