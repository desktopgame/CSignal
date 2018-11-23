// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file native_method.h
 * @brief C言語で実行されるメソッドを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_NATIVE_METHOD_H
#define BEACON_ENV_NATIVE_METHOD_H
struct bc_NativeMethodRef;
struct bc_Enviroment;
struct bc_Method;
struct bc_Frame;
/**
 * Cで実装されたメソッド.
 */
typedef struct bc_NativeMethod {
        struct bc_NativeMethodRef* Ref;
} bc_NativeMethod;

/**
 * ネイティブメソッドを作成します.
 * @return
 */
bc_NativeMethod* bc_NewNativeMethod();

/**
 * ネイティブメソッドを実行します.
 * @param self
 * @param fr
 * @param env
 */
void bc_ExecuteNativeMethod(bc_NativeMethod* self, struct bc_Method* parent,
                            struct bc_Frame* fr, struct bc_Enviroment* env);

/**
 * ネイティブメソッドを開放します.
 * @param self
 */
void bc_DeleteNativeMethod(bc_NativeMethod* self);

#endif  // !SIGNAL_ENV_NATIVE_METHOD_H
