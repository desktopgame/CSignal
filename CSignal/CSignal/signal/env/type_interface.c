#include "type_interface.h"
#include "../util/mem.h"
#include "type_impl.h"
#include "field.h"
#include "method.h"
#include <assert.h>

type * type_new() {
	type* ret = (type*)MEM_MALLOC(sizeof(type));
	ret->tag = type_class;
	ret->location = NULL;
	ret->absolute_index = -1;
	return ret;
}

char * type_name(type * self) {
	//assert(self->tag == type_class);
	if (self->tag == type_class) {
		return self->u.class_->name;
	} else if (self->tag == type_interface) {
		return self->u.interface_->name;
	}
	return NULL;
}

void type_add_field(type* self, field * f) {
	assert(self->tag == type_class);
	class_add_field(self->u.class_, f);
}

void type_add_method(type* self, method * m) {
	if (self->tag == type_class) {
		class_add_method(self->u.class_, m);
	} else if (self->tag == type_interface) {
		interface_add_method(self->u.interface_, m);
	}
}

method * type_find_method(type * self, const char * name, vector * args, enviroment * env, il_load_cache* cache, int * outIndex) {
	if (self->tag == type_class) {
		return class_find_method(self->u.class_, name, args, env, cache, outIndex);
	} else if (self->tag == type_interface) {
		return interface_find_method(self->u.interface_, name, args, env, cache, outIndex);
	}
	return NULL;
}

vtable * type_vtable(type * self) {
	if (self->tag == type_class) {
		class_create_vtable(self->u.class_);
		return self->u.class_->vt;
	} else if (self->tag == type_interface) {
		return self->u.interface_->vt;
	}
	return NULL;
}

void type_dump(type * self, int depth) {
	if (self->tag == type_class) {
		class_dump(self->u.class_, depth);
	} else if (self->tag == type_interface) {
		interface_dump(self->u.interface_, depth);
	}
}

int type_distance(type * a, type * b) {
	if (a == b) {
		return 0;
	}
	if (a->tag == type_class &&
		b->tag == type_class) {
		int dist = class_distance(a->u.class_, b->u.class_);
		return dist;
	}
	return -1;
}

bool type_castable(type * self, type * other) {
	if (self->tag != other->tag) {
		return false;
	}
	if (self->tag == type_class) {
		return class_castable(self->u.class_, other->u.class_);
	}
	return false;
}

void type_unlink(type * self) {
	if (self->tag == type_class) {
		class_unlink(self->u.class_);
	} else if (self->tag == type_interface) {
		interface_unlink(self->u.interface_);
	}
}

void type_delete(type * self) {
	if (self->tag == type_class) {
		class_delete(self->u.class_);
	} else if (self->tag == type_interface) {
		interface_delete(self->u.interface_);
	}
	MEM_FREE(self);
}
