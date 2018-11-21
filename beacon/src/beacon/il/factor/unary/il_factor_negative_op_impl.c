#include "il_factor_negative_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

ILNegativeOp* MallocILNegativeOp(bc_OperatorType type, const char* filename, int lineno) {
	ILNegativeOp* ret = (ILNegativeOp*)bc_MXMalloc(sizeof(ILNegativeOp), filename, lineno);
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

bc_GenericType* EvalILNegativeOp(ILNegativeOp * self, bc_Enviroment * env, bc_CallContext* cctx) {
	return bc_EvalILFactor(self->Parent->Arg, env, cctx);
}

void GenerateILNegativeOp(ILNegativeOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
	if(self->OperatorIndex == -1) {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		if(bc_GENERIC2TYPE(gt) == BC_TYPE_INT) {
			bc_AddOpcodeBuf(env->Bytecode, OP_INEG);
		} else if(bc_GENERIC2TYPE(gt) == BC_TYPE_DOUBLE) {
			bc_AddOpcodeBuf(env->Bytecode, OP_DNEG);
		} else {
			assert(false);
		}
	} else {
		bc_GenerateILFactor(self->Parent->Arg, env, cctx);
		bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		bc_AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILNegativeOp(ILNegativeOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gt = bc_EvalILFactor(self->Parent->Arg, env, cctx);
	if(bc_GENERIC2TYPE(gt) != BC_TYPE_INT &&
	   bc_GENERIC2TYPE(gt) != BC_TYPE_DOUBLE) {
		self->OperatorIndex = GetIndexILUnaryOp(self->Parent, env, cctx);
	}
}

void DeleteILNegativeOp(ILNegativeOp* self) {
	MEM_FREE(self);
}

char* ILNegativeOpToString(ILNegativeOp* self, bc_Enviroment* env) {
	return ILUnaryOpToString_simple(self->Parent, env);
}