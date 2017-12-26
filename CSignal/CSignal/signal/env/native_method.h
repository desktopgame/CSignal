#pragma once
#ifndef SIGNAL_ENV_NATIVE_METHOD_H
#define SIGNAL_ENV_NATIVE_METHOD_H
struct vm;
struct method;

/**
 * Cで実装されたメソッド.
 */
typedef struct native_method {
	void(*impl)(struct method* parent, struct vm* vm);
} native_method;

/**
 * ネイティブメソッドを作成します.
 * @return
 */
native_method* native_method_new();

/**
 * ネイティブメソッドを実行します.
 * @param self
 * @param vm
 */
void native_method_execute(native_method* self, struct method* parent, struct vm* vm);

/**
 * ネイティブメソッドを開放します.
 * @param self
 */
void native_method_delete(native_method* self);

/**
 * ネイティブメソッドの空実装.
 * @param parent
 * @param vm
 */
void native_method_empty(struct method* parent, struct vm* vm);
#endif // !SIGNAL_ENV_NATIVE_METHOD_H
