#pragma once
#ifndef BEACON_IL_IL_METHOD_H
#define BEACON_IL_IL_METHOD_H
#include "../env/generic_cache.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include <stdbool.h>
/**
 * メソッドの定義を表す要素.
 */
typedef struct ILMethod {
	StringView namev;
	Vector* parameter_list;
	Vector* statement_list;
	//il_type* return_type;
	generic_cache* return_fqcn;
	AccessLevel access;
	ModifierType modifier;
	Vector* GetParameterListType;
	bool no_stmt;
} ILMethod;
/**
 * メソッドを作成します.
 * @param name
 * @return
 */
ILMethod* NewILMethod(StringView namev);

/**
 * メソッドを開放します.
 * @param self
 */
void DeleteILMethod(ILMethod* self);
#endif // !SIGNAL_IL_IL_METHOD_H
