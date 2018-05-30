#include "bc_void.h"
#include "../../bc_library_impl.h"

static type* gBCVoidType = NULL;

void bc_void_init() {
	namespace_* lang = namespace_lang();
	class_* voidClass = class_new_preload("Void");
	namespace_add_type(lang, type_wrap_class(voidClass));
}

type* bc_void_type() {
	if(gBCVoidType == NULL) {
		namespace_* lang = namespace_lang();
		gBCVoidType = namespace_get_type(lang, "Void");
	}
	return gBCVoidType;
}