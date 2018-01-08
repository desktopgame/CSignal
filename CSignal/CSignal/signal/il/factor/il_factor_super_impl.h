#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_SUPER_H
#define SIGNAL_IL_IL_FACTOR_SUPER_H
#include "../il_ehandler.h"
struct enviroment;
struct type;

/**
 * superを表す要素.
 */
typedef int il_factor_super;

/**
 * superを表す要素を出力します.
 * @param self
 * @param depth
 */
void il_factor_super_dump(il_factor_super* self, int depth);

/**
 * superを表す要素を出力します.
 * @param self
 * @param env
 */
void il_factor_super_generate(il_factor_super* self, struct enviroment* env);

/**
 * superを表す要素を読み込みます.
 * @param self
 * @param env
 * @param eh
 */
void il_factor_super_load(il_factor_super* self, struct enviroment* env, il_ehandler* eh);

/**
 * superで参照されるオブジェクトの型を返します.
 * @param self
 * @param env
 * @return
 */
struct type* il_factor_super_eval(il_factor_super* self, struct enviroment* env);

/**
 * superを表す要素を出力します.
 * @param depth
 */
void il_factor_super_delete(il_factor_super* self);
#endif // !SIGNAL_IL_IL_FACTOR_SUPER_H
