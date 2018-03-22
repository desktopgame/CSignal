#include "il_type_argument.h"
#include "../util/mem.h"
#include "../util/text.h"

il_type_argument* il_type_argument_new() {
	il_type_argument* ret = (il_type_argument*)MEM_MALLOC(sizeof(il_type_argument));
	ret->gcache = generic_cache_new();
	return ret;
}

void il_type_argument_print(vector* iltype_args) {
	if(iltype_args->length == 0) {
		return;
	}
	text_printf("<");
	for(int i=0; i<iltype_args->length; i++) {
		il_type_argument* e = (il_type_argument*)vector_at(iltype_args, i);
		generic_cache_print(e->gcache);
		if(i != iltype_args->length - 1) {
			text_printf(",");
		}
	}
	text_printf("<");
}

void il_type_argument_delete(il_type_argument* self) {
	generic_cache_delete(self->gcache);
	MEM_FREE(self);
}