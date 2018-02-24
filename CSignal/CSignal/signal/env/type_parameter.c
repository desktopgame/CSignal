#include "type_parameter.h"
#include "../util/mem.h"
#include "../util/text.h"
#include "../util/vector.h"
#include "../il/il_type_parameter.h"
#include "../il/il_load_cache.h"
#include "type_parameter_rule.h"

//proto
static void type_parameter_rule_list_delete(vector_item item);

type_parameter * type_parameter_new(char * name) {
	type_parameter* ret = (type_parameter*)MEM_MALLOC(sizeof(type_parameter));
	ret->name = text_strdup(name);
	ret->kind = type_parameter_kind_default;
	ret->rule_vec = vector_new();
	return ret;
}

type_parameter * type_parameter_dup(il_type_parameter * src, il_load_cache* cache) {
	type_parameter* ret = type_parameter_new(src->name);
	switch (src->kind) {
		case il_type_parameter_kind_default:
			ret->kind = type_parameter_kind_default;
			break;
		case il_type_parameter_kind_in:
			ret->kind = type_parameter_kind_in;
			break;
		case il_type_parameter_kind_out:
			ret->kind = type_parameter_kind_out;
			break;
		default:
			break;
	}
//	type_parameter_rule_list_dup(src->rule_vec, ret->rule_vec, cache);
	return ret;
}

void type_parameter_list_dup(vector* ilSource, vector* sgDest, il_load_cache* cache) {
	//�����IL���x����<K, V>�̕��т�
	//SG���x����<K, V> �֕ϊ����܂��B
	//<K(IComparable<K>), V>�̂悤�Ȑ錾������Ƃ��A
	//K�͉��z�^�Ƃ���IComparable�Ő������F������܂��B
	//���̂��߂ɂ́Atype_parameter���Ƃ肦���o�^���Ă����āA
	//���Ƃ��烋�[���ꗗ��Ή��Â���K�v������܂��B
	//type_parameter_dup���烋�[���̕������폜�����̂����̂��߂ł��B
	for (int i = 0; i < ilSource->length; i++) {
		il_type_parameter* e = (il_type_parameter*)vector_at(ilSource, i);
		type_parameter* newTP = type_parameter_dup(e, cache);
		vector_push(sgDest, newTP);
		//type_parameter_rule_list_dup(e->rule_vec, newTP->rule_vec, cache);
	}
	//�����Ń��[���𓖂Ă͂߂�
	for (int i = 0; i < ilSource->length; i++) {
		il_type_parameter* e = (il_type_parameter*)vector_at(ilSource, i);
		type_parameter* v = vector_at(sgDest, i);
		type_parameter_rule_list_dup(e->rule_vec, v->rule_vec, cache);
	}
}

void type_parameter_print(vector* v) {
	//FIXME:il_type_parameter����̃R�s�y
	if (v->length <= 0) {
		return;
	}
	text_printf("<");
	for (int i = 0; i < v->length; i++) {
		type_parameter* e = (type_parameter*)vector_at(v, i);
		if (e->kind == type_parameter_kind_in) {
			text_printf("in ");
		} else if (e->kind == type_parameter_kind_out) {
			text_printf("out ");
		}
		text_printf("%s", e->name);
		type_parameter_rule_list_print(e->rule_vec);
		if (i != v->length - 1) {
			text_printf(", ");
		}
	}
	text_printf(">");
}

void type_parameter_delete(type_parameter * self) {
	vector_delete(self->rule_vec, type_parameter_rule_list_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}
//private
static void type_parameter_rule_list_delete(vector_item item) {
	type_parameter_rule* e = (type_parameter_rule*)item;
	type_parameter_rule_delete(e);
}

