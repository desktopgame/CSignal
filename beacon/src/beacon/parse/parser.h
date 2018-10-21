#pragma once
#ifndef BEACON_PARSE_PARSER_H
#define BEACON_PARSE_PARSER_H
#include "../ast/ast.h"
#include "yacc_input_type.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * 解析の結果を表す構造体.
 */
typedef enum ParseResult {
	PARSE_AWAIT_T = -1,
	PARSE_COMPLETE_T = 0,
	PARSE_OPEN_ERROR_T,
	PARSE_SYNTAX_ERROR_T
} ParseResult;

/**
 * Yacc/Bisonの解析結果を保存する構造体です.
 */
typedef struct Parser {
	AST* Root;
	Buffer* LiteralBuffer;
	//char* source;
	char* SourceName;
	char* ErrorLineText;
	char* ErrorMessage;
	int ErrorLineIndex;
	int ErrorColumnIndex;
	YaccInputType InputType;
	ParseResult Result;
	int Lineno;
	Vector* LinenoTable;
} Parser;

/**
 * 文字列を入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
Parser* ParseString(const char* source);

/**
 * ファイルを入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
Parser* ParseFile(const char* filename);

/**
 * 現在のパーサーを返します.
 * @return
 */
Parser* GetCurrentParser();

/**
 * エラー情報とASTを解放します.
 * @param self
 */
void DestroyParser(Parser* self);

/**
 * 文字列バッファーをクリアします.
 * @param self
 */
void ClearParserBuffer(Parser* self);

/**
 * 文字列バッファーに一文字加算します.
 * @param self
 * @return
 */
void AppendParserBuffer(Parser* self, char ch);

/**
 * 文字列バッファーをリテラルノードへ還元します.
 * @param self
 * @return
 */
AST* ReduceParserBuffer(Parser* self);

/**
 * パーサーからASTを取り上げて解放させないようにします.
 * 解析が終わった後、まだASTが必要ならこれを使用します。
 * @param self
 * @return
 */
AST* ReleaseParserAST(Parser* self);

/**
 * エラー発生位置を設定します.
 * @param p
 */
void RelocationParserError(Parser* p);
#endif // !SIGNAL_PARSE_PARSER_H
