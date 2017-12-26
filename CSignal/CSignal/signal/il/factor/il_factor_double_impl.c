#include "il_factor_double_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include "../../util/text.h"
#include "../../vm/opcode_buf.h"

il_factor * il_factor_wrap_double(il_factor_double * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_double;
	ret->u.double_ = self;
	return ret;
}

il_factor_double * il_factor_double_new(double d) {
	il_factor_double* ret = (il_factor_double*)malloc(sizeof(il_factor_double));
	ret->value = d;
	return ret;
}

void il_factor_double_dump(il_factor_double * self, int depth) {
	text_putindent(depth);
	printf("Dobule %f", self->value);
	text_putline();
}

void il_factor_double_generate(il_factor_double * self, opcode_buf * buf) {
}

void il_factor_double_delete(il_factor_double * self) {
	free(self);
}
