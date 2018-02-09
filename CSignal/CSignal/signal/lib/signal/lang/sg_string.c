#include "sg_string.h"
#include "../../sg_library_impl.h"
#include <assert.h>

//proto
static void sg_string_nativeInit(method* parent, vm* vm, enviroment* env);

void sg_string_init() {
	namespace_* lang = namespace_lang();
	class_* stringClass = class_new_preload("String");
	namespace_add_type(lang, type_wrap_class(stringClass));
	class_define_native_method(stringClass, "nativeInit", sg_string_nativeInit);
}

string_buffer * sg_string_raw(object* self) {
	vector_item e = vector_at(self->nativeSlotVec, 0);
	assert(self->tag == object_string);
	return (string_buffer*)e;
}

//private
static void sg_string_nativeInit(method* parent, vm* vm, enviroment* env) {
	object* self = vector_at(vm->ref_stack, 0);
	//�v���O�����̒��� �_�u���N�H�[�g("HelloWorld") �ɂ����
	//�����񂪍쐬���ꂽ�ꍇ�ɂ� object_string_new() 
	//�ɂ���Đ�������܂��B
	//������̏ꍇ�ł� object#nativeSlotVec �� C�`���̕�������i�[���܂��B
	//����̓R���X�g���N�^�ɂ���� String ���쐬���ꂽ�ꍇ�ɂ�
	//�Ăяo����Ȃ��̂ŁA���̕����̏����������ōs���܂��B

	//String#charArray���擾
	int temp = 0;
	class_find_field(CL_STRING->u.class_, "charArray", &temp);
	object* charArr = vector_at(self->u.field_vec, temp);
	//����� char* �֕ϊ�
	string_buffer* sb = string_buffer_new();
	for (int i = 0; i < charArr->nativeSlotVec->length; i++) {
		object* e = (object*)vector_at(charArr->nativeSlotVec, i);
		assert(e->tag == object_char);
		string_buffer_append(sb, e->u.char_);
	}
	vector_assign(self->nativeSlotVec, 0, sb);
	self->tag = object_string;
}