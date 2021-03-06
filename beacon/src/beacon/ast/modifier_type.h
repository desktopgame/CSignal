#pragma once
#ifndef BEACON_AST_MODIFIER_TYPE_H
#define BEACON_AST_MODIFIER_TYPE_H
#include <stdbool.h>
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum modifier_type {
	modifier_none_T		= (1 << 0),
	modifier_static_T		= (1 << 1),
	modifier_native_T		= (1 << 2),
	modifier_abstract_T	= (1 << 3),
	modifier_override_T	= (1 << 4),
	modifier_final_T		= (1 << 5)
} modifier_type;

/**
 * 指定の修飾子が static を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_static(modifier_type type);

/**
 * 指定の修飾子が native を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_native(modifier_type type);

/**
 * 指定の修飾子が abstract を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_abstract(modifier_type type);

/**
 * 指定の修飾子が override を含むなら true.
 * @param type
 * @return
 */
bool modifier_is_override(modifier_type type);

/**
 * @param type
 * @return
 */
bool modifier_is_final(modifier_type type);

/**
 * 修飾子を出力します.
 * @param type
 */
void modifier_print(modifier_type type);
#endif // !SIGNAL_AST_MODIFIER_TYPE_H
