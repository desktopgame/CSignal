#pragma once
#ifndef BEACON_AST_AST_NEW_FACTOR_H
#define BEACON_AST_AST_NEW_FACTOR_H
#include "ast.h"

/**
 * trueを表す要素を作成します.
 * @return
 */
ast* ast_new_true();

/**
 * falseを表す要素を作成します.
 * @return
 */
ast* ast_new_false();

/**
 * nullを表す要素を作成します.
 * @return
 */
ast* ast_new_null();

/**
 * ... as Int を表す要素を作成します.
 * @param afact
 * @param atypename
 * @return
 */
ast* ast_new_as(ast* afact, ast* atypename);

/**
 * キャストを表す要素を作成します.
 * @param atypename
 * @param afact
 * @return
 */
ast* ast_new_cast(ast* atypename, ast* afact);

/**
 * 前置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_inc(ast* a);

/**
 * 前置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_pre_dec(ast* a);

/**
 * 後置きインクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_inc(ast* a);

/**
 * 後置きデクリメントを表す要素を作成します.
 * @param a
 * @return
 */
ast* ast_new_post_dec(ast* a);

/**
 * 名前参照を表す要素を作成します.
 * 名前参照には identifier だけで構成される変数参照と、
 * 名前空間とクラス名を連結した 静的フィールド参照が存在します。
 * @param atypename
 * @return
 */
ast* ast_new_name_reference(ast* atypename);

/**
 * 変数を表す要素を作成します.
 * @param a
 * @param atype_args
 * @return
 */
ast* ast_new_variable(ast* a, ast* atype_args);

/**
 * 変数を表す要素を作成します.
 * @param strv
 * @param atype_args
 * @return
 */
ast* ast_new_variable_fromstr(string_view strv, ast* atype_args);

/**
 * 関数呼び出し演算子を表す要素を作成します.
 * @param areceiver
 * @param aargs
 * @return
 */
ast* ast_new_op_call(ast* areceiver, ast* aargs);

/**
 * thisを表す因子を作成します.
 * @return
 */
ast* ast_new_this();

/**
 * superを表す因子を作成します.
 * @return
 */
ast* ast_new_super();

/**
 * hoge.foo を表す因子を作成します.
 * @param afact
 * @param name
 * @param atype_args
 * @return
 */
ast* ast_new_field_access(ast* afact, string_view namev, ast* atype_args);

/**
 * new X::Y(...) を表す因子を作成します.
 * @param afqcn
 * @param atype_args
 * @parma argument_list
 * @return
 */
ast* ast_new_new_instance(ast* afqcn, ast* atype_args, ast* argument_list);

/**
 * a instanceof b を表す要素を作成します.
 * @param afact
 * @param atype
 * @return
 */
ast* ast_new_instanceof(ast* afact, ast* atype);

/**
 * 明示的な二項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @param aarg
 * @return
 */
ast* ast_new_explicit_bioperator(ast* afact, operator_type type, ast* aarg);

/**
 * 明示的な単項演算の呼び出しを表す要素を作成します.
 * @param afact
 * @param type
 * @return
 */
ast* ast_new_explicit_uoperator(ast* afact, operator_type type);

/**
 * ラムダを表す要素を作成します.
 * @param aparameter_list
 * @param areturn
 * @param abody
 * @return
 */
ast* ast_new_lambda(ast* aparameter_list, ast* areturn, ast* abody);

/**
 * @param afact
 * @param aindex
 * @return
 */
ast* ast_new_subscript_access(ast* afact, ast* aindex);
#endif // !SIGNAL_AST_AST_NEW_FACTOR_H
