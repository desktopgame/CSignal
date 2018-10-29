#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct ILUnaryOp;
struct GenericType;
struct Enviroment;

typedef struct ILNegativeOp {
	struct ILUnaryOp* Parent;
	OperatorType Type;
	int OperatorIndex;
} ILNegativeOp;

#define ILNegativeOp_new(type) (MallocILNegativeOp(type, __FILE__, __LINE__))
ILNegativeOp* MallocILNegativeOp(OperatorType type, const char* filename, int lineno);

struct GenericType* EvalILNegativeOp(ILNegativeOp * self, struct Enviroment * env, CallContext* cctx);

void GenerateILNegativeOp(ILNegativeOp* self, struct Enviroment* env, CallContext* cctx);

void LoadILNegativeOp(ILNegativeOp* self, struct Enviroment* env, CallContext* cctx);

void DeleteILNegativeOp(ILNegativeOp* self);

char* ILNegativeOpToString(ILNegativeOp* self, struct Enviroment* env);
#endif