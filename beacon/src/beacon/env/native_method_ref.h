//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file native_method_ref.h
 * @brief ネイティブメソッドのための関数ポインタのラッパーです。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_NATIVE_METHOD_REF_H
#define BEACON_ENV_NATIVE_METHOD_REF_H
#include "method.h"
#include "../vm/vm.h"
#include "../vm/enviroment.h"
#include <stdint.h>
/**
 * ネイティブメソッドの実装.
 */
typedef void(*bc_NativeImpl)(bc_Method* parent, Frame* vm, Enviroment* env);

/**
 * ネイティブメソッドを表す関数ポインタをラップする構造体.
 */
typedef struct bc_NativeMethodRef {
	bc_NativeImpl Body;
} bc_NativeMethodRef;

/**
 * ラッパーを作成します.
 * @param impl
 * @return
 */
bc_NativeMethodRef* bc_NewNativeMethodRef(bc_NativeImpl impl);

/**
 * ラッパーを開放します.
 * @param self
 */
void bc_DeleteNativeMethodRef(bc_NativeMethodRef* self);
#endif // !SIGNAL_ENV_NATIVE_METHOD_REF_H
