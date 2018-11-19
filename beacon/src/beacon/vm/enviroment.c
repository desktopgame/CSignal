#include "enviroment.h"
#include "../env/class_loader.h"
#include "../env/type_interface.h"
#include "../env/TYPE_IMPL.h"
#include "../env/object.h"
#include "../env/fqcn_cache.h"
#include "../lib/bc_library_interface.h"
#include "line_range.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "../util/mem.h"
#include "../util/string_buffer.h"
#include "../util/text.h"
#include "../env/generic_type.h"

//proto
static void delete_constant(VectorItem item);
static void delete_line_range(VectorItem item);
static void add_constant(Enviroment* self, bc_Object* o);
static void delete_object_self(VectorItem item);
static void delete_object(bc_Object* obj);

Enviroment * NewEnviroment() {
	Enviroment* ret = (Enviroment*)MEM_MALLOC(sizeof(Enviroment));
	ret->Bytecode = NewOpcodeBuf();
	ret->ConstantPool = NewVector();
	ret->Symboles = NewSymbolTable();
	ret->ContextRef = NULL;
	ret->LineRangeTable = NewVector();
	return ret;
}

void AddRangeEnviroment(Enviroment* self, int lineno) {
	assert(lineno >= 0);
	//空なので追加
	if (IsEmptyVector(self->LineRangeTable)) {
		LineRange* lr = NewLineRange();
		lr->StartOffset = 0;
		lr->EndOffset = 0;
		lr->Lineno = lineno;
		PushVector(self->LineRangeTable, lr);
		return;
	}
	//空ではないなら、
	//最後についかしたレンジを伸ばすか新たに追加する
	LineRange* lrt = (LineRange*)TopVector(self->LineRangeTable);
	if (lrt->Lineno == lineno) {
		lrt->EndOffset = self->Bytecode->Instructions->Length;
	} else {
		LineRange* lr = NewLineRange();
		lr->StartOffset = self->Bytecode->Instructions->Length;
		lr->EndOffset = self->Bytecode->Instructions->Length;
		lr->Lineno = lineno;
		PushVector(self->LineRangeTable, lr);
	}
}

void DumpEnviromentOp(Enviroment * self, int depth) {
	OpcodeBuf* buf = self->Bytecode;
	LineRange* lr = NULL;
	int lrPos = -1;
	for (int i = 0; i < buf->Instructions->Length; i++) {
		bc_Printi(depth);
		i = PrintOpcode(buf->Instructions, i);
		if (!IsEmptyVector(self->LineRangeTable)) {
			if (lr == NULL) {
				lr = AtVector(self->LineRangeTable, 0);
				lrPos = 0;
			} else {
				if (i > lr->EndOffset) {
					lrPos++;
					if (lrPos < self->LineRangeTable->Length) {
						lr = AtVector(self->LineRangeTable, lrPos);
					}
				}
			}
		}
		if (lr != NULL) {
			printf("<%d>", lr->Lineno);
		}
		bc_Println();
	}
	bc_Println();
}

int AddCIntEnviroment(Enviroment * self, int i) {
	int len = self->ConstantPool->Length;
	add_constant(self, (bc_Object*)NewInteger(i));
	return len;
}

int AddCDoubleEnviroment(Enviroment * self, double d) {
	int len = self->ConstantPool->Length;
	add_constant(self, (bc_Object*)NewDouble(d));
	return len;
}

int AddCCharEnviroment(Enviroment * self, char c) {
	int len = self->ConstantPool->Length;
	add_constant(self, (bc_Object*)NewChar(c));
	return len;
}

int AddCStringEnviroment(Enviroment * self, StringView sv) {
	int len = self->ConstantPool->Length;
	add_constant(self, (bc_Object*)NewString(Ref2Str(sv)));
	return len;
}

VectorItem GetEnviromentSourceAt(Enviroment * self, int index) {
	return AtVector(self->Bytecode->Instructions, index);
}

bc_Object* GetEnviromentConstantAt(Enviroment * self, int index) {
	return (bc_Object*)AtVector(self->ConstantPool, index);
}

bc_Object* GetEnviromentCIntAt(Enviroment * self, int index) {
	bc_Object* e = GetEnviromentConstantAt(self, index);
	assert(bc_IsIntValue(e));
	return e;
}

bc_Object* GetEnviromentCDoubleAt(Enviroment * self, int index) {
	bc_Object* e = GetEnviromentConstantAt(self, index);
	assert(bc_IsDoubleValue(e));
	return e;
}

bc_Object* GetEnviromentCCharAt(Enviroment * self, int index) {
	bc_Object* e = GetEnviromentConstantAt(self, index);
	assert(bc_IsCharValue(e));
	return e;
}

bc_Object* GetEnviromentCStringAt(Enviroment * self, int index) {
	bc_Object* e = GetEnviromentConstantAt(self, index);
	assert(bc_IsStringValue(e));
	return e;
}

void DeleteEnviroment(Enviroment * self) {
	if(self == NULL) {
		return;
	}
	DeleteVector(self->ConstantPool, delete_constant);
	DeleteVector(self->LineRangeTable, delete_line_range);
	DeleteOpcodeBuf(self->Bytecode);
	DeleteSymbolTable(self->Symboles);
	MEM_FREE(self);
}

//private
static void delete_constant(VectorItem item) {
	delete_object((bc_Object*)item);
}

static void delete_line_range(VectorItem item) {
	LineRange* e = (LineRange*)item;
	DeleteLineRange(e);
}

static void add_constant(Enviroment* self, bc_Object* o) {
	PushVector(self->ConstantPool, o);
	assert(o->Paint == PAINT_ONEXIT_T);
}

static void delete_object_self(VectorItem item) {
}

static void delete_object(bc_Object* obj) {
	bc_DestroyObject(obj);
}
