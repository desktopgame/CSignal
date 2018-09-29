#pragma once
#ifndef BEACON_VM_OPCODE_H
#define BEACON_VM_OPCODE_H
#include "../util/vector.h"
#include <stdio.h>

/**
 * 命令の一覧です.
 */
typedef enum opcode {
	OP_IADD = 1,
	OP_ISUB,
	OP_IMUL,
	OP_IDIV,
	OP_IMOD,
	OP_IBIT_OR,
	OP_ILOGIC_OR,
	OP_IBIT_AND,
	OP_ILOGIC_AND,
	OP_IEQ,
	OP_INOTEQ,
	OP_IGT,
	OP_IGE,
	OP_ILT,
	OP_ILE,
	OP_ILSH,
	OP_IRSH,
	OP_IEXCOR,
	OP_IFLIP,

	OP_CEQ,
	OP_CNOTEQ,
	OP_CGT,
	OP_CGE,
	OP_CLT,
	OP_CLE,

	OP_DADD,
	OP_DSUB,
	OP_DMUL,
	OP_DDIV,
	OP_DMOD,

	OP_DEQ,
	OP_DNOTEQ,
	OP_DGT,
	OP_DGE,
	OP_DLT,
	OP_DLE,

	OP_INEG,

	OP_DNEG,

	OP_BNOT,
	OP_BBIT_OR,
	OP_BLOGIC_OR,
	OP_BBIT_AND,
	OP_BLOGIC_AND,
	OP_BEXCOR,
	OP_BFLIP,

	OP_ICONST,
	OP_DCONST,
	OP_CCONST,
	OP_SCONST,
	OP_TRUE,
	OP_FALSE,
	OP_NULL,
	OP_RETURN,
	OP_TRY_ENTER,
	OP_TRY_EXIT,
	OP_THROW,
	OP_TRY_CLEAR,
	OP_DEFER_ENTER,
	OP_DEFER_EXIT,
	OP_DEFER_REGISTER,
	OP_HEXCEPTION,
	OP_INSTANCEOF,

	OP_DUP,
	OP_POP,
	OP_NOP,

	OP_PUT_FIELD,
	OP_GET_FIELD,

	OP_PUT_STATIC,
	OP_GET_STATIC,

	OP_PUT_PROPERTY,
	OP_GET_PROPERTY,
	OP_PUT_STATIC_property,
	OP_GET_STATIC_property,

	//op_lookup,
	//op_glookup,
	OP_STORE,
	OP_LOAD,
	OP_DOWN_AS,
	OP_UP_AS,

	OP_CHAIN_THIS,
	OP_CHAIN_SUPER,
	OP_NEW_OBJECT,
	OP_ALLOC_FIELD,
	OP_NEW_INSTANCE,
	OP_THIS,
	OP_SUPER,
	OP_INVOKEVIRTUAL,
	OP_INVOKESTATIC,
	OP_INVOKESPECIAL,
	OP_INVOKEINTERFACE,
	OP_INVOKEOPERATOR,

	OP_CORO_INIT,
	OP_CORO_NEXT,
	OP_CORO_EXIT,
	OP_CORO_RESUME,
	OP_CORO_CURRENT,
	OP_CORO_PARAMETER,
	OP_CORO_SWAP_SELF,

	OP_GENERIC_ADD,
	OP_GENERIC_ENTER,
	OP_GENERIC_UNIQUE_TYPE,
	OP_GENERIC_INSTANCE_TYPE,
	OP_GENERIC_STATIC_TYPE,
	OP_GENERIC_EXIT,

	OP_BREAKPOINT,

	OP_GOTO,
	OP_GOTO_if_true,
	OP_GOTO_if_false,
	OP_SIZE,
} opcode;

/**
 * オペコードを出力します.
 * @param source
 * @param index
 */
int opcode_print(Vector* source, int index);

/**
 * オペコードを出力します.
 * @param fp
 * @param source
 * @param index
 */
int opcode_fprint(FILE* fp, Vector* source, int index);
#endif // !SIGNAL_VM_OPCODE_H
