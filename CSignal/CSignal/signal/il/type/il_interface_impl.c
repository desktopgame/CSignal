#include "il_interface_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../il_method.h"
#include "../il_type_parameter.h"

//proto
static void il_interface_fqcn_delete(vector_item item);
static void il_interface_method_delete(vector_item item);

il_type * il_type_wrap_interface(il_interface * self) {
	il_type* ret = il_type_new();
	ret->tag = iltype_interface;
	ret->u.interface_ = self;
	return ret;
}

il_interface * il_interface_new(const char * name) {
	il_interface* ret = (il_interface*)MEM_MALLOC(sizeof(il_interface));
	ret->extends_list = vector_new();
	ret->method_list = vector_new();
	ret->name = text_strdup(name);
	ret->type_parameter_list = vector_new();
	return ret;
}

void il_interface_add_method(il_interface * self, il_method * method) {
	vector_push(self->method_list, method);
}

void il_interface_dump(il_interface * self, int depth) {
	text_putindent(depth);
	text_printf("interface %s", self->name);
	il_type_parameter_list_print(self->type_parameter_list);
	text_putline();
	//継承するインターフェイスの一覧を出力
	for (int i = 0; i < self->extends_list->length; i++) {
		fqcn_cache* e = (fqcn_cache*)vector_at(self->extends_list, i);
		fqcn_cache_dump(e, depth + 1);
	}

	for (int i = 0; i < self->method_list->length; i++) {
		vector_item e = vector_at(self->method_list, i);
		il_method* ilm = (il_method*)e;
		il_method_dump(ilm, depth + 1);
	}
}

void il_interface_delete(il_interface * self) {
	vector_delete(self->extends_list, il_interface_fqcn_delete);
	vector_delete(self->method_list, il_interface_method_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private 
static void il_interface_fqcn_delete(vector_item item) {
	fqcn_cache* e = (fqcn_cache*)item;
	fqcn_cache_delete(e);
}

static void il_interface_method_delete(vector_item item) {
	il_method* e = (il_method*)item;
	il_method_delete(e);
}