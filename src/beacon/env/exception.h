// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file exception.h
 * @brief 例外を生成するためのユーティリティを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_EXCEPTION_H
#define BEACON_ENV_EXCEPTION_H
#include <stdarg.h>

struct bc_Object;
struct bc_Frame;

/**
 * signal::lang::Exception 型の例外を作成します.
 * @param fr
 * @param message
 * @return
 */
struct bc_Object* bc_NewSimpleException(struct bc_Frame* fr,
                                        const char* message);
/**
 * signal::lang::Exception 型の例外を作成します.
 * フォーマット付きです.
 * @param fr
 * @param message
 * @param ...
 * @return
 */
struct bc_Object* bc_NewSimplefException(struct bc_Frame* fr,
                                         const char* message, ...);
#endif  // !SIGNAL_ENV_EXCEPTION_H