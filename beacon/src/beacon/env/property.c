#include "property.h"
#include "../util/mem.h"

property* property_malloc(string_view namev, const char* filename, int lineno) {
	property* ret = mem_malloc(sizeof(property), filename, lineno);
	ret->namev = namev;
	ret->gtype = NULL;
	ret->parent = NULL;
	ret->set = property_body_new(property_set_T);
	ret->get = property_body_new(property_get_T);
	ret->is_short = false;
	ret->source_ref = NULL;
	ret->set->parent = ret;
	ret->get->parent = ret;
	return ret;
}
void property_delete(property* self) {
	property_body_delete(self->set);
	property_body_delete(self->get);
	MEM_FREE(self);
}
