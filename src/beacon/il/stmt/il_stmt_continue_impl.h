// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_stmt_continue_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_STMT_CONTINUE_H
#define BEACON_IL_IL_STMT_CONTINUE_H
#include "../il_stmt_interface.h"

bc_ILStatement* bc_WrapILContinue();

void bc_GenerateILContinue(void* empty, bc_Enviroment* env,
                           bc_CallContext* cctx);

void bc_LoadILContinue(void* empty, bc_Enviroment* env, bc_CallContext* cctx);

void bc_DeleteILContinue(void* empty);
#endif  // !SIGNAL_IL_IL_STMT_CONTINUE_H