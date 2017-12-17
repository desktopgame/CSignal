#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_CALL_H
#define SIGNAL_IL_IL_FACTOR_CALL_H
#include "../il_argument_list.h"
/**
 * �֐��Ăяo����\���v�f.
 */
typedef struct il_factor_call {
	char* name;
	il_argument_list* argument_list;
} il_factor_call;

/**
 * �֐��Ăяo�����X�[�p�[�Z�b�g�Ƀ��b�v���܂�.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_call(il_factor_call* self);

/**
 * �֐��Ăяo����\���v�f���쐬���܂�.
 * @param name
 * @return
 */
il_factor_call* il_factor_call_new(const char* name);

/**
 * �֐��Ăяo�����o�͂��܂�.
 * @param self
 * @param depth
 */
void il_factor_call_dump(il_factor_call* self, int depth);

/**
 * �֐��Ăяo�����J�����܂�.
 * @param self
 */
void il_factor_call_delete(il_factor_call* self);
#endif // !SIGNAL_IL_IL_FACTOR_CALL_H
