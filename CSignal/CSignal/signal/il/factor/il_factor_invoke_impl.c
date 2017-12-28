#include "il_factor_invoke_impl.h"
#include <stdio.h>
#include <stdlib.h>
#include "../../util/text.h"
#include "../../vm/enviroment.h"
#include "../il_argument.h"
#include "../../env/class.h"
#include "../../env/method.h"

//proto
static void il_factor_invoke_argument_delete(vector_item item);
static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env);

il_factor * il_factor_wrap_invoke(il_factor_invoke * self) {
	il_factor* ret = (il_factor*)malloc(sizeof(il_factor));
	ret->type = ilfactor_invoke;
	ret->u.invoke_ = self;
	return ret;
}

il_factor_invoke * il_factor_invoke_new(const char * name) {
	il_factor_invoke* ret = (il_factor_invoke*)malloc(sizeof(il_factor_invoke));
	ret->name = text_strdup(name);
	ret->argument_list = vector_new();
	ret->receiver = NULL;
	ret->m = NULL;
	ret->methodIndex = -1;
	return ret;
}

void il_factor_invoke_dump(il_factor_invoke * self, int depth) {
	text_putindent(depth);
	printf("invoke %s", self->name);
	text_putline();
	il_factor_dump(self->receiver, depth + 1);
	for (int i = 0; i < self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ila = (il_argument*)e;
		il_argument_dump(ila, depth + 1);
	}
}

void il_factor_invoke_generate(il_factor_invoke * self, enviroment* env) {
	il_factor_invoke_find(self, env);
	//このメソッドを呼び出しているオブジェクトをプッシュ
	il_factor_generate(self->receiver, env);
	//全ての引数をプッシュ
	for(int i=0; i<self->argument_list->length; i++) {
		vector_item e = vector_at(self->argument_list, i);
		il_argument* ilarg = (il_argument*)e;
		il_factor_generate(ilarg->factor, env);
	}
	//メソッドのインデックスをプッシュ
	opcode_buf_add(env->buf, (vector_item)op_method);
	opcode_buf_add(env->buf, (vector_item)self->methodIndex);
	opcode_buf_add(env->buf, (vector_item)op_invokevirtual);
}

class_ * il_factor_invoke_eval(il_factor_invoke * self, enviroment * env) {
	il_factor_invoke_find(self, env);
	return self->m->return_type;
}

void il_factor_invoke_delete(il_factor_invoke * self) {
	vector_delete(self->argument_list, il_factor_invoke_argument_delete);
	free(self->name);
	il_factor_delete(self->receiver);
	free(self);
}

//private
static void il_factor_invoke_argument_delete(vector_item item) {
	il_argument* e = (il_argument*)item;
	il_argument_delete(e);
}

static void il_factor_invoke_find(il_factor_invoke* self, enviroment* env) {
	if(self->m != NULL) {
		return;
	}
	int temp = 0;
	self->m = class_find_methodvf(
		il_factor_eval(self->receiver, env),
		self->name,
		self->argument_list,
		env,
		&temp
	);
	self->methodIndex = temp;
}