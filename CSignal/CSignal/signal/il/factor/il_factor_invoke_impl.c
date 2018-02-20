#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"
#include "../../env/type_interface.h"
#include "../../env/method.h"
#include "../../util/mem.h"
#include "../../util/logger.h"
#include "../../env/type_impl.h"

//proto
static void il_factor_invoke_argument_delete(vector_item item);
static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env, il_load_cache* cache);

il_factor * il_factor_wrap_invoke(il_factor_invoke * self) {
	il_factor* ret = (il_factor*)MEM_MALLOC(sizeof(il_factor));
	ret->type = ilfactor_invoke;
	ret->u.invoke_ = self;
	return ret;
}

il_factor_invoke * il_factor_invoke_new(const char * name) {
	il_factor_invoke* ret = (il_factor_invoke*)MEM_MALLOC(sizeof(il_factor_invoke));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	ret->receiver = NULL;
	ret->m = NULL;
	ret->method_index = -1;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke * self, int depth) {
	text_putindent(depth);
	text_printf("invoke %s", self->name);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_invoke_generate(il_factor_invoke * self, enviroment* env, il_load_cache* cache) {
	il_factor_invoke_find(self, env, cache);
	//NOTE:Hoge.Foo() hoge.Foo() はil_named_invokeに拾われるので、
	//こちらでは関数の戻り値や式に対する呼び出しだけ考慮する。
	//全ての引数をプッシュ
	for(int i=0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env, cache);
	}
	//このメソッドを呼び出しているオブジェクトをプッシュ
	il_factor_generate(self->receiver, env, cache);
	//メソッドのインデックスをプッシュ
	if (self->m->access == access_private) {
		opcode_buf_add(env->buf, (vector_item)op_invokespecial);
	} else {
		type* receiverType = il_factor_eval(self->receiver, env, cache);
		if (receiverType->tag == type_class) {
			opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
		} else {
			opcode_buf_add(env->buf, (vector_item)op_invokeinterface);
			opcode_buf_add(env->buf, receiverType->absolute_index);
		}
	}
	opcode_buf_add(env->buf, (vector_item)self->method_index);
}

void il_factor_invoke_load(il_factor_invoke * self, enviroment * env, il_load_cache* cache, il_ehandler * eh) {
}

type * il_factor_invoke_eval(il_factor_invoke * self, enviroment * env, il_load_cache* cache) {
	il_factor_invoke_find(self, env, cache);
	return self->m->return_type;
}

void il_factor_invoke_delete(il_factor_invoke * self) {
	vector_delete(self->argument_list, il_factor_invoke_argument_delete);
	MEM_FREE(self->name);
	il_factor_delete(self->receiver);
	MEM_FREE(self);
}

//private
static void il_factor_invoke_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env, il_load_cache* cache) {
	if(self->m != NULL) {
		return;
	}
	int temp = 0;
	self->m = type_find_method(
		il_factor_eval(self->receiver, env, cache),
		self->name,
		self->argument_list,
		env,
		cache,
		&temp
	);
	self->method_index = temp;
	assert(self->m != NULL);
}