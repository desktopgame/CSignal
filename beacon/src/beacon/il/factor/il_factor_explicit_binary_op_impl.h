//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_explicit_binary_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#define BEACON_IL_FACTOR_IL_FACTOR_EXPLICIT_BINARY_OP_IMPL_H
#include "../../ast/operator_type.h"
#include "../call_context.h"
struct ILFactor;
struct Enviroment;
struct GenericType;

typedef struct ILExplicitBinaryOp {
	struct ILFactor* Receiver;
	struct ILFactor* Arg;
	OperatorType Type;
	int Index;
} ILExplicitBinaryOp;

struct ILFactor* WrapILExplicitBinaryOp(ILExplicitBinaryOp* self);

ILExplicitBinaryOp* NewILExplicitBinaryOp(OperatorType type);

void GenerateILExplicitBinaryOp(ILExplicitBinaryOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILExplicitBinaryOp(ILExplicitBinaryOp* self, struct Enviroment* env, CallContext* cctx);

struct GenericType* EvalILExplicitBinaryOp(ILExplicitBinaryOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILExplicitBinaryOp(ILExplicitBinaryOp* self);
#endif