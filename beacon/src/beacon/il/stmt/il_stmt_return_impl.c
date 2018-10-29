#include "il_stmt_return_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../env/method.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>

static void check_method_return(ILReturn * self, Enviroment * env, CallContext* cctx);

ILStatement * WrapILReturn(ILReturn * self) {
	ILStatement* ret = ILStatement_new(ILSTMT_RETURN_T);
	ret->u.return_ = self;
	return ret;
}

ILReturn * NewILReturn() {
	ILReturn* ret = (ILReturn*)MEM_MALLOC(sizeof(ILReturn));
	ret->fact = NULL;
	return ret;
}

void GenerateILReturn(ILReturn * self, Enviroment * env, CallContext* cctx) {
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->Bytecode, OP_RETURN);
}

void LoadILReturn(ILReturn * self, Enviroment * env, CallContext* cctx) {
	LoadILFactor(self->fact, env, cctx);
	BC_ERROR();
	check_method_return(self, env, cctx);
}

void DeleteILReturn(ILReturn * self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
//private
static void check_method_return(ILReturn * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	Method* m = GetMethodCContext(cctx);
	//戻り値が Void なのに値を返している
	if(m->ReturnGType->CoreType == TYPE_VOID) {
		ThrowBCError(BCERROR_RETURN_VALUE_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
		return;
	}
	//戻り値の型に互換性がない
	GenericType* retT =EvalILFactor(self->fact, env, cctx);
	if(retT->CoreType != TYPE_NULL &&
	   DistanceGenericType(m->ReturnGType, retT, cctx) < 0) {
		ThrowBCError(BCERROR_RETURN_VALUE_TYPE_IS_NOT_COMPATIBLE_NOT_VOID_METHOD_T,
			Ref2Str(GetTypeName(m->Parent)),
			Ref2Str(m->Name)
		);
	}
}