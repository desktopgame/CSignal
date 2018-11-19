#include "il_factor_this_impl.h"
#include <stdio.h>
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../vm/enviroment.h"
#include "../../env/type_interface.h"
#include "../../env/method.h"
#include "../call_context.h"
#include "../../error.h"
#include <assert.h>

static void check_context(ILThis * self, Enviroment * env, CallContext* cctx);

ILThis* NewILThis() {
	ILThis* ret = (ILThis*)MEM_MALLOC(sizeof(ILThis));
	ret->Resolved = NULL;
	return ret;
}

void GenerateILThis(ILThis * self, Enviroment * env, CallContext* cctx) {
	AddOpcodeBuf(env->Bytecode, OP_THIS);
}

void LoadILThis(ILThis * self, Enviroment * env, CallContext* cctx) {
	check_context(self, env, cctx);
}

bc_GenericType* EvalILThis(ILThis * self, Enviroment * env, CallContext* cctx) {
	return GetTypeCContext(cctx)->GenericSelf;
}

char* ILThisToString(ILThis* self, Enviroment* env) {
	return bc_Strdup("this");
}

void DeleteILThis(ILThis * self) {
	MEM_FREE(self);
}
//private
static void check_context(ILThis * self, Enviroment * env, CallContext* cctx) {
	if(cctx->Tag != CALL_METHOD_T) {
		return;
	}
	bc_Method* met = GetMethodCContext(cctx);
	if(bc_IsStaticModifier(met->Modifier)) {
		bc_Panic(BCERROR_ACCESS_TO_THIS_AT_STATIC_METHOD_T,
			Ref2Str(bc_GetTypeName(met->Parent)),
			Ref2Str(met->Name)
		);
	}
}