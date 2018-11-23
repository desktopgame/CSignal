// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file string_buffer.h
 * @brief 可変長な文字列を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_UTIL_Buffer_H
#define BEACON_UTIL_Buffer_H
#include <stdarg.h>

/**
 * 可変長の文字列を格納する構造体.
 * 文字を格納する場合はこちらを使用します。
 */
typedef struct bc_Buffer {
        int Length;
        int Capacity;
        char* Text;
} bc_Buffer;

/**
 * 文字列バッファーを作成します.
 * @return
 */
#define bc_NewBuffer() (bc_MallocBuffer(__FILE__, __LINE__))

/**
 * 文字列バッファーを作成します.
 * @param filename
 * @param lineno
 * @return
 */
bc_Buffer* bc_MallocBuffer(const char* filename, int lineno);

/**
 * バッファーの最後に追記します.
 * @param self
 * @param c
 */
void bc_AppendBuffer(bc_Buffer* self, char c);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ...
 */
void bc_AppendfBuffer(bc_Buffer* self, const char* fmt, ...);

/**
 * フォーマットして追記します.
 * @param self
 * @param fmt
 * @param ap
 */
void bc_VappendfBuffer(bc_Buffer* self, const char* fmt, va_list ap);

/**
 * 全て追記します.
 * @param self
 * @param s
 */
void bc_AppendsBuffer(bc_Buffer* self, const char* s);

/**
 * shrink,freeを実行して文字列だけを返します.
 * @param self
 * @return
 */
char* bc_ReleaseBuffer(bc_Buffer* self);

/**
 * バッファを拡張します.
 * @param self
 */
void bc_ReserveBuffer(bc_Buffer* self);

/**
 * 将来の拡張のために確保された余分な領域を開放します.
 * また、末尾をゼロ文字にします。
 * @param self
 */
void bc_ShrinkBuffer(bc_Buffer* self);

/**
 * @param self
 * @param lineIndex
 * @param len
 * @return
 */
bc_Buffer* bc_IndentBuffer(bc_Buffer* self, int lineIndex, int len);

/**
 * バッファーと中身を開放します.
 * @param self
 */
void bc_DeleteBuffer(bc_Buffer* self);
#endif  // !SIGNAL_UTIL_Buffer_H
