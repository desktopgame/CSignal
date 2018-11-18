//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_not_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NOT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../../il/call_context.h"
struct ILUnaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILNotOp {
	struct ILUnaryOp* Parent;
	bc_OperatorType Type;
	int OperatorIndex;
} ILNotOp;

ILNotOp* NewILNotOp(bc_OperatorType type);

struct GenericType* EvalILNotOp(ILNotOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNotOp(ILNotOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILNotOp(ILNotOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNotOp(ILNotOp* self);

char* ILNotOpToString(ILNotOp* self, struct Enviroment* env);
#endif