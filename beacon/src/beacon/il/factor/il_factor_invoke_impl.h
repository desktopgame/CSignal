#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_INVOKE_H
#define SIGNAL_IL_IL_FACTOR_INVOKE_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
struct method;
struct type;
struct generic_type;
/**
 * メソッド呼び出しを表す要素.
 */
typedef struct il_factor_invoke {
	char* name;
	il_factor* receiver;
	vector* argument_list;
	vector* type_argument_list;
	struct method* m;
	struct type* static_receiver;
	struct generic_type* return_type;
	int method_index;
} il_factor_invoke;

/**
 * メソッド呼び出しをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_invoke(il_factor_invoke* self);

/**
 * メソッド呼び出しを表す要素を作成します.
 * @param name
 * @return
 */
il_factor_invoke* il_factor_invoke_new(const char* name);

/**
 * メソッド呼び出しを出力します.
 * @param self
 * @param depth
 */
void il_factor_invoke_dump(il_factor_invoke* self, int depth);

/**
 * メソッド呼び出しを生成します.
 * @param self
 * @param env
 * @param cache
 */
void il_factor_invoke_generate(il_factor_invoke* self, struct enviroment* env, il_load_cache* cache);

/**
 * メソッド呼び出しを読み込みます.
 * @param self
 * @param env
 * @param cache
 * @param eh
 */
void il_factor_invoke_load(il_factor_invoke* self, struct enviroment* env, il_load_cache* cache, il_ehandler* eh);

/**
 * メソッド呼び出しの戻り値の型を返します.
 * @param self
 * @param env
 * @param cache
 * @return
 */
generic_type* il_factor_invoke_eval(il_factor_invoke* self, struct enviroment* env, il_load_cache* cache);

/**
 * メソッド呼び出しを開放します.
 * @param self
 */
void il_factor_invoke_delete(il_factor_invoke* self);
#endif // !SIGNAL_IL_IL_FACTOR_INVOKE_H