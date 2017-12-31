#include "il_factor_variable_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../env/class.h"
#include "../../util/mem.h"

//proto
static void il_factor_variable_check(il_factor_variable* self, enviroment* env);

il_factor * il_factor_wrap_variable(il_factor_variable * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_variable;
	ret->u.variable_ = self;
	return ret;
}

il_factor_variable * il_factor_variable_new(const char * name) {
	il_factor_variable* ret = (il_factor_variable*)MEM_MALLOC(sizeof(il_factor_variable));
	ret->name = text_strdup(name);
	ret->index = -1;
	return ret;
}

void il_factor_variable_dump(il_factor_variable * self, int depth) {
	text_putindent(depth);
	printf("variable %s", self->name);
	text_putline();
}

void il_factor_variable_generate(il_factor_variable * self, enviroment* env) {
	il_factor_variable_check(self, env);
}

class_ * il_factor_variable_eval(il_factor_variable * self, enviroment * env) {
	il_factor_variable_check(self, env);
	return NULL;
}

void il_factor_variable_delete(il_factor_variable * self) {
	MEM_FREE(self->name);
	MEM_FREE(self);
}

//private
static void il_factor_variable_check(il_factor_variable* self, enviroment* env) {
	if (self->index != -1) {
		return;
	}
	self->index = symbol_table_add(env->sym_table, self->name);
}