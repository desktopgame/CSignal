#include "enviroment.h"
#include <stdlib.h>

//proto
static void enviroment_constant_pool_delete(vector_item item);

enviroment * enviroment_new() {
	enviroment* ret = (enviroment*)malloc(sizeof(enviroment));
	ret->buf = opcode_buf_new();
	ret->constant_pool = vector_new();
	ret->class_ = NULL;
	return ret;
}

int enviroment_add_constant(enviroment * self, vector_item item) {
	int index = self->constant_pool->length;
	vector_push(self->constant_pool, item);
	return index;
}

vector_item enviroment_source_at(enviroment * self, int index) {
	return vector_at(self->buf->source, index);
}

vector_item enviroment_constant_at(enviroment * self, int index) {
	return vector_at(self->constant_pool, index);
}

void enviroment_delete(enviroment * self) {
	opcode_buf_delete(self->buf);
	vector_delete(self->constant_pool, vector_deleter_null);
	free(self);
}

//private
static void enviroment_constant_pool_delete(vector_item item) {

}
