#pragma once
#ifndef BEACON_IL_IL_TYPE_PARAMETER_H
#define BEACON_IL_IL_TYPE_PARAMETER_H
#include "../util/vector.h"
#include "../util/string_pool.h"

/**
 * 型引数の属性を表す列挙型.
 */
typedef enum il_type_parameter_kind {
	il_type_parameter_kind_default_T,
	il_type_parameter_kind_in_T,
	il_type_parameter_kind_out_T,
} il_type_parameter_kind;

/**
 * 型引数を表す構造体.
 */
typedef struct il_type_parameter {
	il_type_parameter_kind kind;
	string_view namev;
//	vector* rule_vec;
} il_type_parameter;

/**
 * 新しい型引数を作成します.
 * @param name
 * @return
 */
il_type_parameter* il_type_parameter_new(string_view namev);

/**
 * 型引数の一覧を出力します.
 * @param v<il_>
 */
void il_type_parameter_list_print(vector* v);

/**
 * 型引数を解放します.
 * @param self
 */
void il_type_parameter_delete(il_type_parameter* self);
#endif // !SIGNAL_IL_IL_TYPE_PARAMETER_H
