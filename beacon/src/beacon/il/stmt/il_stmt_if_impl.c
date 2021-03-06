#include "il_stmt_if_impl.h"
#include "../../util/text.h"
#include "../../util/mem.h"
#include "../../env/namespace.h"
#include "../../vm/opcode_buf.h"
#include "../../vm/enviroment.h"
#include <stdlib.h>
#include <stdio.h>

//proto
static void il_stmt_elif_list_delete_impl(vector_item item);
static void il_stmt_if_delete_stmt(vector_item item);
static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx);

il_stmt * il_stmt_wrap_if(il_stmt_if * self) {
	il_stmt* ret = il_stmt_new(ilstmt_if_T);
	ret->u.if_ = self;
	return ret;
}

il_stmt_if * il_stmt_if_new() {
	il_stmt_if* ret = (il_stmt_if*)MEM_MALLOC(sizeof(il_stmt_if));
	ret->condition = NULL;
	ret->elif_list = vector_new();
	ret->else_body = il_stmt_else_new();
	ret->body = vector_new();
	return ret;
}

il_stmt_elif * il_stmt_elif_new() {
	il_stmt_elif* ret = (il_stmt_elif*)MEM_MALLOC(sizeof(il_stmt_elif));
	ret->condition = NULL;
	ret->body = vector_new();
	return ret;
}

vector * il_stmt_elif_list_new() {
	return vector_new();
}

il_stmt_else * il_stmt_else_new() {
	il_stmt_else* ret = (il_stmt_else*)MEM_MALLOC(sizeof(il_stmt_else));
	ret->body = vector_new();
	return ret;
}

void il_stmt_elif_list_push(vector * self, il_stmt_elif * child) {
	vector_push(self, child);
}

void il_stmt_if_dump(il_stmt_if * self, int depth) {
	io_printi(depth);
	printf("if");
	io_println();
	il_factor_dump(self->condition, depth + 1);
	//ステートメントの一覧をダンプ
	for (int i = 0; i < self->body->length; i++) {
		vector_item e = vector_at(self->body, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
	//エルスイフの一覧をダンプ
	for (int i = 0; i < self->elif_list->length; i++) {
		vector_item e = vector_at(self->elif_list, i);
		il_stmt_elif* elif = (il_stmt_elif*)e;
		io_printi(depth);
		printf("elif");
		io_println();
		il_factor_dump(elif->condition, depth + 1);
		for (int i = 0; i < elif->body->length; i++) {
			vector_item e = vector_at(elif->body, i);
			il_stmt* s = (il_stmt*)e;
			il_stmt_dump(s, depth + 1);
		}
	}
	
	io_printi(depth + 1);
	printf("else");
	io_println();
	//ステートメントの一覧をダンプ
	for (int i = 0; i < self->else_body->body->length; i++) {
		vector_item e = vector_at(self->else_body->body, i);
		il_stmt* s = (il_stmt*)e;
		il_stmt_dump(s, depth + 1);
	}
	io_println();
}

void il_stmt_if_generate(il_stmt_if * self, enviroment* env, call_context* cctx) {
	//if(...)
	il_factor_generate(self->condition, env, cctx);
	label* l1 = opcode_buf_label(env->buf, -1);
	label* tail = opcode_buf_label(env->buf, -1);
	// { ... }
	opcode_buf_add(env->buf, op_goto_if_false);
	opcode_buf_add(env->buf, l1);
	for (int i = 0; i < self->body->length; i++) {
		il_stmt* stmt = (il_stmt*)vector_at(self->body, i);
		il_stmt_generate(stmt, env, cctx);
	}
	//条件が満たされて実行されたら最後までジャンプ
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, tail);
	l1->cursor = opcode_buf_nop(env->buf);
	// elif(...)
	for (int i = 0; i < self->elif_list->length; i++) {
		il_stmt_elif* elif = (il_stmt_elif*)vector_at(self->elif_list, i);
		il_factor_generate(elif->condition, env, cctx);
		label* l2 = opcode_buf_label(env->buf, -1);
		// { ... }
		opcode_buf_add(env->buf, op_goto_if_false);
		opcode_buf_add(env->buf, l2);
		for (int j = 0; j < elif->body->length; j++) {
			il_stmt* stmt = (il_stmt*)vector_at(elif->body, j);
			il_stmt_generate(stmt, env, cctx);
		}
		//条件が満たされて実行されたら最後までジャンプ
		opcode_buf_add(env->buf, op_goto);
		opcode_buf_add(env->buf, tail);
		l2->cursor = opcode_buf_nop(env->buf);
	}
	// else { ... }
	if (self->else_body == NULL ||
		self->else_body->body->length == 0) {
		tail->cursor = opcode_buf_nop(env->buf);
	} else {
		for (int i = 0; i < self->else_body->body->length; i++) {
			il_stmt* stmt = (il_stmt*)vector_at(self->else_body->body, i);
			il_stmt_generate(stmt, env, cctx);
		}
		tail->cursor = opcode_buf_nop(env->buf);
	}
}

void il_stmt_if_load(il_stmt_if * self, struct enviroment* env, call_context* cctx) {
	il_factor_load(self->condition, env, cctx);
	for(int i=0; i<self->body->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->body, i);
		il_stmt_load(e, env, cctx);
		BC_ERROR();
	}
	for(int i=0; i<self->elif_list->length; i++) {
		il_stmt_elif* e = (il_stmt_elif*)vector_at(self->elif_list, i);
		il_factor_load(e->condition, env, cctx);
		for(int j=0; j<e->body->length; j++) {
			il_stmt* st = (il_stmt*)vector_at(e->body, j);
			il_stmt_load(st, env, cctx);
			BC_ERROR();
		}
		BC_ERROR();
	}
	for(int i=0; i<self->else_body->body->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->else_body->body, i);
		il_stmt_load(e, env, cctx);
		BC_ERROR();
	}
	//条件が bool を返さない
	BC_ERROR();
	check_condition_type(self->condition, env, cctx);
	for(int i=0; i<self->elif_list->length; i++) {
		il_stmt_elif* elif = vector_at(self->elif_list, i);
		check_condition_type(elif->condition, env, cctx);
		BC_ERROR();
	}
}

void il_stmt_if_delete(il_stmt_if * self) {
	vector_delete(self->elif_list, il_stmt_elif_list_delete_impl);
	il_stmt_else_delete(self->else_body);
	vector_delete(self->body, il_stmt_if_delete_stmt);
	il_factor_delete(self->condition);
	MEM_FREE(self);
}

void il_stmt_elif_delete(il_stmt_elif * self) {
	il_factor_delete(self->condition);
	vector_delete(self->body, il_stmt_if_delete_stmt);
	MEM_FREE(self);
}

void il_stmt_elif_list_delete(vector * self) {
	vector_delete(self, il_stmt_elif_list_delete_impl);
}

void il_stmt_else_delete(il_stmt_else * self) {
	vector_delete(self->body, il_stmt_if_delete_stmt);
	MEM_FREE(self);
}

//private
static void il_stmt_elif_list_delete_impl(vector_item item) {
	il_stmt_elif* el = (il_stmt_elif*)item;
	il_stmt_elif_delete(el);
}

static void il_stmt_if_delete_stmt(vector_item item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void check_condition_type(il_factor* fact, enviroment* env, call_context* cctx) {
	generic_type* cond_T = il_factor_eval(fact, env, cctx);
	if(cond_T->core_type != TYPE_BOOL) {
		char* condstr = il_factor_tostr(fact, env);
		bc_error_throw(bcerror_if_expr_type_of_not_bool_T,
			condstr
		);
		MEM_FREE(condstr);
	}
}