#include "il_type_interface.h"
#include "../util/mem.h"
#include "type/il_class_impl.h"
#include "type/il_interface_impl.h"

il_type * il_type_new() {
	il_type* ret = (il_type*)MEM_MALLOC(sizeof(il_type));
	ret->tag = iltype_class;
	return ret;
}

vector * il_type_method_vec(il_type * self) {
	if (self->tag == iltype_class) {
		return self->u.class_->method_list;
	} else if (self->tag == iltype_interface) {
		return self->u.interface_->method_list;
	}
	return NULL;
}

vector * il_type_smethod_vec(il_type * self) {
	if (self->tag == iltype_class) {
		return self->u.class_->smethod_list;
	} else if (self->tag == iltype_interface) {
		//return self->u.interface_->smethod_list;
		return NULL;
	}
	return NULL;
}

void il_type_dump(il_type * self, int depth) {
	if (self->tag == iltype_class) {
		il_class_dump(self->u.class_, depth);
	} else if (self->tag == iltype_interface) {
		il_interface_dump(self->u.interface_, depth);
	}
}

void il_type_delete(il_type * self) {
	if (self->tag == iltype_class) {
		il_class_delete(self->u.class_);
	} else if (self->tag == iltype_interface) {
		il_interface_delete(self->u.interface_);
	}
	MEM_FREE(self);
}