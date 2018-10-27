#ifndef BEACON_IL_STMT_RETURN_EMPTY_H
#define BEACON_IL_STMT_RETURN_EMPTY_H
#include "../il_stmt_interface.h"

/**
 * 式を返却する文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILReturnEmpty(ILStatement_return_empty self, Enviroment* env, CallContext* cctx);

/**
 * 式を返却する文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILReturnEmpty(ILStatement_return_empty self, Enviroment* env, CallContext* cctx);
#endif