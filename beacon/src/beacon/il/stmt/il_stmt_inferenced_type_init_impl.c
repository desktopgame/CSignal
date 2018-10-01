#include "il_stmt_inferenced_type_init_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/symbol_entry.h"
#include "../../env/type_interface.h"
#include "../../env/namespace.h"
#include <stdio.h>
#include <string.h>

il_stmt * WrapILInferencedTypeInit(il_stmt_inferenced_type_init * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_INFERENCED_TYPE_INIT_T);
	ret->u.inferenced_type_init = self;
	return ret;
}

il_stmt_inferenced_type_init * NewILInferencedTypeInit(string_view namev) {
	il_stmt_inferenced_type_init* ret = (il_stmt_inferenced_type_init*)MEM_MALLOC(sizeof(il_stmt_inferenced_type_init));
	ret->namev = namev;
	ret->fact = NULL;
	return ret;
}

void GenerateILInferencedTypeInit(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	//右辺の方で宣言する
	GenerateILFactor(self->fact, env, cctx);
	AddOpcodeBuf(env->buf, OP_STORE);
	AddOpcodeBuf(env->buf, self->sym->index);
}

void LoadILInferencedTypeInit(il_stmt_inferenced_type_init * self, enviroment * env, call_context* cctx) {
	//代入するオブジェクトを計算
	LoadILFactor(self->fact, env, cctx);
	generic_type* gtp = EvalILFactor(self->fact, env, cctx);
	BC_ERROR();
	//voidは代入できない
	if(gtp->core_type != NULL &&
	   gtp->core_type == TYPE_VOID) {
		   ThrowBCError(BCERROR_VOID_ASSIGN_T);
		return;
	}
	//変数を登録
	if(IsContainsSymbol(env->sym_table, self->namev)) {
		ThrowBCError(BCERROR_OVERWRAP_VARIABLE_NAME_T,
			Ref2Str(self->namev)
		);
	}
	symbol_entry* e = EntrySymbolTable(
		env->sym_table,
		gtp,
		self->namev
	);
	self->sym = e;
}

void DeleteILInferencedTypeInit(il_stmt_inferenced_type_init * self) {
	DeleteILFactor(self->fact);
	MEM_FREE(self);
}
