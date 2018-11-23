// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file ast_new_factor.h
 * @brief 計算可能なAST要素の生成関数を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_AST_AST_NEW_FACTOR_H
#define BEACON_AST_AST_NEW_FACTOR_H
#include "ast.h"

/**
 * @param b
 * @return
 */
bc_AST* bc_NewASTBool(bool b);

/**
 * trueを表す要素を作成します.
 * @return
 */
bc_AST* bc_NewASTTrue();

/**
 * falseを表す要素を作成します.
 * @return
 */
bc_AST* bc_NewASTFalse();

/**
 * nullを表す要素を作成します.
 * @return
 */
bc_AST* bc_NewASTNull();

/**
 * ... as Int を表す要素を作成します.
 * @param afact
 * @param atypename
 * @return
 */
bc_AST* bc_NewASTAs(bc_AST* afact, bc_AST* atypename);

/**
 * 名前参照を表す要素を作成します.
 * 名前参照には identifier だけで構成される変数参照と、
 * 名前空間とクラス名を連結した 静的フィールド参照が存在します。
 * @param atypename
 * @return
 */
bc_AST* bc_NewASTNameReference(bc_AST* atypename);

/**
 * 変数を表す要素を作成します.
 * @param a
 * @param atype_args
 * @return
 */
bc_AST* bc_NewASTVariable(bc_AST* a, bc_AST* atype_args);

/**
 * 変数を表す要素を作成します.
 * @param str
 * @param atype_args
 * @return
 */
bc_AST* bc_NewASTVariableFromString(bc_StringView str, bc_AST* atype_args);

/**
 * 関数呼び出し演算子を表す要素を作成します.
 * @param areceiver
 * @param aargs
 * @return
 */
bc_AST* bc_NewASTOpCall(bc_AST* areceiver, bc_AST* aargs);

/**
 * thisを表す因子を作成します.
 * @return
 */
bc_AST* bc_NewASTThis();

/**
 * superを表す因子を作成します.
 * @return
 */
bc_AST* bc_NewASTSuper();

/**
 * hoge.foo を表す因子を作成します.
 * @param afact
 * @param name
 * @param atype_args
 * @return
 */
bc_AST* bc_NewASTFieldAccess(bc_AST* afact, bc_StringView name,
                             bc_AST* atype_args);

/**
 * new X::Y(...) を表す因子を作成します.
 * @param afqcn
 * @param atype_args
 * @parma argument_list
 * @return
 */
bc_AST* bc_NewASTNewInstance(bc_AST* afqcn, bc_AST* atype_args,
                             bc_AST* argument_list);

/**
 * a instanceof b を表す要素を作成します.
 * @param afact
 * @param atype
 * @return
 */
bc_AST* bc_NewASTInstanceTof(bc_AST* afact, bc_AST* atype);

/**
 * 明示的な二項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @param aarg
 * @return
 */
bc_AST* bc_NewASTExplicitBiOperator(bc_AST* afact, bc_OperatorType type,
                                    bc_AST* aarg);

/**
 * 明示的な単項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @return
 */
bc_AST* bc_NewASTExplicitUOperator(bc_AST* afact, bc_OperatorType type);

/**
 * @param afact
 * @param aindex
 * @return
 */
bc_AST* bc_NewASTSubscriptAccess(bc_AST* afact, bc_AST* aindex);
#endif  // !SIGNAL_AST_AST_NEW_FACTOR_H
