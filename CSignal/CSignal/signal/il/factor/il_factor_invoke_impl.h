#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_INVOKE_H
#define SIGNAL_IL_IL_FACTOR_INVOKE_H
#include "../il_argument_list.h"

/**
 * ���\�b�h�Ăяo����\���v�f.
 */
typedef struct il_factor_invoke {
	char* name;
	il_factor* receiver;
	il_argument_list* argument_list;
} il_factor_invoke;

/**
 * ���\�b�h�Ăяo�����X�[�p�[�Z�b�g�Ƀ��b�v���܂�.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_invoke(il_factor_invoke* self);

/**
 * ���\�b�h�Ăяo����\���v�f���쐬���܂�.
 * @param name
 * @return
 */
il_factor_invoke* il_factor_invoke_new(const char* name);

/**
 * ���\�b�h�Ăяo�����o�͂��܂�.
 * @param self
 * @param depth
 */
void il_factor_invoke_dump(il_factor_invoke* self, int depth);

/**
 * ���\�b�h�Ăяo�����J�����܂�.
 * @param self
 */
void il_factor_invoke_delete(il_factor_invoke* self);
#endif // !SIGNAL_IL_IL_FACTOR_INVOKE_H
