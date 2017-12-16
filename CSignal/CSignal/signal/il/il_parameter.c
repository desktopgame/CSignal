#include "il_parameter.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/text.h"

il_parameter * il_parameter_new(const char * name) {
	il_parameter* ret = (il_parameter*)malloc(sizeof(il_parameter));
	ret->name = text_strdup(name);
	ret->param_type = il_param_type_default;
	ret->type = NULL;
	return ret;
}

void il_parameter_dump(il_parameter * self, int depth) {
	text_putindent(depth);
	printf("parameter %s %s", self->type->name, self->name);
	text_putline();
}

void il_parameter_delete(il_parameter * self) {
	if (self == NULL) {
		return;
	}
	free(self->name);
	il_type_delete(self->type);
	free(self);
}
