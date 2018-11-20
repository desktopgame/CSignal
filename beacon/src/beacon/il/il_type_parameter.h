//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_type_parameter.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_TYPE_PARAMETER_H
#define BEACON_IL_IL_TYPE_PARAMETER_H
#include "../util/vector.h"
#include "../util/string_pool.h"

/**
 * 型引数の属性を表す列挙型.
 */
typedef enum ILTypeParameterTag {
	IL_TYPE_PARAMETER_KIND_DEFAULT_T,
	IL_TYPE_PARAMETER_KIND_IN_T,
	IL_TYPE_PARAMETER_KIND_OUT_T,
} ILTypeParameterTag;

/**
 * 型引数を表す構造体.
 */
typedef struct ILTypeParameter {
	ILTypeParameterTag Tag;
	bc_StringView Name;
} ILTypeParameter;

/**
 * 新しい型引数を作成します.
 * @param name
 * @return
 */
ILTypeParameter* NewILTypeParameter(bc_StringView name);

/**
 * 型引数の一覧を出力します.
 * @param v<il_>
 */
void PrintILTypeParameterList(bc_Vector* v);

/**
 * 型引数を解放します.
 * @param self
 */
void DeleteILTypeParameter(ILTypeParameter* self);
#endif // !SIGNAL_IL_IL_TYPE_PARAMETER_H
