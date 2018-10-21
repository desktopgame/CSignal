#ifndef BEACON_AST_OPERATOR_TYPE_H
#define BEACON_AST_OPERATOR_TYPE_H
#include <stdio.h>
#include <stdbool.h>

/**
 * 演算子のカテゴリを表す列挙.
 */
typedef enum OperatorCategory {
	OPERATOR_CARITHMERIC_T,
	OPERATOR_CLOGIC_T,
	OPERATOR_CCOMPARE_T,
	OPERATOR_CSHIFT_T,
	OPERATOR_CCHILDA_T,
	OPERATOR_CNEGATIVE_T,
	OPERATOR_CNOT_T,
	OPERATOR_CEXCOR_T,
} OperatorCategory;

/**
 * 演算子の種類を表す列挙.
 */
typedef enum OperatorType {
	OPERATOR_ADD_T,
	OPERATOR_SUB_T,
	OPERATOR_MUL_T,
	OPERATOR_DIV_T,
	OPERATOR_MOD_T,

	OPERATOR_BIT_OR_T,
	OPERATOR_BIT_AND_T,

	OPERATOR_LOGIC_OR_T,
	OPERATOR_LOGIC_AND_T,

	OPERATOR_EQ_T,
	OPERATOR_NOT_EQ_T,

	OPERATOR_GT_T,
	OPERATOR_GE_T,
	OPERATOR_LT_T,
	OPERATOR_LE_T,
	OPERATOR_LSHIFT_T,
	OPERATOR_RSHIFT_T,
	OPERATOR_EXCOR_T,

	OPERATOR_CHILDA_T,
	OPERATOR_NEGATIVE_T,
	OPERATOR_NOT_T,

	OPERATOR_SUB_SCRIPT_SET_T,
	OPERATOR_SUB_SCRIPT_GET_T,
} OperatorType;
/**
 * オペレータを文字列として出力します.
 * @param fp
 * @param self
 */
void FprintfOperator(FILE* fp, OperatorType self);

/**
 * オペレータを文字列にして返します.
 * @param self
 * @return
 */
char* OperatorToString(OperatorType self);

/**
 * オペレータが算術演算子なら true.
 * @param self
 * @return
 */
bool IsArithmeticOperator(OperatorType self);

/**
 * オペレータがビット演算子なら true.
 * @param self
 * @return
 */
bool IsBitOperator(OperatorType self);

/**
 * オペレータが論理演算子なら true.
 * @param self
 * @return
 */
bool IsLogicOperator(OperatorType self);

/**
 * オペレータが比較演算子なら true.
 * @param self
 * @return
 */
bool IsCompareOperator(OperatorType self);

/**
 * オペレータがシフト演算子なら true.
 * @param self
 * @return
 */
bool IsShiftOperator(OperatorType self);

/**
 * オペレータが二項演算子なら true.
 * @param self
 * @return
 */
bool Is2ArgOperator(OperatorType self);

/**
 * オペレータが単項演算子なら true.
 * @param self
 * @return
 */
bool Is1ArgOperator(OperatorType self);
#endif