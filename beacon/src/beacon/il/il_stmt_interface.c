#include "il_stmt_interface.h"
#include "il_stmt_impl.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../vm/enviroment.h"
#include "../util/mem.h"
#include "il_print_layout.h"

il_stmt* il_stmt_malloc(il_stmt_type type, const char* filename, int lineno) {
	il_stmt* ret = mem_malloc(sizeof(il_stmt), filename, lineno);
	ret->type = type;
	ret->lineno = -1;
	return ret;
}

void il_stmt_generate(il_stmt * self, struct enviroment* env, call_context* cctx) {
	if(bc_error_last()) {
		return;
	}
	bc_error_file(env->context_ref->filename);
	bc_error_line(self->lineno);
	switch (self->type) {
		case ILSTMT_IF_T:
			il_stmt_if_generate(self->u.if_, env, cctx);
			//il_stmt_if_delete(self->u.if_);
			break;
		case ILSTMT_PROC_T:
			il_stmt_proc_generate(self->u.proc_, env, cctx);
			//il_stmt_proc_delete(self->u.proc_);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			il_stmt_variable_decl_generate(self->u.variable_decl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			il_stmt_variable_init_generate(self->u.variable_init, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			il_stmt_return_generate(self->u.return_, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			il_stmt_return_empty_generate(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			il_stmt_while_generate(self->u.while_, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			il_stmt_break_generate(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			il_stmt_continue_generate(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_generate(self->u.inferenced_type_init, env, cctx);
			break;
		case ILSTMT_TRY_T:
			il_stmt_try_generate(self->u.try_, env, cctx);
			break;
		case ILSTMT_THROW_T:
			il_stmt_throw_generate(self->u.throw_, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			il_stmt_assert_generate(self->u.bcassert_, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			il_stmt_defer_generate(self->u.defer_, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			il_stmt_yield_return_generate(self->u.yield_return, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			il_stmt_yield_break_generate(self->u.yield_break, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			il_stmt_inject_jni_generate(self->u.inject_jni, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
	enviroment_add_range(env, self->lineno);
}

void il_stmt_load(il_stmt * self, enviroment* env, call_context* cctx) {
	if(bc_error_last()) {
		return;
	}
	bc_error_file(env->context_ref->filename);
	bc_error_line(self->lineno);
	switch (self->type) {
		case ILSTMT_IF_T:
			il_stmt_if_load(self->u.if_, env, cctx);
			break;
		case ILSTMT_PROC_T:
			il_stmt_proc_load(self->u.proc_, env, cctx);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			il_stmt_variable_decl_load(self->u.variable_decl, env, cctx);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			il_stmt_variable_init_load(self->u.variable_init, env, cctx);
			break;
		case ILSTMT_RETURN_T:
			il_stmt_return_load(self->u.return_, env, cctx);
			break;
		case ILSTMT_RETURN_EMPTY_T:
			il_stmt_return_empty_load(NULL, env, cctx);
			break;
		case ILSTMT_WHILE_T:
			il_stmt_while_load(self->u.while_, env, cctx);
			break;
		case ILSTMT_BREAK_T:
			il_stmt_break_load(NULL, env, cctx);
			break;
		case ILSTMT_CONTINUE_T:
			il_stmt_continue_load(NULL, env, cctx);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_load(self->u.inferenced_type_init, env, cctx);
			break;
		case ILSTMT_TRY_T:
			il_stmt_try_load(self->u.try_, env, cctx);
			break;
		case ILSTMT_THROW_T:
			il_stmt_throw_load(self->u.throw_, env, cctx);
			break;
		case ILSTMT_ASSERT_T:
			il_stmt_assert_load(self->u.bcassert_, env, cctx);
			break;
		case ILSTMT_DEFER_T:
			il_stmt_defer_load(self->u.defer_, env, cctx);
			break;
		case ILSTMT_YIELD_RETURN_T:
			il_stmt_yield_return_load(self->u.yield_return, env, cctx);
			break;
		case ILSTMT_YIELD_BREAK_T:
			il_stmt_yield_break_load(self->u.yield_break, env, cctx);
			break;
		case ILSTMT_INJECT_JNI_T:
			il_stmt_inject_jni_load(self->u.inject_jni, env, cctx);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			break;
	}
}

void il_stmt_delete(il_stmt * self) {
	switch (self->type) {
		case ILSTMT_IF_T:
			il_stmt_if_delete(self->u.if_);
			break;
		case ILSTMT_PROC_T:
			il_stmt_proc_delete(self->u.proc_);
			break;
		case ILSTMT_VARIABLE_DECL_T:
			il_stmt_variable_decl_delete(self->u.variable_decl);
			break;
		case ILSTMT_VARIABLE_INIT_T:
			il_stmt_variable_init_delete(self->u.variable_init);
			break;
		case ILSTMT_RETURN_T:
			il_stmt_return_delete(self->u.return_);
			break;
		case ILSTMT_WHILE_T:
			il_stmt_while_delete(self->u.while_);
			break;
		case ILSTMT_BREAK_T:
			il_stmt_break_delete(NULL);
			break;
		case ILSTMT_CONTINUE_T:
			il_stmt_continue_delete(NULL);
			break;
		case ILSTMT_INFERENCED_TYPE_INIT_T:
			il_stmt_inferenced_type_init_delete(self->u.inferenced_type_init);
			break;
		case ILSTMT_TRY_T:
			il_stmt_try_delete(self->u.try_);
			break;
		case ILSTMT_THROW_T:
			il_stmt_throw_delete(self->u.throw_);
			break;
		case ILSTMT_ASSERT_T:
			il_stmt_assert_delete(self->u.bcassert_);
			break;
		case ILSTMT_DEFER_T:
			il_stmt_defer_delete(self->u.defer_);
			break;
		case ILSTMT_YIELD_RETURN_T:
			il_stmt_yield_return_delete(self->u.yield_return);
			break;
		case ILSTMT_YIELD_BREAK_T:
			//il_stmt_yield_break_delete(self->u.yield_break);
			break;
		case ILSTMT_INJECT_JNI_T:
			il_stmt_inject_jni_delete(self->u.inject_jni);
			break;
		default:
			//ERROR("ステートメントを開放出来ませんでした。");
			{ int x = 0; }
			break;
	}
	MEM_FREE(self);
}
