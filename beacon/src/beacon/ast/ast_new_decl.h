// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file ast_new_decl.h
 * @brief ソースコード中で宣言に関するAST生成関数を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_AST_AST_NEW_DECL_H
#define BEACON_AST_AST_NEW_DECL_H
#include "access_level.h"
#include "ast.h"
#include "constructor_chain_type.h"
#include "modifier_type.h"
#include "operator_type.h"

/**
 * 名前空間を表す要素を作成します.
 * @param anamespace_path
 * @param abody
 * @return
 */
bc_AST* bc_NewASTNamespaceDecl(bc_AST* anamespace_path, bc_AST* abody);

/**
 * 名前空間の内側に定義された名前空間を表す要素を作成します.
 * @param anamespace_path
 * @param abody
 * @return
 */
bc_AST* bc_NewASTNamespaceNamespaceDecl(bc_AST* anamespace_path, bc_AST* abody);

/**
 * 名前空間の内側に含めることが出来る定義の一覧を作成します.
 * @param aforward
 * @param alist
 * @return
 */
bc_AST* bc_NewASTNamespaceMemberDeclList(bc_AST* aforward, bc_AST* alist);

/**
 * 抽象クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 */
bc_AST* bc_NewASTAbstractClassDecl(bc_AST* aclass_name, bc_AST* aextend_list,
                                   bc_AST* amember_list);

/**
 * クラス宣言を表す要素を作成します.
 * @param aclass_name
 * @param aextend_list
 * @param amember_list
 * @return
 */
bc_AST* bc_NewASTClassDecl(bc_AST* aclass_name, bc_AST* aextend_list,
                           bc_AST* amember_list);

/**
 * インターフェース宣言を表す要素を作成します.
 * @param ainterface_name
 * @param asuper_interface_list
 * @param amember_list
 * @return
 */
bc_AST* bc_NewASTInterfaceDecl(bc_AST* ainterface_name,
                               bc_AST* asuper_interface_list,
                               bc_AST* amember_list);

/**
 * 列挙宣言を表す要素を作成します.
 * @param aenum_name
 * @param aident_list
 * @return
 */
bc_AST* bc_NewASTEnumDecl(bc_StringView enum_name, bc_AST* aident_list);

/**
 * スーパークラスを表す要素を作成します.
 * @param afqcn
 * @return
 */
bc_AST* bc_NewASTSuperclass(bc_AST* afqcn);

/**
 * "アクセス修飾子とメンバー一覧のセット" のリストを返します.
 * @param amember_tree
 * @param amember_list
 * @return
 */
bc_AST* bc_NewASTAccessMemberTree(bc_AST* member_tree, bc_AST* member_list);

/**
 * アクセス修飾子とメンバーの一覧をセットにして返します.
 * @param level
 * @param amember_list
 * @return
 */
bc_AST* bc_NewASTAccessMemberList(bc_AccessLevel level, bc_AST* amember_list);

/**
 * アクセスレベルを表す要素を作成します.
 * @param level
 * @return
 */
bc_AST* bc_NewASTAccess(bc_AccessLevel level);

/**
 * 修飾子の一覧を表す要素を作成します.
 * @param amod
 * @param amod_list
 * @return
 */
bc_AST* bc_NewASTModifierList(bc_AST* amod, bc_AST* amod_list);

/**
 * 修飾子を表す要素を作成します.
 * @param type
 * @return
 */
bc_AST* bc_NewASTModifier(bc_ModifierType type);

/**
 * メンバーを表す要素を作成します.
 * @param amem
 * @return
 */
bc_AST* bc_NewASTMemberDecl(bc_AST* amem);

/**
 * メンバーを表す要素を作成します.
 * @param amember_list
 * @param amember
 * @param
 */
bc_AST* bc_NewASTMemberDeclList(bc_AST* amember_list, bc_AST* amember);

/**
 * フィールド宣言を表す要素を作成します.
 * @param amodifier
 * @param atypename
 * @param field_name
 * @param afact
 * @return
 */
bc_AST* bc_NewASTFieldDecl(bc_AST* amodifier, bc_AST* atypename,
                           bc_StringView field_name, bc_AST* afact);

/**
 * 関数宣言を表す要素を作成します.
 * @param function_namev
 * @param atypeparams
 * @parma aparameter_list
 * @param abody
 * @param areturn_type
 */
bc_AST* bc_NewASTFunctionDecl(bc_StringView function_namev, bc_AST* atypeparams,
                              bc_AST* aparameter_list, bc_AST* abody,
                              bc_AST* areturn_type);

/**
 * 引数のない関数宣言を表す要素を作成します.
 * @param function_name
 * @param atypeparams
 * @param abody
 * @param areturn_name
 * @return
 */
bc_AST* bc_NewASTFunctionDeclEmptyParams(bc_StringView function_name,
                                         bc_AST* atypeparams, bc_AST* abody,
                                         bc_AST* areturn_type);

/**
 * メソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_name
 * @param atype_parameter
 * @param aparameter_list
 * @param abody
 * @param areturn_GetTypeName
 * @return
 */
bc_AST* bc_NewASTMethodDecl(bc_AST* amodifier, bc_StringView func_name,
                            bc_AST* atype_parameter, bc_AST* aparameter_list,
                            bc_AST* abody, bc_AST* areturn_type);

/**
 * 引数のないメソッド宣言を表す要素を作成します.
 * @param amodifier
 * @param func_name
 * @param atype_parameter
 * @param abody
 * @param areturn_type
 * @return
 */
bc_AST* bc_NewASTMethodDeclEmptyParams(bc_AST* amodifier,
                                       bc_StringView func_name,
                                       bc_AST* atype_parameter, bc_AST* abody,
                                       bc_AST* areturn_type);

/**
 * コンストラクタ宣言を表す要素を作成します.
 * @param aparameter_list
 * @param aconstructor_chain
 * @param abody
 * @return
 */
bc_AST* bc_NewASTConstructorDecl(bc_AST* aparameter_list,
                                 bc_AST* aconstructor_chain, bc_AST* abody);

/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @param chain
 * @param aargument_list
 * @return
 */
bc_AST* bc_NewASTConstructorChain(bc_ConstructorChainType chain_type,
                                  bc_AST* aargument_list);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_name
 * @return
 */
bc_AST* bc_NewASTParameter(bc_AST* atypename,
                           bc_StringView parameter_access_name);

/**
 * 仮引数を表す要素を作成します.
 * @param atypename
 * @param parameter_access_name
 * @param aparameter_list
 * @return
 */
bc_AST* bc_NewASTParameterList(bc_AST* atypename,
                               bc_StringView parameter_access_name,
                               bc_AST* aparameter_list);

/**
 * クラスが実装するインターフェイスの一覧として使用される、
 * 型名の一覧を作成します.
 * @param atypename
 * @param atypename_list
 * @return
 */
bc_AST* bc_NewASTTypenameList(bc_AST* atypename, bc_AST* atypename_list);

/**
 * X::Y::C や C を型名でラップします.
 * @param afqcn
 * @param atype_args
 * @return
 */
bc_AST* bc_NewASTTypename(bc_AST* fqcn, bc_AST* atype_args);

/**
 * T や K V などの要素を作成します.
 * @param name
 * @param arule_list
 * @return
 */
bc_AST* bc_NewASTTypeParameter(bc_StringView name, bc_AST* arule_list);
bc_AST* bc_NewASTTypeInParameter(bc_StringView name, bc_AST* arule_list);
bc_AST* bc_NewASTTypeOutParameter(bc_StringView name, bc_AST* arule_list);

/**
 * T や K V の要素のリストを作成します.
 * @param aparam
 * @param alist
 * @return
 */
bc_AST* bc_NewASTTypeParameterList(bc_AST* aparam, bc_AST* alist);

/**
 * Name<T> や Name<K, V> のような要素を作成します.
 * @param name
 * @param aparams
 * @return
 */
bc_AST* bc_NewASTParameterizedTypename(bc_StringView name, bc_AST* aparams);

/**
 * 型制約の一覧を表す要素を作成します.
 * @param arule_list
 * @return
 */
bc_AST* bc_NewASTTypeParameterRuleList(bc_AST* arule_list);

/**
 * 演算子オーバーロードを表す要素を作成します.
 * @param type
 * @param aparam_list
 * @param abody
 * @param areturn
 */
bc_AST* bc_NewASTOperatorOverload(bc_OperatorType type, bc_AST* aparam_list,
                                  bc_AST* abody, bc_AST* areturn);

/**
 * プロパティの set部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @areturn
 */
bc_AST* bc_NewASTPropSet(bc_AST* aacess, bc_AST* abody);

/**
 * プロパティの get部分 を表す要素を作成します.
 * @param aacess
 * @param abody
 * @return
 */
bc_AST* bc_NewASTPropGet(bc_AST* aacess, bc_AST* abody);

/**
 * プロパティ宣言を作成します.
 * @param amodifier
 * @param atypename
 * @param namev
 * @param aset
 * @param aget
 */
bc_AST* bc_NewASTPropDecl(bc_AST* amodifier, bc_AST* atypename,
                          bc_StringView name, bc_AST* aset, bc_AST* aget);
#endif  // !SIGNAL_AST_AST_NEW_DECL_H
