#include "il_function.h"
#include "../env/fqcn_cache.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "il_parameter.h"
#include "il_stmt_interface.h"
#include <stdio.h>

//proto
static void il_function_parameter_delete(vector_item item);
static void il_function_stmt_delete(vector_item item);

il_function * il_function_new(const char * name) {
	il_function* ret = (il_function*)MEM_MALLOC(sizeof(il_function));
	ret->name = text_strdup(name);
	ret->parameter_list = vector_new();
	ret->statement_list = vector_new();
	ret->return_fqcn = fqcn_cache_new();
	return ret;
}

void il_function_dump(il_function * self, int depth) {
	text_putindent(depth);
	printf("function %s -> ", self->name);
	fqcn_cache_print(self->return_fqcn);
	text_putline();
	for (int i = 0; i < self->parameter_list->length; i++) {
		vector_item e = vector_at(self->parameter_list, i);
		il_parameter* p = (il_parameter*)e;
		il_parameter_dump(p, depth + 1);
	}
	for (int i = 0; i < self->statement_list->length; i++) {
		vector_item e = vector_at(self->statement_list, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
	text_putindent(depth);
	printf("function end");
	text_putline();
}

void il_function_delete(il_function * self) {
	vector_delete(self->parameter_list, il_function_parameter_delete);
	vector_delete(self->statement_list, il_function_stmt_delete);
	fqcn_cache_delete(self->return_fqcn);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_function_parameter_delete(vector_item item) {
	il_parameter* e = (il_parameter*)item;
	il_parameter_delete(e);
}

static void il_function_stmt_delete(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}