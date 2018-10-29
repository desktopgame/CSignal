#include "il_factor_arithmetic_op_impl.h"
#include "../../../util/mem.h"
#include "../../../util/text.h"
#include "../../../util/string_buffer.h"
#include "../../../env/generic_type.h"
#include "../../../env/operator_overload.h"
#include "../../../vm/enviroment.h"
#include "../../il_factor_impl.h"
#include "../../../env/namespace.h"
#include "../../../env/TYPE_IMPL.h"
#include <assert.h>

static Opcode operator_to_iopcode(OperatorType type);
static Opcode operator_to_dopcode(OperatorType type);

ILArithmeticOp* NewILArithmeticOp(OperatorType type) {
	ILArithmeticOp* ret = (ILArithmeticOp*)MEM_MALLOC(sizeof(ILArithmeticOp));
	ret->Type = type;
	ret->Parent = NULL;
	ret->OperatorIndex = -1;
	return ret;
}

GenericType* EvalILArithmeticOp(ILArithmeticOp * self, Enviroment* env, CallContext* cctx) {
	GenericType* lgtype = EvalILFactor(self->Parent->Left, env, cctx);
	GenericType* rgtype = EvalILFactor(self->Parent->Right, env, cctx);
	assert(lgtype != NULL);
	assert(rgtype != NULL);
	type* cint = TYPE_INT;
	type* cdouble = TYPE_DOUBLE;
	if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
		return TYPE2GENERIC(cint);
	}
	if(IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
		return TYPE2GENERIC(cdouble);
	}
	//プリミティブ型同士でないのに
	//演算子オーバーロードもない
	if(self->OperatorIndex == -1) {
		ThrowBCError(BCERROR_UNDEFINED_COMPARE_OPERATOR_T,
			OperatorToString(self->Type)
		);
		return NULL;
	}
	OperatorOverload* operator_ov = GetOperatorOverloadClass(TYPE2CLASS(GENERIC2TYPE(lgtype)), self->OperatorIndex);
	return ApplyILBinaryOp(self->Parent, operator_ov->ReturnGType, env, cctx);
}

void GenerateILArithmeticOp(ILArithmeticOp* self, Enviroment* env, CallContext* cctx) {
	//演算子オーバーロードが見つからない
	if(self->OperatorIndex == -1) {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		if(IsIntIntBinaryOp(self->Parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_iopcode(self->Type));
		} else if(IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
			AddOpcodeBuf(env->Bytecode, (VectorItem)operator_to_dopcode(self->Type));
		} else {
			assert(false);
		}
	} else {
		GenerateILFactor(self->Parent->Right, env, cctx);
		GenerateILFactor(self->Parent->Left, env, cctx);
		AddOpcodeBuf(env->Bytecode, OP_INVOKEOPERATOR);
		AddOpcodeBuf(env->Bytecode, self->OperatorIndex);
	}
}

void LoadILArithmeticOp(ILArithmeticOp* self, Enviroment* env, CallContext* cctx) {
	if(!IsIntIntBinaryOp(self->Parent, env, cctx) &&
	   !IsDoubleDoubleBinaryOp(self->Parent, env, cctx)) {
		self->OperatorIndex = GetIndexILBinaryOp(self->Parent, env, cctx);
	}
}

void DeleteILArithmeticOp(ILArithmeticOp* self) {
	MEM_FREE(self);
}

char* ILArithmeticOpToString(ILArithmeticOp* self, Enviroment* env) {
	return ILBinaryOpToString_simple(self->Parent, env);
}
//static
static Opcode operator_to_iopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_IADD;
		case OPERATOR_SUB_T: return OP_ISUB;
		case OPERATOR_MUL_T: return OP_IMUL;
		case OPERATOR_DIV_T: return OP_IDIV;
		case OPERATOR_MOD_T: return OP_IMOD;
	}
	assert(false);
}

static Opcode operator_to_dopcode(OperatorType type) {
	switch(type) {
		case OPERATOR_ADD_T: return OP_DADD;
		case OPERATOR_SUB_T: return OP_DSUB;
		case OPERATOR_MUL_T: return OP_DMUL;
		case OPERATOR_DIV_T: return OP_DDIV;
		case OPERATOR_MOD_T: return OP_DMOD;
	}
	assert(false);
}