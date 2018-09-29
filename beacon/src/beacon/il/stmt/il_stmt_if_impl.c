#include "il_stmt_if_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/namespace.h"
#include "../../vm/opcode_buf.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void il_stmt_elif_list_delete_impl(VectorItem item);
static void il_stmt_if_delete_stmt(VectorItem item);
static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx);

il_stmt * il_stmt_wrap_if(il_stmt_if * self) {
	il_stmt* ret = il_stmt_new(ILSTMT_IF_T);
	ret->u.if_ = self;
	return ret;
}

il_stmt_if * il_stmt_if_new() {
	il_stmt_if* ret = (il_stmt_if*)MEM_MALLOC(sizeof(il_stmt_if));
	ret->condition = NULL;
	ret->elif_list = NewVector();
	ret->else_body = il_stmt_else_new();
	ret->body = NewVector();
	return ret;
}

il_stmt_elif * il_stmt_elif_new() {
	il_stmt_elif* ret = (il_stmt_elif*)MEM_MALLOC(sizeof(il_stmt_elif));
	ret->condition = NULL;
	ret->body = NewVector();
	return ret;
}

Vector * il_stmt_elif_list_new() {
	return NewVector();
}

il_stmt_else * il_stmt_else_new() {
	il_stmt_else* ret = (il_stmt_else*)MEM_MALLOC(sizeof(il_stmt_else));
	ret->body = NewVector();
	return ret;
}

void il_stmt_elif_list_push(Vector * self, il_stmt_elif * child) {
	PushVector(self, child);
}

void il_stmt_if_generate(il_stmt_if * self, enviroment* env, call_context* cctx) {
	//if(...)
	env->sym_table->scope_depth++;
	il_factor_generate(self->condition, env, cctx);
	label* l1 = opcode_buf_label(env->buf, -1);
	label* tail = opcode_buf_label(env->buf, -1);
	// { ... }
	opcode_buf_add(env->buf, OP_GOTO_if_false);
	opcode_buf_add(env->buf, l1);
	for (int i = 0; i < self->body->length; i++) {
		il_stmt* stmt = (il_stmt*)AtVector(self->body, i);
		il_stmt_generate(stmt, env, cctx);
	}
	//条件が満たされて実行されたら最後までジャンプ
	opcode_buf_add(env->buf, OP_GOTO);
	opcode_buf_add(env->buf, tail);
	l1->cursor = opcode_buf_nop(env->buf);
	// elif(...)
	for (int i = 0; i < self->elif_list->length; i++) {
		il_stmt_elif* elif = (il_stmt_elif*)AtVector(self->elif_list, i);
		il_factor_generate(elif->condition, env, cctx);
		label* l2 = opcode_buf_label(env->buf, -1);
		// { ... }
		opcode_buf_add(env->buf, OP_GOTO_if_false);
		opcode_buf_add(env->buf, l2);
		for (int j = 0; j < elif->body->length; j++) {
			il_stmt* stmt = (il_stmt*)AtVector(elif->body, j);
			il_stmt_generate(stmt, env, cctx);
		}
		//条件が満たされて実行されたら最後までジャンプ
		opcode_buf_add(env->buf, OP_GOTO);
		opcode_buf_add(env->buf, tail);
		l2->cursor = opcode_buf_nop(env->buf);
	}
	// else { ... }
	if (self->else_body == NULL ||
		self->else_body->body->length == 0) {
		tail->cursor = opcode_buf_nop(env->buf);
	} else {
		for (int i = 0; i < self->else_body->body->length; i++) {
			il_stmt* stmt = (il_stmt*)AtVector(self->else_body->body, i);
			il_stmt_generate(stmt, env, cctx);
		}
		tail->cursor = opcode_buf_nop(env->buf);
	}
	env->sym_table->scope_depth--;
}

void il_stmt_if_load(il_stmt_if * self, struct enviroment* env, call_context* cctx) {
	env->sym_table->scope_depth++;
	il_factor_load(self->condition, env, cctx);
	for(int i=0; i<self->body->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->body, i);
		il_stmt_load(e, env, cctx);
		BC_ERROR();
	}
	for(int i=0; i<self->elif_list->length; i++) {
		il_stmt_elif* e = (il_stmt_elif*)AtVector(self->elif_list, i);
		il_factor_load(e->condition, env, cctx);
		for(int j=0; j<e->body->length; j++) {
			il_stmt* st = (il_stmt*)AtVector(e->body, j);
			il_stmt_load(st, env, cctx);
			BC_ERROR();
		}
		BC_ERROR();
	}
	for(int i=0; i<self->else_body->body->length; i++) {
		il_stmt* e = (il_stmt*)AtVector(self->else_body->body, i);
		il_stmt_load(e, env, cctx);
		BC_ERROR();
	}
	//条件が bool を返さない
	BC_ERROR();
	check_condition_type(self->condition, env, cctx);
	for(int i=0; i<self->elif_list->length; i++) {
		il_stmt_elif* elif = AtVector(self->elif_list, i);
		check_condition_type(elif->condition, env, cctx);
		BC_ERROR();
	}
	env->sym_table->scope_depth--;
}

void il_stmt_if_delete(il_stmt_if * self) {
	DeleteVector(self->elif_list, il_stmt_elif_list_delete_impl);
	il_stmt_else_delete(self->else_body);
	DeleteVector(self->body, il_stmt_if_delete_stmt);
	il_factor_delete(self->condition);
	MEM_FREE(self);
}

void il_stmt_elif_delete(il_stmt_elif * self) {
	il_factor_delete(self->condition);
	DeleteVector(self->body, il_stmt_if_delete_stmt);
	MEM_FREE(self);
}

void il_stmt_elif_list_delete(Vector * self) {
	DeleteVector(self, il_stmt_elif_list_delete_impl);
}

void il_stmt_else_delete(il_stmt_else * self) {
	DeleteVector(self->body, il_stmt_if_delete_stmt);
	MEM_FREE(self);
}

//private
static void il_stmt_elif_list_delete_impl(VectorItem item) {
	il_stmt_elif* el = (il_stmt_elif*)item;
	il_stmt_elif_delete(el);
}

static void il_stmt_if_delete_stmt(VectorItem item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx) {
	generic_type* cond_T = il_factor_eval(fact, env, cctx);
	if(cond_T->core_type != TYPE_BOOL) {
		char* condstr = il_factor_tostr(fact, env);
		bc_error_throw(BCERROR_IF_EXPR_TYPE_OF_NOT_BOOL_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}