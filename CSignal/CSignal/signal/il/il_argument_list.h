#pragma once
#ifndef SIGNAL_IL_IL_ARGUMENT_LIST_H
#define SIGNAL_IL_IL_ARGUMENT_LIST_H
#include "il_argument.h"
#include "../util/list.h"
/**
 * �������̈ꗗ��\���v�f.
 */
typedef list il_argument_list;

/**
 * �������̈ꗗ��\���v�f���쐬���܂�.
 * @return
 */
il_argument_list* il_argument_list_new();

/**
 * �������̈ꗗ�ɉ����܂�.
 * @param self
 * @param child
 */
void il_argument_list_push(il_argument_list* self, il_argument* child);

/**
 * �������̈ꗗ���o�͂��܂�.
 * @param self
 * @param depth
 */
void il_argument_list_dump(il_argument_list* self, int depth);

/**
 * �������̈ꗗ���J�����܂�.
 * @param self
 */
void il_argument_list_delete(il_argument_list* self);
#endif // !SIGNAL_IL_IL_ARGUMENT_LIST_H
