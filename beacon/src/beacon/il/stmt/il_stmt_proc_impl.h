#pragma once
#ifndef BEACON_IL_IL_STMT_EXPR_H
#define BEACON_IL_IL_STMT_EXPR_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
/**
 * 式のみで構成される文を表す要素.
 */
typedef struct ILProc {
	ILFactor* factor;
} ILProc;

/**
 * 式のみで構成される文を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILProc(ILProc* self);

/**
 * 式のみで構成される文を表す要素を作成します.
 * @return
 */
ILProc* NewILProc();

/**
 * 式のみで構成される文を生成します.
 * @param self
 * @param env
 * @param cctx
 */
void GenerateILProc(ILProc* self, Enviroment* env, CallContext* cctx);

/**
 * 式のみで構成される文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILProc(ILProc* self, Enviroment* env, CallContext* cctx);

/**
 * 式のみで構成される文を表す要素を開放します.
 * @param self
 */
void DeleteILProc(ILProc* self);
#endif // !SIGNAL_IL_IL_STMT_EXPR_H
