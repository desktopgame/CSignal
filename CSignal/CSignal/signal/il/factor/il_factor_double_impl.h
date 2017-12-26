#pragma once
#ifndef SIGNAL_IL_IL_FACTOR_DOUBLE_H
#define SIGNAL_IL_IL_FACTOR_DOUBLE_H
#include "../il_factor_interface.h"
//struct opcode_buf;
/**
 * 浮動小数リテラルを表す要素.
 */
typedef struct il_factor_double {
	double value;
} il_factor_double;

/**
 * 浮動小数リテラルをスーパーセットにラップします.
 * @param self
 * @return
 */
il_factor* il_factor_wrap_double(il_factor_double* self);

/**
 * 浮動小数リテラルを表す要素を作成します.
 * @param d
 * @return
 */
il_factor_double* il_factor_double_new(double d);

/**
 * 浮動小数リテラルを表示します.
 * @param self
 * @param depth
 */
void il_factor_double_dump(il_factor_double* self, int depth);

/**
 * 浮動小数リテラルを表す要素を生成します.
 * @param self
 * @param buf
 */
void il_factor_double_generate(il_factor_double* self, struct opcode_buf* buf);

/**
 * 浮動小数リテラルを表す要素を開放します.
 * @param self
 */
void il_factor_double_delete(il_factor_double* self);
#endif // !SIGNAL_IL_IL_FACTOR_DOUBLE_H
