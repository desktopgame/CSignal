// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file text.h
 * @brief 文字列に関するユーティリティを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_UTIL_TEXT_H
#define BEACON_UTIL_TEXT_H
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include "../util/io.h"
#include "vector.h"

/**
 * beaconのshortリテラル表現をCのリテラルへ変換します。
 * @param literal
 * @return
 */
short bc_StrToShort(const char* literal);

/**
 * beaconのintリテラル表現をCのリテラルへ変換します。
 * @param literal
 * @return
 */
int bc_StrToInt(const char* literal);

/**
 * beaconのlongリテラル表現をCのリテラルへ変換します。
 * @param literal
 * @return
 */
long bc_StrToLong(const char* literal);

/**
 * beaconのfloatリテラル表現をCのリテラルへ変換します。
 * @param literal
 * @return
 */
float bc_StrToFloat(const char* literal);

/**
 * beaconのdoubleリテラル表現をCのリテラルへ変換します。
 * @param literal
 * @return
 */
double bc_StrToDouble(const char* literal);

/**
 * 引数の文字列を複製して返します.
 * コンパイラごとの差分を吸収するために提供されます。
 * @param source
 */
char* bc_Strdup(const char* source);

/**
 * 二つの文字列を連結して返します.
 * @param a 呼び出し側で開放してください.
 * @param b 呼び出し側で開放してください.
 * @return 呼び出し側で開放してください.
 */
char* bc_ConcatString(const char* a, const char* b);

/**
 * 指定の位置の行を取り出します.
 * @param src
 * @param lineno
 * @return 呼び出し側で開放してください。
 */
char* bc_GetLineAt(const char* src, int lineno);

/**
 * 標準入力から一行読み込んで返します.
 * @return
 */
char* bc_ReadLine();

/**
 * 指定のファイルから一行読み込みます.
 * @param fp
 * @return
 */
char* bc_FreadLine(FILE* fp);

/**
 * srcをpathで区切った時、最後に現れる文字列をbufferへ格納します。
 * @param src
 * @param path
 * @param buffer
 * @param bufsize
 * @return バッファに入力した文字数
 */
int bc_GetLastPathComponent(const char* src, char path, char buffer[],
                            int bufsize);
#endif  // !SIGNAL_UTIL_TEXT_H
