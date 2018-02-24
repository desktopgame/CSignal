#include "generic_type.h"
#include "type_interface.h"
#include "../util/mem.h"

//proto
static void generic_type_tree_delete(vector_item item);

generic_type * generic_type_new(type * core_type) {
	generic_type* ret = (generic_type*)MEM_MALLOC(sizeof(generic_type));
	ret->core_type = core_type;
	ret->type_args_list = vector_new();
	return ret;
}

bool generic_type_assignable(generic_type * left, generic_type * right) {
	//���S�ɓ����|�C���^�Ȃ��r�͕s�v
	if (left == right) {
		return true;
	}
	//��{�^���^�����̐����Ⴄ�Ȃ� false
	if (left->core_type != right->core_type ||
		left->type_args_list->length != right->type_args_list) {
		return false;
	}
	//�^������ 0 �Ȃ��r�s�v
	if (left->type_args_list->length == 0 &&
		right->type_args_list->length == 0) {
		return true;
	}
	//TODO: in/out �̍l��
	//��{�^�ƌ^������0�ȏ�ň�v����Ȃ炻�����r
	bool ret = true;
	for (int i = 0; i < left->type_args_list->length; i++) {
		generic_type* le = (generic_type*)vector_at(left->type_args_list, i);
		generic_type* re = (generic_type*)vector_at(right->type_args_list, i);
		if (!generic_type_assignable(le, re)) {
			ret = false;
			break;
		}
	}
	return ret;
}

void generic_type_delete(generic_type * self) {
	vector_delete(self->type_args_list, generic_type_tree_delete);
	MEM_FREE(self);
}

//private
static void generic_type_tree_delete(vector_item item) {
	generic_type* e = (generic_type*)item;
	generic_type_delete(e);
}