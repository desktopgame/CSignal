#include "il_factor_not_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../env/generic_type.h"
#include "../../../vm/enviroment.h"
#include "../../../env/namespace.h"
#include "../../il_factor_impl.h"
#include "../../../env/TYPE_IMPL.h"
#include "../../../env/operator_overload.h"
#include "../il_factor_unary_op_impl.h"

ILNotOp* NewILNotOp(bc_OperatorType type) {
	ILNotOp* ret = (ILNotOp*)MEM_MALLOC(sizeof(ILNotOp));
	ret->Parent = NULL;
	ret->Type = type;
	ret->OperatorIndex = -1;
	return ret;
}

GenericType* EvalILNotOp(ILNotOp * self, Enviroment * env, CallContext* cctx) {
	return TYPE2GENERIC(TYPE_BOOL);
}

void GenerateILNotOp(ILNotOp* self, Enviroment* env, CallContext* cctx) {
	if(self->OperatorIndex == -1) {
		GenerateILFactor(self->Parent->Arg, env, cctx);
		if(bc_GetLastPanic()) {
			return;
		}
		GenericType* gt = EvalILFactor(self->Parent->Arg, env, cctx);
		if(GENERIC2TYPE(gt) == TYPE_BOOL) {
			AddOpcodeBuf(env->Bytecode, OP_BNOT);
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->Parent->Arg, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILNotOp(ILNotOp* self, Enviroment* env, CallContext* cctx) {
	 LoadILFactor(self->Parent->Arg, env, cctx);
	GenericType* gt = EvalILFactor(self->Parent->Arg, env, cctx);
	if(GENERIC2TYPE(gt) != TYPE_BOOL) {
		self->OperatorIndex = GetIndexILUnaryOp(self->Parent, env, cctx);
	}
}

void DeleteILNotOp(ILNotOp* self) {
	MEM_FREE(self);
}

char* ILNotOpToString(ILNotOp* self, Enviroment* env) {
	return ILUnaryOpToString_simple(self->Parent, env);
}