//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_proc_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_STMT_EXPR_H
#define BEACON_IL_IL_STMT_EXPR_H
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
/**
 * 式のみで構成される文を表す要素.
 */
typedef struct ILProc {
	bc_ILFactor* Factor;
} ILProc;

/**
 * 式のみで構成される文を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
bc_ILStatement* WrapILProc(ILProc* self);

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
void GenerateILProc(ILProc* self, bc_Enviroment* env, bc_CallContext* cctx);

/**
 * 式のみで構成される文を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILProc(ILProc* self, bc_Enviroment* env, bc_CallContext* cctx);

/**
 * 式のみで構成される文を表す要素を開放します.
 * @param self
 */
void DeleteILProc(ILProc* self);
#endif // !SIGNAL_IL_IL_STMT_EXPR_H
