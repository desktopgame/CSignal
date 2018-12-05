// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file modifier_type.h
 * @brief メンバーの属性を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_AST_MODIFIER_TYPE_H
#define BEACON_AST_MODIFIER_TYPE_H
#include <stdarg.h>
#include <stdbool.h>
#include "../util/string_pool.h"
/**
 * アクセス修飾子を表す列挙型.
 */
typedef enum bc_ModifierType {
        MODIFIER_NONE_T = (1 << 0),
        MODIFIER_STATIC_T = (1 << 1),
        MODIFIER_NATIVE_T = (1 << 2),
        MODIFIER_ABSTRACT_T = (1 << 3),
        MODIFIER_OVERRIDE_T = (1 << 4),
        MODIFIER_FINAL_T = (1 << 5)
} bc_ModifierType;

/**
 * 指定の修飾子が static を含むなら true.
 * @param type
 * @return
 */
bool bc_IsStaticModifier(bc_ModifierType type);

/**
 * 指定の修飾子が native を含むなら true.
 * @param type
 * @return
 */
bool bc_IsNativeModifier(bc_ModifierType type);

/**
 * 指定の修飾子が abstract を含むなら true.
 * @param type
 * @return
 */
bool bc_IsAbstractModifier(bc_ModifierType type);

/**
 * 指定の修飾子が override を含むなら true.
 * @param type
 * @return
 */
bool bc_IsOverrideModifier(bc_ModifierType type);

/**
 * @param type
 * @return
 */
bool bc_IsFinalModifier(bc_ModifierType type);

/**
 * 修飾子を出力します.
 * @param type
 */
void bc_PrintModifier(bc_ModifierType type);

/**
 * 引数に列挙する修飾子を全て含むなら true.
 * @param self
 * @param ...
 * @return
 */
bool bc_IsIncludeModifier(bc_ModifierType self, int count,
                          bc_ModifierType list[], int* outIndex);

/**
 * 修飾子を文字列へ変換します。
 * @param type
 * @return
 */
bc_StringView bc_ModifierTypeToString(bc_ModifierType type);
#endif  // !SIGNAL_AST_MODIFIER_TYPE_H
