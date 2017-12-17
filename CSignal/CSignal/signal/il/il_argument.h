#pragma once
#ifndef SIGNAL_IL_IL_ARGUMENT_H
#define SIGNAL_IL_IL_ARGUMENT_H
#include "il_factor_interface.h"
/**
 * ��������\���v�f.
 */
typedef struct il_argument {
	//char* name;
	il_factor* factor;
} il_argument;

/**
 * ��������\���v�f���쐬���܂�.
 * @return
 */
il_argument* il_argument_new();

/**
 * ��������\���v�f���o�͂��܂�.
 * @param self
 * @param depth
 */
void il_argument_dump(il_argument* self, int depth);

/**
 * ��������\���v�f���J�����܂�.
 * @param self
 */
void il_argument_delete(il_argument* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_H
