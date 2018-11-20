#include "il_top_level.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/mem.h"
#include "il_stmt_interface.h"
#include "il_import.h"
#include "il_namespace.h"
#include "il_function.h"

//proto
static void ILToplevel_import_delete(bc_VectorItem item);
static void ILToplevel_DeleteNamespace(bc_VectorItem item);
static void ILToplevel_function_delete(bc_VectorItem item);
static void ILToplevel_stmt_delete(bc_VectorItem item);

ILToplevel* NewILToplevel() {
	ILToplevel* ret = (ILToplevel*)MEM_MALLOC(sizeof(ILToplevel));
	ret->ImportList = bc_NewVector();
	ret->NamespaceList = bc_NewVector();
	ret->StatementList = bc_NewVector();
	ret->FunctionList = bc_NewVector();
	return ret;
}

void DeleteILToplevel(ILToplevel* self) {
	if(self == NULL) {
		return;
	}
	bc_DeleteVector(self->ImportList, ILToplevel_import_delete);
	bc_DeleteVector(self->NamespaceList, ILToplevel_DeleteNamespace);
	bc_DeleteVector(self->StatementList, ILToplevel_stmt_delete);
	bc_DeleteVector(self->FunctionList, ILToplevel_function_delete);
	MEM_FREE(self);
}

//private
static void ILToplevel_import_delete(bc_VectorItem item) {
	ILImport* e = (ILImport*)item;
	DeleteILImport(e);
}

static void ILToplevel_DeleteNamespace(bc_VectorItem item) {
	ILNamespace* e = (ILNamespace*)item;
	DeleteILNamespace(e);
}

static void ILToplevel_function_delete(bc_VectorItem item) {
	ILFunction* e = (ILFunction*)item;
	DeleteILFunction(e);
}

static void ILToplevel_stmt_delete(bc_VectorItem item) {
	ILStatement* e = (ILStatement*)item;
	DeleteILStmt(e);
}