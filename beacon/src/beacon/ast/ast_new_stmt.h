#pragma once
#ifndef BEACON_AST_AST_NEW_STMT_H
#define BEACON_AST_AST_NEW_STMT_H
#include "ast.h"

/**
 * 実行可能な文を表す要素を作成します.
 */
#define ast_new_stmt(stmt) (MallocASTStmt(stmt, __FILE__, __LINE__))

/**
 * 実行可能な文を表す要素を作成します.
 * @param astmt
 * @param filename
 * @param lineno
 * @return
 */
AST* MallocASTStmt(AST* astmt, const char* filename, int lineno);

/**
 * 実行可能な文を表す要素を作成します. 
 * @param astmt
 * @param astmt_list
 * @return
 */
AST* NewASTStmtList(AST* astmt, AST* astmt_list);

/**
 * ifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
AST* NewASTIf(AST* acond, AST* abody);

/** 
 * elseを表す要素を作成します.
 * @param abody
 * @return
 */
AST* NewASTElse(AST* abody);

/**
 * if-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param afalseBody
 * @return
 */
AST* NewASTIfElse(AST* acond, AST* atrueBody, AST* afalseBody);

/**
 * if-elif... を表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @return
 */
AST* NewASTIfElifList(AST* acond, AST* atrueBody, AST* aelifList);

/**
 * if-elif...-elseを表す要素を作成します.
 * @param acond
 * @param atrueBody
 * @param aelifList
 * @param aelseBody
 * @param
 */
AST* NewASTIfElifListElse(AST* acond, AST* atrueBody, AST* aelifList, AST* aelseBody);

/**
 * elif...を表す要素を作成します.
 * @param aforward
 * @param atail
 * @return
 */
AST* NewASTElifList(AST* aforward, AST* atail);

/**
 * elifを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
AST* NewASTElif(AST* acond, AST* abody);

/**
 * whileを表す要素を作成します.
 * @param acond
 * @param abody
 * @return
 */
AST* NewASTWhile(AST* acond, AST* abody);

/** 
 * ループから抜けるステートメントを作成します.
 * @return
 */
AST* NewASTBreak();

/**
 * 次のループまでスキップするステートメントを作成します.
 * @return
 */
AST* NewASTContinue();

/**
 * 値を返却するステートメントを作成します.
 * @param afact
 * @return
 */
AST* NewASTReturn(AST* afact);

/**
 * @return
 */
AST* NewASTReturnEmpty();

/**
 * 例外をスローするステートメントを作成します.
 * @param afact
 * @return
 */
AST* NewASTThrow(AST* afact);

/**
 * 例外が発生するかもしれない処理を囲うステートメント.
 * @param abody
 * @param acatch_list
 */
AST* NewASTTry(AST* abody, AST* acatch_list);

/**
 * 例外を捕捉するステートメントを作成します.
 * @param typename
 * @param snamev
 * @param abody
 * @return
 */
AST* NewASTCatch(AST* stypename, StringView snamev, AST* abody);

/**
 * キャッチ節の一覧を作成します.
 * @param acatch
 * @param acatch_list
 * @return
 */
AST* NewASTCatchList(AST* acatch, AST* acatch_list);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @return
*/
AST* NewASTArgument(AST* afactor);

/**
* 実引数を表す要素を作成します.
* @param afactor
* @param aargument_list
* @return
*/
AST* NewASTArgumentList(AST* factor, AST* argument_list);

/**
 * 完全クラス名(XX::YY::Foo)を表す要素を作成します.
 * @param apart_list
 * @param class_name
 * @return
 */
AST* NewASTFQCN(AST* part_list, StringView class_namev);

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 */
#define NewASTFQCN_part(name) (MallocASTFQCNPart(name, __FILE__, __LINE__))

/**
 * 完全修飾クラス名の 1節 を表す要素を作成します.
 * @param name
 * @param filename
 * @param lineno
 * @return
 */
AST* MallocASTFQCNPart(StringView namev, const char* filename, int lineno);

/**
 * 完全修飾クラス名の名前空間部分(XX::YY::)の一覧を表す要素を作成します.
 * @param apart
 * @param apart_list
 * @return
 */
AST* NewASTFQCNPartList(AST* part, AST* part_list);

/**
 * X::Y y; を表す要素を作成します.
 * @param atype
 * @param namev
 * @return
 */
AST* NewASTVariableDecl(AST* type, StringView namev);

/**
 * X::Y y = new X::Y() のような初期化を表す要素を作成します.
 * @param atype
 * @param namev
 * @param afact
 * @return
 */
AST* NewASTVariableInit(AST* type, StringView namev, AST* fact);

/**
 * var y = new X::Y() のような初期化を表す要素を作成します.
 * @param name
 * @param afact
 * @return
 */
AST* NewASTInferencedTypeInit(StringView namev, AST* fact);

/**
 * assert 条件 を表す要素を作成します.
 * @param afact
 * @param amsg
 * @return
 */
AST* NewASTAssert(AST* afact, AST* amsg);

/**
 * 強制実行を表す要素を作成します.
 * @param astmt
 * @return
 */
AST* NewASTDefer(AST* astmt);

/**
 * コルーチンの区切りを表す要素を作成します.
 * @param afact
 * @return
 */
AST* NewASTYieldReturn(AST* afact);

/**
 * コルーチンの終了を表す要素を作成します.
 * @return
 */
AST* NewASTYieldBreak();

/**
 * Javaから beacon が実行される時、事前に定義されたテーブルを注入するためのノード.
 * @param namev 変数名
 * @param avalue 値
 * @return
 */
AST* NewASTInject(StringView namev, AST* avalue);
#endif // !SIGNAL_AST_AST_NEW_STMT_H
