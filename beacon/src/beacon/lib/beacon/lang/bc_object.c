#include "bc_object.h"
#include "../../bc_library_impl.h"
#include "../../../util/string_buffer.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include <stdio.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static void bc_object_nativeToString(method* parent, frame* fr, enviroment* env);
static void bc_object_nativeReferenceEquals(method* parent, frame* fr, enviroment* env);

void bc_object_init() {
	namespace_* lang = GetLangNamespace();
	type* objectType = class_new_preload(InternString("Object"));
	class_* objectClass = TYPE2CLASS(objectType);
	AddTypeNamespace(lang, objectType);
	class_define_native_method(objectClass, "nativeToString", bc_object_nativeToString);
	class_define_native_method(objectClass, "nativeReferenceEquals", bc_object_nativeReferenceEquals);
}

type* bc_object_type() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Object"));
}

//private
static void bc_object_nativeToString(method* parent, frame* fr, enviroment* env) {
	object* self = (object*)AtVector(fr->ref_stack, 0);
	string_buffer* sb = NewBuffer();
	//参照型
	if (self->tag == OBJECT_REF_T) {
		//char* name = type_name(self->type);
		AppendBuffer(sb, '[');
		AppendsBuffer(sb, "Ref");
		AppendBuffer(sb, ']');
		ShrinkBuffer(sb);
	//真偽型
	} else if (self->tag == OBJECT_BOOL_T) {
		if (self == GetTrueObject()) {
			AppendsBuffer(sb, "true");
		} else if (self == GetFalseObject()) {
			AppendsBuffer(sb, "false");
		}
	//整数型
	} else if (self->tag == OBJECT_INT_T) {
#define BUFF_LEN 256
		char buff[256];
		int res = sprintf(buff, "%d", self->u.int_);
		AppendsBuffer(sb, buff);
#undef BUFF_LEN
	}
	char* str = ReleaseBuffer(sb);
	object* ret = object_string_new(str);
	PushVector(fr->value_stack, ret);
	MEM_FREE(str);
}

static void bc_object_nativeReferenceEquals(method* parent, frame* fr, enviroment* env) {
	object* a = (object*)AtVector(fr->ref_stack, 1);
	object* b = (object*)AtVector(fr->ref_stack, 2);
	PushVector(fr->value_stack, GetBoolObject(a == b));
}