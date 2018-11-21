#include "il_factor_explicit_binary_op_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/generic_type.h"
#include "../../env/TYPE_IMPL.h"
#include "../../env/operator_overload.h"
#include "../../vm/enviroment.h"
#include "../il_factor_impl.h"
#include <assert.h>

bc_ILFactor* WrapILExplicitBinaryOp(ILExplicitBinaryOp* self) {
	bc_ILFactor* ret = bc_NewILFactor(ILFACTOR_EXPLICIT_BINARY_OP_T);
	ret->Kind.ExpBinaryOp = self;
	return ret;
}

ILExplicitBinaryOp* NewILExplicitBinaryOp(bc_OperatorType type) {
	ILExplicitBinaryOp* ret = (ILExplicitBinaryOp*)MEM_MALLOC(sizeof(ILExplicitBinaryOp));
	ret->Type = type;
	ret->Receiver = NULL;
	ret->Arg = NULL;
	ret->Index = -1;
	return ret;
}

void GenerateILExplicitBinaryOp(ILExplicitBinaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Arg, env, cctx);
	bc_GenerateILFactor(self->Receiver, env, cctx);
	bc_AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
	bc_AddOpcodeBuf(env->Bytecode, self->Index);
}

void LoadILExplicitBinaryOp(ILExplicitBinaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Receiver, env, cctx);
	bc_LoadILFactor(self->Arg, env, cctx);
	self->Index = GetIndexILBinaryOp2(self->Receiver, self->Arg, self->Type, env, cctx);
	assert(self->Index != -1);
}

bc_GenericType* EvalILExplicitBinaryOp(ILExplicitBinaryOp* self, bc_Enviroment* env, bc_CallContext* cctx) {
	bc_GenericType* gt = bc_EvalILFactor(self->Receiver, env, cctx);
	bc_OperatorOverload* operator_ov = bc_GetOperatorOverloadClass(BC_TYPE2CLASS(bc_GENERIC2TYPE(gt)), self->Index);
	return operator_ov->ReturnGType;
}

void DeleteILExplicitBinaryOp(ILExplicitBinaryOp* self) {
	bc_DeleteILFactor(self->Receiver);
	bc_DeleteILFactor(self->Arg);
	MEM_FREE(self);
}