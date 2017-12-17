#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_VARIABLE_H
#define SIGNAL_IL_IL_FACTOR_VARIABLE_H
#include "../il_factor_interface.h"
/**
 * �ϐ���\���v�f.
 */
typedef struct il_factor_variable {
	char* name;
} il_factor_variable;

/**
 * �ϐ����X�[�p�[�Z�b�g�Ƀ��b�v���܂�.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_variable(il_factor_variable* self);

/**
 * �ϐ����쐬���܂�.
 * @param name
 * @return
 */
il_factor_variable* il_factor_variable_new(const char* name);

/**
 * �ϐ����o�͂��܂�.
 * @param self
 * @param depth
 */
void il_factor_variable_dump(il_factor_variable* self, int depth);

/**
 * �ϐ����J�����܂�.
 */
void il_factor_variable_delete(il_factor_variable* self);
#endif // !SIGNAL_IL_IL_FACTOR_VARIABLE_H
