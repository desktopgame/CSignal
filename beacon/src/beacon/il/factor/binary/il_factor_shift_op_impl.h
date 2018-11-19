//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_shift_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct bc_GenericType;
struct Enviroment;
struct ILBinaryOp;
typedef struct ILShiftOp {
	struct ILBinaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} ILShiftOp;

ILShiftOp* NewILShiftOp(bc_OperatorType type);

struct bc_GenericType* EvalILShiftOp(ILShiftOp * self, struct Enviroment* env, CallContext* cctx);

void GenerateILShiftOp(ILShiftOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILShiftOp(ILShiftOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILShiftOp(ILShiftOp* self);

char* ILShiftOpToString(ILShiftOp* self, struct Enviroment* env);
#endif