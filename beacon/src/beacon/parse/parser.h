// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file parser.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_PARSE_PARSER_H
#define BEACON_PARSE_PARSER_H
#include <stdbool.h>
#include <stdint.h>
#include "../ast/ast.h"
#include "../util/string_buffer.h"
#include "../util/vector.h"
#include "yacc_input_type.h"

/**
 * 解析の結果を表す構造体.
 */
typedef enum bc_ParseResult {
        PARSE_AWAIT_T = -1,
        PARSE_COMPLETE_T = 0,
        PARSE_OPEN_ERROR_T,
        PARSE_SYNTAX_ERROR_T
} bc_ParseResult;

/**
 * Yacc/Bisonの解析結果を保存する構造体です.
 */
typedef struct bc_Parser {
        bc_AST* Root;
        bc_Buffer* LiteralBuffer;
        // char* source;
        char* SourceName;
        char* ErrorLineText;
        char* ErrorMessage;
        int ErrorLineIndex;
        int ErrorColumnIndex;
        bc_YaccInputType InputType;
        bc_ParseResult Result;
        int Lineno;
        bc_Vector* LinenoTable;
} bc_Parser;

/**
 * 文字列を入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
bc_Parser* bc_ParseString(const char* source);

/**
 * ファイルを入力として構文解析を実行します.
 * 必ず DestroyParser で解放する必要があります。
 * @param source
 * @return
 */
bc_Parser* bc_ParseFile(const char* filename);

/**
 * 現在のパーサーを返します.
 * @return
 */
bc_Parser* bc_GetCurrentParser();

/**
 * エラー情報とASTを解放します.
 * @param self
 */
void bc_DestroyParser(bc_Parser* self);

/**
 * 文字列バッファーをクリアします.
 * @param self
 */
void bc_ClearParserBuffer(bc_Parser* self);

/**
 * 文字列バッファーに一文字加算します.
 * @param self
 * @return
 */
void bc_AppendParserBuffer(bc_Parser* self, char ch);

/**
 * 文字列バッファーをリテラルノードへ還元します.
 * @param self
 * @return
 */
bc_AST* bc_ReduceParserBuffer(bc_Parser* self);

/**
 * パーサーからASTを取り上げて解放させないようにします.
 * 解析が終わった後、まだASTが必要ならこれを使用します。
 * @param self
 * @return
 */
bc_AST* bc_ReleaseParserAST(bc_Parser* self);

/**
 * エラー発生位置を設定します.
 * @param p
 */
void bc_RelocationParserError(bc_Parser* p);
#endif  // !SIGNAL_PARSE_PARSER_H
