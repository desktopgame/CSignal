#include "bc_string.h"
#include "../../bc_library_impl.h"
#include <assert.h>

//proto
static void bc_string_nativeInit(method* parent, vm* vm, enviroment* env);

void bc_string_init() {
	namespace_* lang = namespace_lang();
	class_* stringClass = class_new_preload("String");
	namespace_add_type(lang, type_wrap_class(stringClass));
	class_define_native_method(stringClass, "nativeInit", bc_string_nativeInit);
}

string_buffer * bc_string_raw(object* self) {
	vector_item e = vector_at(self->native_slot_vec, 0);
	assert(self->tag == object_string);
	return (string_buffer*)e;
}

//private
static void bc_string_nativeInit(method* parent, vm* vm, enviroment* env) {
	object* self = vector_at(vm->ref_stack, 0);
	//プログラムの中で ダブルクォート("HelloWorld") によって
	//文字列が作成された場合には object_string_new() 
	//によって生成されます。
	//こちらの場合では object#nativeSlotVec に C形式の文字列を格納します。
	//これはコンストラクタによって String が作成された場合には
	//呼び出されないので、その部分の処理をここで行います。

	//String#charArrayを取得
	int temp = 0;
	class_find_field(CL_STRING->u.class_, "charArray", &temp);
	object* charArr = vector_at(self->u.field_vec, temp);
	//これを char* へ変換
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < charArr->native_slot_vec->length; i++) {
		object* e = (object*)vector_at(charArr->native_slot_vec, i);
		assert(e->tag == object_char);
		string_buffer_append(sb, e->u.char_);
	}
	vector_assign(self->native_slot_vec, 0, sb);
	self->tag = object_string;
}