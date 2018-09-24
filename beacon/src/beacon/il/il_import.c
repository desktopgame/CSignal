#include "il_import.h"
#include "../util/text.h"
#include <stdlib.h>
#include <assert.h>
#include "../util/mem.h"

il_import* il_import_new(string_view pathv) {
	il_import* ret = (il_import*)MEM_MALLOC(sizeof(il_import));
	ret->pathv = pathv;
	return ret;
}

void il_import_delete(il_import* self) {
	if(self == NULL) {
		return;
	}
	MEM_FREE(self);
}