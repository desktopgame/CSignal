#include "fqcn_cache.h"
#include "../util/mem.h"
#include "namespace.h"
#include "type_interface.h"
#include "type_impl.h"
#include <assert.h>

//proto
static type * fqcn_type_impl(fqcn_cache * self, namespace_* current);

fqcn_cache * fqcn_cache_new() {
	fqcn_cache* ret = (fqcn_cache*)MEM_MALLOC(sizeof(fqcn_cache));
	ret->scope_vec = vector_new();
	ret->name = NULL;
	return ret;
}

void fqcn_cache_dump(fqcn_cache * self, int depth) {
	text_putindent(depth);
	text_printf("type %s", self->name);
	text_putline();
	//X::C.call() のような呼び出しなら
	if (self->scope_vec->length > 0) {
		text_putindent(depth);
		text_printf("scope");
		text_putline();
		for (int i = 0; i < self->scope_vec->length; i++) {
			char* e = (char*)vector_at(self->scope_vec, i);
			text_putindent(depth + 1);
			text_printf("%s", e);
			text_putline();
		}
	}
}

void fqcn_cache_print(fqcn_cache * self) {
	if (self->scope_vec->length == 0) {
		text_printf("%s", self->name);
	} else {
		for (int i = 0; i < self->scope_vec->length; i++) {
			text_printf("%s", (char*)vector_at(self->scope_vec, i));
			text_printf("::");
		}
		text_printf("%s", self->name);
	}
}

namespace_ * fqcn_scope(fqcn_cache * self, namespace_* current) {
	if (self->scope_vec->length == 0) {
		return current;
	}
	namespace_* top = NULL;
	for (int i = 0; i < self->scope_vec->length; i++) {
		char* e = (char*)vector_at(self->scope_vec, i);
		if (top == NULL) {
			top = namespace_get_at_root(e);
		} else {
			top = namespace_get_namespace(top, e);
		}
	}
	return top;
}

type * fqcn_type(fqcn_cache * self, namespace_ * current) {
	type* ret = fqcn_type_impl(self, current);
	//Console(X::Yを含まない)のような指定なら
	//signal::lang空間も探索する
	if (ret == NULL && self->scope_vec->length == 0) {
		ret = fqcn_type_impl(self, namespace_lang());
	}
	return ret;
}

interface_ * fqcn_interface(fqcn_cache * self, namespace_ * current) {
	//FIXME:コピペ(fqcn_class)
	type* tp = fqcn_type(self, current);
	if (tp == NULL) {
		return NULL;
	}
	assert(tp->tag == type_interface);
	if (tp->tag != type_interface) {
		return NULL;
	}
	return tp->u.interface_;
}

class_ * fqcn_class(fqcn_cache * self, namespace_ * current) {
	//FIXME:コピペ(fqcn_interface)
	type* tp = fqcn_type(self, current);
	if (tp == NULL) {
		return NULL;
	}
	//assert(tp->tag == type_class);
	if (tp->tag != type_class) {
		return NULL;
	}
	return tp->u.class_;
}

void fqcn_cache_delete(fqcn_cache * self) {
	vector_delete(self->scope_vec, vector_deleter_free);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static type * fqcn_type_impl(fqcn_cache * self, namespace_* current) {
	//Y形式
	if (self->scope_vec->length == 0) {
		char* name = self->name;
		//プリミティブ型はどこからでも参照できる
		if (!strcmp(name, "Object")) {
			return CL_OBJECT;
		} else if (!strcmp(name, "Int")) {
			return CL_INT;
		} else if (!strcmp(name, "Double")) {
			return CL_DOUBLE;
		} else if (!strcmp(name, "Char")) {
			return CL_CHAR;
		} else if (!strcmp(name, "String")) {
			return CL_STRING;
		} else if (!strcmp(name, "Bool")) {
			return CL_BOOL;
		} else if (!strcmp(name, "Void")) {
			return CL_VOID;
		}
		if (current == NULL) {
			return NULL;
		}
		return namespace_get_type(current, self->name);
	}
	//X::Yのような形式
	namespace_* c = fqcn_scope(self, current);
	if (c == NULL) {
		return NULL;
	}
	return namespace_get_type(c, self->name);
}