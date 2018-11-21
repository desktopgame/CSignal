#include "il_stmt_variable_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include "../../env/class_loader.h"
#include "../../env/import_manager.h"
#include <stdio.h>
#include <assert.h>

bc_ILStatement * WrapILVariableInit(ILVariableInit * self) {
	bc_ILStatement* ret = (bc_ILStatement*)MEM_MALLOC(sizeof(ILVariableInit));
	ret->Type = ILSTMT_VARIABLE_INIT_T;
	ret->Kind.VariableInit = self;
	return ret;
}

ILVariableInit * NewILVariableInit(bc_StringView namev) {
	ILVariableInit* ret = (ILVariableInit*)MEM_MALLOC(sizeof(ILVariableInit));
	ret->Name = namev;
	ret->Value = NULL;
	ret->GCache = bc_NewGenericCache();
	return ret;
}

void GenerateILVariableInit(ILVariableInit * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_GenerateILFactor(self->Value, env, cctx);
	//宣言型と代入型が異なる場合
	bc_GenericType* ga = bc_EvalILFactor(self->Value, env, cctx);
	bc_GenericType* gb = bc_ResolveImportManager(NULL, self->GCache, cctx);
	//voidは代入できない
	assert(gb != NULL);
	BC_ERROR();
	if((ga->CoreType != NULL && ga->CoreType == BC_TYPE_VOID) ||
	   (gb->CoreType != NULL && gb->CoreType == BC_TYPE_VOID)) {
		   bc_Panic(BCERROR_VOID_ASSIGN_T);
		return;
	}
	int dist = bc_DistanceGenericType(gb, ga, cctx);
	if (dist < 0) {
		bc_Panic(BCERROR_ASSIGN_NOT_COMPATIBLE_LOCAL_T,
			bc_Ref2Str(self->Name)
		);
	}
	bc_AddOpcodeBuf(env->Bytecode, OP_STORE);
	bc_AddOpcodeBuf(env->Bytecode, self->Symbol->Index);
}

void LoadILVariableInit(ILVariableInit * self, bc_Enviroment * env, bc_CallContext* cctx) {
	bc_LoadILFactor(self->Value, env, cctx);
	if(bc_IsContainsSymbol(env->Symboles, self->Name)) {
		bc_Panic(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			bc_Ref2Str(self->Name)
		);
	}
	bc_GenericType* gt = bc_ResolveImportManager(NULL, self->GCache, cctx);
	if(gt == NULL) {
		bc_Panic(
			BCERROR_UNDEFINED_TYPE_DECL_T,
			bc_Ref2Str(self->GCache->FQCN->Name)
		);
		return;
	}
	bc_SymbolEntry* e = bc_EntrySymbolTable(
		env->Symboles,
		gt,
		self->Name
	);
	self->Symbol = e;
	assert(e->GType != NULL);
}

void DeleteILVariableInit(ILVariableInit * self) {
	bc_DeleteILFactor(self->Value);
	bc_DeleteGenericCache(self->GCache);
	MEM_FREE(self);
}
