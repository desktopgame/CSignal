#include "object.h"
#include "namespace.h"
#include "../util/string_buffer.h"
#include <stdlib.h>
#include "vtable.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "type_interface.h"
#include <assert.h>
#include "type_impl.h"
#include "../lib/signal/lang/sg_array.h"
#include "heap.h"
#include "../lib/signal/lang/sg_array.h"
#include "../util/logger.h"

//proto
static object* object_malloc(object_tag type);
static object* gObjectTrue = NULL;
static object* gObjectFalse = NULL;
static object* gObjectNull = NULL;
static int gObjectCount = 0;


object * object_int_new(int i) {
	object* ret = object_malloc(object_int);
	ret->u.int_ = i;
	ret->type = CL_INT;
	ret->vptr = type_vtable(CL_INT);
	return ret;
}

object * object_double_new(double d) {
	object* ret = object_malloc(object_double);
	ret->u.double_ = d;
	ret->type = CL_DOUBLE;
	ret->vptr = type_vtable(CL_DOUBLE);
	return ret;
}

object * object_char_new(char c) {
	object* ret = object_malloc(object_char);
	ret->u.char_ = c;
	ret->type = CL_CHAR;
	ret->vptr = type_vtable(CL_CHAR);
	return ret;
}

object * object_string_new(const char * s) {
	object* ret = object_malloc(object_string);
	//ret->u.string_ = s;
	ret->u.field_vec = vector_new();
	ret->type = CL_STRING;
	ret->vptr = type_vtable(CL_STRING);

	//�z��𐶐�
	object* arr = object_ref_new();
	type* arrType = sg_array_class();
	type* strType = namespace_get_type(namespace_lang(), "String");
	arr->type = arrType;
	arr->vptr = type_vtable(arrType);
	//�{�b�N�X��
	char* itr = s;
	string_buffer* sb = string_buffer_new();
	while ((*itr) != '\0') {
		char e = (*itr);
		vector_push(arr->nativeSlotVec, object_char_new(e));
		itr++;
		string_buffer_append(sb, e);
	}
	string_buffer_shrink(sb);
	//String#charArray�𖄂߂�
	int temp = 0;
	class_find_field(strType->u.class_, "charArray", &temp);
	vector_assign(ret->u.field_vec, temp, arr);
	vector_item* test = vector_at(ret->u.field_vec, temp);
	assert(test != NULL);
	//Array#length�𖄂߂�
	temp = 0;
	class_find_field(arrType->u.class_, "length", &temp);
	vector_assign(arr->u.field_vec, temp, object_int_new(sb->length));
	//C�`���̕�����ł��ۑ�
	vector_assign(ret->nativeSlotVec, 0, sb);
	return ret;
}

object * object_ref_new() {
	object* ret= object_malloc(object_ref);
	ret->u.field_vec = vector_new();
	return ret;
}

object * object_bool_get(bool b) {
	return (b ? object_get_true() : object_get_false());
}

object * object_get_true() {
	if (gObjectTrue == NULL) {
		gObjectTrue = object_malloc(object_bool);
		gObjectTrue->u.bool_ = !false;
		gObjectTrue->type = CL_BOOL;
	}
	return gObjectTrue;
}

object * object_get_false() {
	if (gObjectFalse == NULL) {
		gObjectFalse = object_malloc(object_bool);
		gObjectFalse->u.bool_ = false;
		gObjectFalse->type = CL_BOOL;
	}
	return gObjectFalse;
}

object * object_get_null() {
	if (gObjectNull == NULL) {
		gObjectNull = object_malloc(object_null);
		gObjectNull->type = CL_NULL;
	}
	return gObjectNull;
}

void object_inc(object * self) {
	if (self->tag == object_int) {
		self->u.int_++;
	} else if (self->tag == object_double) {
		self->u.double_++;
	} else assert(false);
}

void object_dec(object * self) {
	if (self->tag == object_int) {
		self->u.int_--;
	} else if (self->tag == object_double) {
		self->u.double_--;
	} else  assert(false);
}

object* object_copy(object * self) {
	object* ret = NULL;
	if (self->tag == object_int) {
		ret = object_int_new(self->u.int_);
	} else if (self->tag == object_double) {
		ret = object_double_new(self->u.double_);
	} else if (self->tag == object_char) {
		ret = object_char_new(self->u.char_);
	} else {
		ret = self;
	}
	return ret;
}

object * object_copy_s(object * self) {
	assert(self->tag != object_ref);
	return object_copy(self);
}

void object_markall(object * self) {
	//field#static_value��
	//���ۂɏC���q�� static �łȂ��Ƃ��� NULL
	if (self == NULL) {
		return;
	}
	if (self->paint == paint_marked) {
		return;
	}
	if (self->paint != paint_onexit) {
		self->paint = paint_marked;
	}
	//�t�B�[���h��S�ă}�[�N
	if (self->tag == object_string ||
		self->tag == object_ref) {
		for (int i = 0; i < self->u.field_vec->length; i++) {
			object* e = (object*)vector_at(self->u.field_vec, i);
			object_markall(e);
		}
	}
	//�z��^�Ȃ�X���b�g���S�ă}�[�N
	type* arrayType = sg_array_class();
	if (self->tag == object_ref &&
		self->type == arrayType) {
		for (int i = 0; i < self->nativeSlotVec->length; i++) {
			object* e = (object*)vector_at(self->nativeSlotVec, i);
			object_markall(e);
		}
	}
}

int object_count() {
	return gObjectCount;
}

void object_print(object * self) {
	if (self->tag == object_int) {
		text_printf("Int: %d", self->u.int_);
	} else if (self->tag == object_double) {
		text_printf("Double: %d", self->u.double_);
	} else if (self->tag == object_string) {
		string_buffer* sb = (string_buffer*)vector_at(self->nativeSlotVec, 0);
		text_printf("String: %s", sb->text);
	} else if (self->tag == object_bool) {
		text_printf("Bool: %s", (self == object_get_true() ? "true" : "false"));
	} else if (self->tag == object_null) {
		text_printf("Ref: Null");
	} else if (self->tag == object_ref) {
		text_printf("Ref: %s", type_name(self->type));
	}
}

void object_delete(object * self) {
	gObjectCount--;
	//sg_info(__FILE__, __LINE__, "deleted object %s", type_name(self->type));
	if (self->tag == object_string) {
		string_buffer* sb = vector_at(self->nativeSlotVec, 0);
		vector_remove(self->nativeSlotVec, 0);
		string_buffer_delete(sb);
	}
	if (self->tag == object_string ||
		self->tag == object_ref) {
		vector_delete(self->u.field_vec, vector_deleter_null);
	}
	vector_delete(self->nativeSlotVec, vector_deleter_null);
	MEM_FREE(self);
}

//private
static object* object_malloc(object_tag type) {
	object* ret = (object*)MEM_MALLOC(sizeof(object));
	ret->type = NULL;
	ret->paint = paint_unmarked;
	ret->tag = type;
	ret->vptr = NULL;
	ret->nativeSlotVec = vector_new();
	heap_add(heap_get(), ret);
	gObjectCount++;
	return ret;
}