#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_LOGIC_OP_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"

struct il_factor_binary_op;
struct GenericType;
struct Enviroment;
typedef struct il_factor_logic_op {
	struct il_factor_binary_op* parent;
	OperatorType type;
	int operator_index;
} il_factor_logic_op;

il_factor_logic_op* NewILLogicOp(OperatorType type);

struct GenericType* EvalILLogicOp(il_factor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void GenerateILLogicOp(il_factor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void LoadILLogicOp(il_factor_logic_op* self, struct Enviroment* env, CallContext* cctx);

void DeleteILLogicOp(il_factor_logic_op* self);

char* ILLogicOpToString(il_factor_logic_op* self, struct Enviroment* env);
#endif