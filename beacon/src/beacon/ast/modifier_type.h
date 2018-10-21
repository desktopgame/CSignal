#pragma once
#ifndef BEACON_AST_MODIFIER_TYPE_H
#define BEACON_AST_MODIFIER_TYPE_H
#include <stdbool.h>
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum ModifierType {
	MODIFIER_NONE_T		= (1 << 0),
	MODIFIER_STATIC_T		= (1 << 1),
	MODIFIER_NATIVE_T		= (1 << 2),
	MODIFIER_ABSTRACT_T	= (1 << 3),
	MODIFIER_OVERRIDE_T	= (1 << 4),
	MODIFIER_FINAL_T		= (1 << 5)
} ModifierType;

/**
 * 指定の修飾子が static を含むなら true.
 * @param type
 * @return
 */
bool IsStaticModifier(ModifierType type);

/**
 * 指定の修飾子が native を含むなら true.
 * @param type
 * @return
 */
bool IsNativeModifier(ModifierType type);

/**
 * 指定の修飾子が abstract を含むなら true.
 * @param type
 * @return
 */
bool IsAbstractModifier(ModifierType type);

/**
 * 指定の修飾子が override を含むなら true.
 * @param type
 * @return
 */
bool IsOverrideModifier(ModifierType type);

/**
 * @param type
 * @return
 */
bool IsFinalModifier(ModifierType type);

/**
 * 修飾子を出力します.
 * @param type
 */
void PrintModifier(ModifierType type);
#endif // !SIGNAL_AST_MODIFIER_TYPE_H
