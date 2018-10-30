//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_logic_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"

struct ILBinaryOp;
struct GenericType;
struct Enviroment;
typedef struct ILLogicOp {
	struct ILBinaryOp* Parent;
	OperatorType Type;
	int OperatorIndex;
} ILLogicOp;

ILLogicOp* NewILLogicOp(OperatorType type);

struct GenericType* EvalILLogicOp(ILLogicOp* self, struct Enviroment* env, CallContext* cctx);

void GenerateILLogicOp(ILLogicOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILLogicOp(ILLogicOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILLogicOp(ILLogicOp* self);

char* ILLogicOpToString(ILLogicOp* self, struct Enviroment* env);
#endif