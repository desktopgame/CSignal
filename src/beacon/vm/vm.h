// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file vm.h
 * @brief beacon言語のインタプリタ本体の挙動を定義するVMです。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_VM_VM_H
#define BEACON_VM_VM_H
#include "../util/stack.h"
#include "../util/vector.h"
#include "enviroment.h"
#include "frame.h"
#include "opcode.h"

/**
 * 指定のバイトコードを実行します.
 * @param self
 * @param env
 */
void bc_ExecuteVM(bc_Frame* self, bc_Enviroment* env);

/**
 * 開始位置を指定して指定のバイトコードを実行します.
 * @param self
 * @param env
 * @param pos
 */
void bc_ResumeVM(bc_Frame* self, bc_Enviroment* env, int pos);

/**
 * ネイティブメソッドから例外をスローする場合にはこちらを使用します.
 * @param self
 * @param exc
 */
void bc_ThrowVM(bc_Frame* self, struct bc_Object* exc);

/**
 * selfを起点としてたどれるVM全ての例外フラグをクリアします.
 * 例外オブジェクトは非保護状態になります。
 * @param self NULLのときは何もしません。
 */
void bc_CatchVM(bc_Frame* self);

/**
 * VMがキャッチされなかった例外によって終了した時、
 * そのメッセージを返します.
 * @return
 */
bc_StringView bc_GetVMErrorMessage();
#endif  // !SIGNAL_VM_VM_H