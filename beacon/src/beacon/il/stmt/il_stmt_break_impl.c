#include "il_stmt_break_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include <stdio.h>

ILStatement * WrapILBreak() {
	ILStatement* ret = NewILStatement(ILSTMT_BREAK_T);
	return ret;
}

void GenerateILBreak(void * empty, Enviroment * env, CallContext* cctx) {
	if(cctx->Control.WhileStartTable->Length == 0) {
		bc_Panic(BCERROR_BREAK_AT_NOT_LOOP_T);
		return;
	}
	Label* lab = (Label*)TopVector(cctx->Control.WhileEndTable);
	AddOpcodeBuf(env->Bytecode, OP_GOTO);
	AddOpcodeBuf(env->Bytecode, lab);
}

void LoadILBreak(void * empty, Enviroment * env, CallContext* cctx) {
}

void DeleteILBreak(void * empty) {
}
