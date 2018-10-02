#include "enviroment.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include "../lib/beacon/lang/bc_array.h"
#include "line_range.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void enviroment_constant_pool_vec_delete(VectorItem item);
static void enviroment_DeleteLineRange(VectorItem item);
static void enviroment_add_constant(enviroment* self, object* o);
static void enviroment_DeleteObject_self(VectorItem item);
static void enviroment_DeleteObject(object* obj);

enviroment * NewEnviroment() {
	enviroment* ret = (enviroment*)MEM_MALLOC(sizeof(enviroment));
	ret->buf = NewOpcodeBuf();
	ret->constant_pool_vec = NewVector();
	ret->sym_table = NewSymbolTable();
	ret->context_ref = NULL;
	ret->line_range_vec = NewVector();
	return ret;
}

void AddRangeEnviroment(enviroment* self, int lineno) {
	assert(lineno >= 0);
	//空なので追加
	if (IsEmptyVector(self->line_range_vec)) {
		line_range* lr = NewLineRange();
		lr->start_offset = 0;
		lr->end_offset = 0;
		lr->lineno = lineno;
		PushVector(self->line_range_vec, lr);
		return;
	}
	//空ではないなら、
	//最後についかしたレンジを伸ばすか新たに追加する
	line_range* lrt = (line_range*)TopVector(self->line_range_vec);
	if (lrt->lineno == lineno) {
		lrt->end_offset = self->buf->source_vec->length;
	} else {
		line_range* lr = NewLineRange();
		lr->start_offset = self->buf->source_vec->length;
		lr->end_offset = self->buf->source_vec->length;
		lr->lineno = lineno;
		PushVector(self->line_range_vec, lr);
	}
}

void DumpEnviromentOp(enviroment * self, int depth) {
	opcode_buf* buf = self->buf;
	line_range* lr = NULL;
	int lrPos = -1;
	for (int i = 0; i < buf->source_vec->length; i++) {
		Printi(depth);
		i = PrintOpcode(buf->source_vec, i);
		if (!IsEmptyVector(self->line_range_vec)) {
			if (lr == NULL) {
				lr = AtVector(self->line_range_vec, 0);
				lrPos = 0;
			} else {
				if (i > lr->end_offset) {
					lrPos++;
					if (lrPos < self->line_range_vec->length) {
						lr = AtVector(self->line_range_vec, lrPos);
					}
				}
			}
		}
		if (lr != NULL) {
			printf("<%d>", lr->lineno);
		}
		Println();
	}
	Println();
}

int AddCIntEnviroment(enviroment * self, int i) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_int_new(i));
	return len;
}

int AddCDoubleEnviroment(enviroment * self, double d) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_double_new(d));
	return len;
}

int AddCCharEnviroment(enviroment * self, char c) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_char_new(c));
	return len;
}

int AddCStringEnviroment(enviroment * self, string_view sv) {
	int len = self->constant_pool_vec->length;
	enviroment_add_constant(self, object_string_new(Ref2Str(sv)));
	return len;
}

VectorItem GetEnviromentSourceAt(enviroment * self, int index) {
	return AtVector(self->buf->source_vec, index);
}

object* GetEnviromentConstantAt(enviroment * self, int index) {
	return (object*)AtVector(self->constant_pool_vec, index);
}

object* GetEnviromentCIntAt(enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_INT_T);
	return e;
}

object* GetEnviromentCDoubleAt(enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_DOUBLE_T);
	return e;
}

object* GetEnviromentCCharAt(enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_CHAR_T);
	return e;
}

object* GetEnviromentCStringAt(enviroment * self, int index) {
	object* e = GetEnviromentConstantAt(self, index);
	assert(e->tag == OBJECT_STRING_T);
	return e;
}

void DeleteEnviroment(enviroment * self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->constant_pool_vec, enviroment_constant_pool_vec_delete);
	DeleteVector(self->line_range_vec, enviroment_DeleteLineRange);
	DeleteOpcodeBuf(self->buf);
	DeleteSymbolTable(self->sym_table);
	MEM_FREE(self);
}

//private
static void enviroment_constant_pool_vec_delete(VectorItem item) {
	enviroment_DeleteObject((object*)item);
}

static void enviroment_DeleteLineRange(VectorItem item) {
	line_range* e = (line_range*)item;
	DeleteLineRange(e);
}

static void enviroment_add_constant(enviroment* self, object* o) {
	PushVector(self->constant_pool_vec, o);
	assert(o->paint == PAINT_ONEXIT_T);
}

static void enviroment_DeleteObject_self(VectorItem item) {
}

static void enviroment_DeleteObject(object* obj) {
	DestroyObject(obj);
}
