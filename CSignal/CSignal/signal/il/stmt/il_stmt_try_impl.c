#include "il_stmt_try_impl.h"
#include "../../util/mem.h"
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../../vm/symbol_entry.h"
#include "../../env/namespace.h"
#include "../../env/type_interface.h"
#include <stdio.h>

//proto
static void il_stmt_catch_stmt_delete(void* item);
static void il_stmt_try_catch_delete(void* item);

il_stmt* il_stmt_wrap_try(il_stmt_try* self) {
	il_stmt* ret = (il_stmt*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->type = ilstmt_try;
	ret->u.try_ = self;
	return ret;
}

il_stmt_try* il_stmt_try_new() {
	il_stmt_try* ret = (il_stmt_try*)MEM_MALLOC(sizeof(il_stmt_try));
	ret->statement_list = vector_new();
	ret->catch_list = vector_new();
	return ret;
}

il_stmt_catch* il_stmt_catch_new(const char* name) {
	il_stmt_catch* ret = (il_stmt_catch*)MEM_MALLOC(sizeof(il_stmt_catch));
	ret->name = text_strdup(name);
	ret->fqcn = generic_cache_new();
	ret->statement_list = vector_new();
	return ret;
}

void il_stmt_try_dump(il_stmt_try* self, int depth) {
	text_putindent(depth);
	text_printf("try");
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
	for(int i=0; i<self->catch_list->length; i++) {
		il_stmt_catch* e = (il_stmt_catch*)vector_at(self->catch_list, i);
		il_stmt_catch_dump(e, depth + 1);
	}
}

void il_stmt_catch_dump(il_stmt_catch* self, int depth) {
	text_putindent(depth);
	text_printf("catch(");
	generic_cache_print(self->fqcn);
	text_printf(" %s)", self->name);
	text_putline();
	for(int i=0; i<self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_dump(e, depth + 1);
	}
}

void il_stmt_try_generate(il_stmt_try* self, enviroment* env, il_load_cache* cache) {
	label* try_end = opcode_buf_label(env->buf, -1);
	label* catch_start = opcode_buf_label(env->buf, -1);
	opcode_buf_add(env->buf, op_try_enter);
	//������catch�̊J�n�ɔ�΂��܂����A
	//op_try_enter����͂��̕����̓X�L�b�v����܂��B
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, catch_start);
	//��O���������邩������Ȃ�
	//�X�e�[�g�����g�̈ꗗ
	for (int i = 0; i < self->statement_list->length; i++) {
		il_stmt* e = (il_stmt*)vector_at(self->statement_list, i);
		il_stmt_generate(e, env, cache);
	}
	opcode_buf_add(env->buf, op_try_exit);
	//��O���������Ȃ������Ȃ�catch���X�L�b�v
	opcode_buf_add(env->buf, op_goto);
	opcode_buf_add(env->buf, try_end);
	//��O��ߑ������炱���ɔ�Ԃ悤��
	catch_start->cursor = opcode_buf_nop(env->buf);
	//�S�Ă�catch�߂ɑ΂���
	label* nextCause = NULL;
	for (int i = 0; i < self->catch_list->length; i++) {
		//��O���w��̖��O�ŃA�N�Z�X�o����悤��
		il_stmt_catch* ilcatch = (il_stmt_catch*)vector_at(self->catch_list, i);
		type* exType = generic_cache_type(ilcatch->fqcn, (namespace_*)vector_top(cache->namespace_vec));
		int exIndex = symbol_table_entry(env->sym_table, exType, ilcatch->name)->index;
		//���O�̃P�[�X�̃W�����v���������
		if (nextCause != NULL) {
			int head = opcode_buf_nop(env->buf);
			nextCause->cursor = head;
		}
		nextCause = opcode_buf_label(env->buf, -1);
		//���݂̗�O�� catch�� �̌^�Ɍ݊���������Ȃ瑱�s
		opcode_buf_add(env->buf, op_hexception);
		opcode_buf_add(env->buf, op_instanceof);
		opcode_buf_add(env->buf, exType->absolute_index);
		//�݊������Ȃ��̂Ŏ��̃P�[�X��
		opcode_buf_add(env->buf, op_goto_if_false);
		opcode_buf_add(env->buf, nextCause);
		//�w��̖��O�ŗ�O��錾
		opcode_buf_add(env->buf, op_hexception);
		opcode_buf_add(env->buf, op_store);
		opcode_buf_add(env->buf, exIndex);
		//catch�̓����̃X�e�[�g�����g�𐶐�
		for (int j = 0; j < ilcatch->statement_list->length; j++) {
			il_stmt* e = (il_stmt*)vector_at(ilcatch->statement_list, j);
			il_stmt_generate(e, env, cache);
		}
		//catch���ꂽ�̂ŁA
		//��O�t���O���N���A����
		opcode_buf_add(env->buf, op_try_clear);
		//�Ō��catch�̌���
		opcode_buf_add(env->buf, op_goto);
		opcode_buf_add(env->buf, try_end);
		//nextCause = opcode_buf_label(env->buf, -1);
	}
	//try-catch�̍Ō�
	nextCause->cursor = opcode_buf_nop(env->buf);
	//�ǂ�catch�ɂ�����������Ȃ�����
	opcode_buf_add(env->buf, op_try_exit);
	//catch�����������炱����
	try_end->cursor = opcode_buf_nop(env->buf);
}

void il_stmt_catch_generate(il_stmt_catch* self, enviroment* env, il_load_cache* cache) {

}

void il_stmt_try_load(il_stmt_try* self, enviroment* env, il_load_cache* cache, il_ehandler* eh) {

}

void il_stmt_catch_load(il_stmt_catch* self, enviroment* env, il_load_cache* cache, il_ehandler* eh) {

}

void il_stmt_catch_delete(il_stmt_catch* self) {
	generic_cache_delete(self->fqcn);
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	MEM_FREE(self->name);
	MEM_FREE(self);
}

void il_stmt_try_delete(il_stmt_try* self) {
	vector_delete(self->statement_list, il_stmt_catch_stmt_delete);
	vector_delete(self->catch_list, il_stmt_try_catch_delete);
	MEM_FREE(self);
}
//private
static void il_stmt_catch_stmt_delete(void* item) {
	il_stmt* e = (il_stmt*)item;
	il_stmt_delete(e);
}

static void il_stmt_try_catch_delete(void* item) {
	il_stmt_catch* e = (il_stmt_catch*)item;
	il_stmt_catch_delete(e);
}