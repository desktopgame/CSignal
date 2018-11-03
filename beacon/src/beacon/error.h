//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file error.h
 * @brief beaconインタプリタのエラー情報を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_ERROR_H
#define BEACON_ERROR_H
#include <stdarg.h>
#include <stdio.h>
#include "util/string_pool.h"

#define BC_ERROR() if(GetLastBCError()) return
#define BC_ERROR_RET(a) if(GetLastBCError()) return a
/**
 * beaconインタプリタがソース解析中に検出したエラーを表す列挙.
 */
typedef enum BCErrorID {
	BCERROR_NONE_T = 0,
	BCERROR_GENERIC_T,
	BCERROR_PARSE_T,
	BCERROR_REQUIRE_NOT_FOUND_T,
	BCERROR_OVERWRAP_PARAMETER_NAME_T,
	BCERROR_OVERWRAP_TYPE_TYPE_PARAMETER_NAME_T,
	BCERROR_OVERWRAP_METHOD_TYPE_PARAMETER_NAME_T,
	BCERROR_OVERWRAP_VARIABLE_NAME_T,
	BCERROR_OVERWRAP_MODIFIER_T,
	BCERROR_OVERWRAP_FIELD_NAME_T,
	BCERROR_OVERWRAP_PROPERTY_NAME_T,

	BCERROR_NATIVE_FIELD_T,
	BCERROR_ABSTRACT_FIELD_T,
	BCERROR_OVERRIDE_FIELD_T,

	BCERROR_STATIC_OVERRIDE_METHOD_T,
	BCERROR_ABSTRACT_OVERRIDE_METHOD_T,
	BCERROR_ABSTRACT_STATIC_METHOD_T,

	BCERROR_EMPTY_STMT_METHOD_T,
	BCERROR_NOT_EMPTY_STMT_METHOD_T,

	BCERROR_RETURN_VALUE_VOID_METHOD_T,
	BCERROR_NOT_RETURN_VALUE_NOT_VOID_METHOD_T,
	BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T,

	BCERROR_YIELD_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_T,

	BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
	BCERROR_WHILE_EXPR_TYPE_OF_NOT_BOOL_T,

	BCERROR_BREAK_AT_NOT_LOOP_T,
	BCERROR_CONTINUE_AT_NOT_LOOP_T,

	BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
	BCERROR_ACCESS_TO_SUPER_AT_STATIC_METHOD_T,

	BCERROR_ASSIGN_TO_FINAL_FIELD_T,
	BCERROR_NOT_DEFAULT_VALUE_STATIC_FINAL_FIELD_T,
	BCERROR_NOT_INITIAL_FIELD_NOT_INITIALIZED_AT_CTOR_T,
	BCERROR_FIELD_DEFAULT_VALUE_NOT_COMPATIBLE_TO_FIELD_TYPE_T,
	BCERROR_LHS_IS_NOT_SUBSCRIPT_T,

	BCERROR_ARG_COUNT_NOT2_BIOPERATOR_T,
	BCERROR_ARG_COUNT_NOT1_UOPERATOR_T,
	BCERROR_ARG_COUNT_NOT2_SUBSCRIPT_SET_OP_T,
	BCERROR_ARG_COUNT_NOT1_SUBSCRIPT_GET_OP_T,
	BCERROR_RETURN_TYPE_NOT_BOOL_COMPARE_OPERATOR_T,
	BCERROR_RETURN_TYPE_NOT_BOOL_NOT_OPERATOR_T,
	BCERROR_RETURN_TYPE_NOT_EQUAL_NEGATIVE_OPERATOR_T,

	BCERROR_THROWN_NOT_EXCEPTION_TYPE_T,

	BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
	BCERROR_ASSIGN_NOT_COMPATIBLE_FIELD_T,
	BCERROR_ASSIGN_NOT_COMPATIBLE_PROPERTY_T,

	BCERROR_AUTO_CHAIN_CTOR_NOT_FOUND_T,
	BCERROR_EXPLICIT_CHAIN_CTOR_NOT_FOUND_T,

	BCERROR_NEW_INSTANCE_UNDEFINED_CLASS_T,
	BCERROR_REF_UNDEFINED_LOCAL_VARIABLE_T,

	BCERROR_INVOKE_BOUND_UNDEFINED_METHOD_T,
	BCERROR_INVOKE_INSTANCE_UNDEFINED_METHOD_T,
	BCERROR_INVOKE_STATIC_UNDEFINED_METHOD_T,

	BCERROR_NEW_INSTANCE_UNDEFINED_CTOR_T,

	BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
	BCERROR_UNDEFINED_ARITHMETIC_OPERATOR_T,
	BCERROR_UNDEFINED_SHIFT_OPERATOR_T,
	BCERROR_UNDEFINED_BIT_OPERATOR_T,
	BCERROR_UNDEFINED_LOGIC_OPERATOR_T,
	BCERROR_UNDEFINED_EXCOR_OPERATOR_T,

	BCERROR_VOID_ASSIGN_T,
	BCERROR_VOID_DECL_T,

	BCERROR_CAST_NOT_COMPATIBLE_T,

	BCERROR_UNDEFINED_TYPE_DECL_T,
	BCERROR_UNDEFINED_TYPE_STATIC_INVOKE_T,
	BCERROR_UNDEFINED_NAME_BOUND_INVOKE_T,
	BCERROR_UNDEFINED_PROPERTY_T,
	BCERROR_ASSIGN_TO_INVOKE_T,

	BCERROR_INTERFACE_HAS_FIELD_T,
	BCERROR_INTERFACE_HAS_CTOR_T,
	BCERROR_INTERFACE_HAS_OPOV_T,

	BCERROR_INTERFACE_HAS_PRIVATE_MEMBER_T,

	BCERROR_CONSTRUCT_ABSTRACT_TYPE_T,
	BCERROR_CAN_T_RESOLVE_LAMBDA_T,
	BCERROR_NOT_FUNCTIONAL_INTERFACE_T,
	BCERROR_CLASS_FIRST_T,
	BCERROR_MULTI_EQINTERFACE_T,
	BCERROR_INTERFACE_ONLY_T,
	BCERROR_CHAIN_T,
	BCERROR_ABSTRACT_METHOD_BY_T,
	BCERROR_NOT_IMPLEMENT_INTERFACE_T,
	BCERROR_NOT_IMPLEMENT_ABSTRACT_METHOD_T,
	BCERROR_PRIVATE_OPERATOR_T,
	BCERROR_INVALID_PROPERTY_DECL_T,
	BCERROR_CAN_T_ACCESS_FIELD_T,
	BCERROR_CAN_T_ACCESS_PROPERTY_T,
	BCERROR_INVALID_ACCESS_LEVEL_OF_PROPERTY_T,
	BCERROR_SPECIFIED_BOTH_PROPERTY_ACCESSOR_T,
} BCErrorID;

/**
 * 指定のIDでエラーを発生させます.
 * @param id
 * @param ...
 */
void ThrowBCError(BCErrorID id, ...);

/**
 * 指定のIDでエラーを発生させます.
 * @param id
 * @param ap
 */
void VthrowBCError(BCErrorID id, va_list ap);

/**
 * エラーから文字列を作成します.
 * @param block
 * @param id
 * @param ...
 * @return
 */
char* FormatBCError(BCErrorID id, ...);
/**
 * エラーから文字列を作成します.
 * @param block
 * @param id
 * @param ap
 * @return
 */
char* VformatBCError(BCErrorID id, va_list ap);

/**
 * エラーフラグをクリアします.
 */
void ClearBCError();

/**
 * エラーが発生したファイルを記録します.
 * @param filename
 */
void SetBCErrorFile(const char* filename);

/**
 * エラーが発生した行を記録します.
 * @param lineno
 */
void SetBCErrorLine(int lineno);

/**
 * エラーが発生した列を記録します.
 * @param column
 */
void SetBCErrorColumn(int column);

/**
 * 最後に発生したエラーメッセージを返します.
 * @return
 */
StringView GetBCErrorMessage();

/**
 * 現在発生中のエラーを返します.
 * @return
 */
BCErrorID GetLastBCError();
#endif