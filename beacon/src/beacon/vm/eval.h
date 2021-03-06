#pragma once
#ifndef BEACON_VM_EVAL_H
#define BEACON_VM_EVAL_H
#include <stdbool.h>
struct script_context;

/**
 * 指定のファイルを解析して AST を出力します.
 * @param filename
 * @return 成功したなら true.
 */
bool eval_ast(const char* filename);

/**
 * 指定のファイルを解析して IL を出力します.
 * @param filename
 * @return 成功したなら true.
 */
bool eval_il(const char* filename);

/**
 * 指定のファイルを解析してオペコードを出力します.
 * @param filename
 * @return 成功したなら true.
 */
bool eval_op(const char* filename);

/**
 * ファイルの中身を現在のコンテキストで実行します.
 * @param filename
 * @return 解析に成功したなら false
 */
bool eval_file(const char* filename);

/**
 * 指定のソースコードを現在のコンテキストで実行します.
 * @param source
 * @return 成功したなら true.
 */
bool eval_string(const char* source);
#endif // !SIGNAL_VM_EVAL_H
