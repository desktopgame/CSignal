//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_childa_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_CHILDA_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct bc_ILUnaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct bc_ILChildaOp {
	struct bc_ILUnaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} bc_ILChildaOp;

bc_ILChildaOp* bc_NewILChildaOp(bc_OperatorType type);

struct bc_GenericType* bc_EvalILChildaOp(bc_ILChildaOp * self, struct bc_Enviroment * env, bc_CallContext* cctx);

void bc_GenerateILChildaOp(bc_ILChildaOp* self, struct bc_Enviroment* env, bc_CallContext* cctx);

void bc_LoadILChildaOp(bc_ILChildaOp* self, struct bc_Enviroment* env, bc_CallContext* cctx);

void bc_DeleteILChildaOp(bc_ILChildaOp* self);

char* bc_ILChildaOpToString(bc_ILChildaOp* self, struct bc_Enviroment* env);
#endif