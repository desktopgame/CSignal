#pragma once
#ifndef BEACON_AST_AST_NEW_FACTOR_H
#define BEACON_AST_AST_NEW_FACTOR_H
#include "ast.h"

/**
 * @param b
 * @return
 */
AST* NewASTBool(bool b);

/**
 * trueを表す要素を作成します.
 * @return
 */
AST* NewASTTrue();

/**
 * falseを表す要素を作成します.
 * @return
 */
AST* NewASTFalse();

/**
 * nullを表す要素を作成します.
 * @return
 */
AST* NewASTNull();

/**
 * ... as Int を表す要素を作成します.
 * @param afact
 * @param atypename
 * @return
 */
AST* NewASTAs(AST* afact, AST* atypename);

/**
 * 名前参照を表す要素を作成します.
 * 名前参照には identifier だけで構成される変数参照と、
 * 名前空間とクラス名を連結した 静的フィールド参照が存在します。
 * @param atypename
 * @return
 */
AST* NewASTNameReference(AST* atypename);

/**
 * 変数を表す要素を作成します.
 * @param a
 * @param atype_args
 * @return
 */
AST* NewASTVariable(AST* a, AST* atype_args);

/**
 * 変数を表す要素を作成します.
 * @param strv
 * @param atype_args
 * @return
 */
AST* NewASTVariableFromString(StringView strv, AST* atype_args);

/**
 * 関数呼び出し演算子を表す要素を作成します.
 * @param areceiver
 * @param aargs
 * @return
 */
AST* NewASTOpCall(AST* areceiver, AST* aargs);

/**
 * thisを表す因子を作成します.
 * @return
 */
AST* NewASTThis();

/**
 * superを表す因子を作成します.
 * @return
 */
AST* NewASTSuper();

/**
 * hoge.foo を表す因子を作成します.
 * @param afact
 * @param name
 * @param atype_args
 * @return
 */
AST* NewASTFieldAccess(AST* afact, StringView namev, AST* atype_args);

/**
 * new X::Y(...) を表す因子を作成します.
 * @param afqcn
 * @param atype_args
 * @parma argument_list
 * @return
 */
AST* NewASTNewInstance(AST* afqcn, AST* atype_args, AST* argument_list);

/**
 * a instanceof b を表す要素を作成します.
 * @param afact
 * @param atype
 * @return
 */
AST* NewASTInstanceTof(AST* afact, AST* atype);

/**
 * 明示的な二項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @param aarg
 * @return
 */
AST* NewASTExplicitBiOperator(AST* afact, OperatorType type, AST* aarg);

/**
 * 明示的な単項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @return
 */
AST* NewASTExplicitUOperator(AST* afact, OperatorType type);

/**
 * @param afact
 * @param aindex
 * @return
 */
AST* NewASTSubscriptAccess(AST* afact, AST* aindex);
#endif // !SIGNAL_AST_AST_NEW_FACTOR_H
