#pragma once
#ifndef BEACON_UTIL_Buffer_H
#define BEACON_UTIL_Buffer_H
#include <stdarg.h>

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct Buffer_t {
	int Length;
	int Capacity;
	char* Text;
} Buffer;

/**
 * 文字列バッファーを作成します.
 * @return
 */
#define NewBuffer() (MallocBuffer(__FILE__, __LINE__))

/**
 * 文字列バッファーを作成します.
 * @param filename
 * @param lineno
 * @return
 */
Buffer* MallocBuffer(const char* filename, int lineno);

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void AppendBuffer(Buffer* self, char c);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ...
 */
void AppendfBuffer(Buffer* self, const char* fmt, ...);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ap
 */
void VappendfBuffer(Buffer* self, const char* fmt, va_list ap);

/**
 * 全て追記します.
 * @param self
 * @param s
 */
void AppendsBuffer(Buffer* self, const char* s);

/**
 * shrink,freeを実行して文字列だけを返します.
 * @param self
 * @return
 */
char* ReleaseBuffer(Buffer* self);

/**
 * バッファを拡張します.
 * @param self
 */
void ReserveBuffer(Buffer* self);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void ShrinkBuffer(Buffer* self);

/**
 * @param self
 * @param lineIndex
 * @param len
 * @return
 */
Buffer* IndentBuffer(Buffer* self, int lineIndex, int len);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void DeleteBuffer(Buffer* self);
#endif // !SIGNAL_UTIL_Buffer_H
