#include "bc_file.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_interface.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static void bc_file_nativeOpen(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativePut(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeGet(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeAvailable(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeGetStdIn(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeGetStdOut(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeGetStdErr(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_file_nativeClose(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);

bc_Object* NewFile(FILE* fp) {
	File* file = bc_ConstructObject(sizeof(File), GetFileType()->GenericSelf);
	assert(file->Super.Paint != PAINT_ONEXIT_T);
	file->Pointer = fp;
	return (bc_Object*)file;
}

FILE* GetFilePointer(bc_Object* self) {
	return ((File*)self)->Pointer;
}

void InitFile() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	bc_Type* fileType = bc_NewPreloadClass(bc_InternString("File"));
	bc_Class* fileClass = BC_TYPE2CLASS(fileType);
	fileType->AllocSize = sizeof(File);
	bc_AddTypeNamespace(unsafe, fileType);
	bc_DefineNativeMethodClass(fileClass, "nativeOpen", bc_file_nativeOpen);
	bc_DefineNativeMethodClass(fileClass, "nativePut", bc_file_nativePut);
	bc_DefineNativeMethodClass(fileClass, "nativeGet", bc_file_nativeGet);
	bc_DefineNativeMethodClass(fileClass, "nativeAvailable", bc_file_nativeAvailable);
	bc_DefineNativeMethodClass(fileClass, "nativeGetStdIn", bc_file_nativeGetStdIn);
	bc_DefineNativeMethodClass(fileClass, "nativeGetStdOut", bc_file_nativeGetStdOut);
	bc_DefineNativeMethodClass(fileClass, "nativeGetStdErr", bc_file_nativeGetStdErr);
	bc_DefineNativeMethodClass(fileClass, "nativeClose", bc_file_nativeClose);
}

bc_Type* GetFileType() {
	bc_Namespace* unsafe = bc_GetUnsafeNamespace();
	return bc_FindTypeFromNamespace(unsafe, bc_InternString("File"));
}
//private
static void bc_file_nativeOpen(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* fileObj = bc_AtVector(fr->VariableTable, 1);
	bc_Object* modeObj = bc_AtVector(fr->VariableTable, 2);
	bc_Buffer* fileStr = GetRawString(fileObj);
	bc_Buffer* modeStr = GetRawString(modeObj);
	//bc_Printfln("%s : %s", fileStr->text, modeStr->text);

	FILE* fp = fopen(fileStr->Text, modeStr->Text);
	if(fp == NULL) {
		//ひらけなかった
		bc_PushVector(fr->ValueStack, bc_GetNullObject());
		return;
	}
	bc_Object* file = NewFile(fp);
	bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativePut(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* ch = bc_AtVector(fr->VariableTable, 1);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	fputc(bc_ObjectToChar(ch), fp);
}

static void bc_file_nativeGet(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	char ret = fgetc(fp);
	bc_PushVector(fr->ValueStack, NewChar(ret));
}

static void bc_file_nativeAvailable(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	bc_PushVector(fr->ValueStack, bc_GetBoolObject(!feof(fp)));
}

static void bc_file_nativeGetStdIn(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* file = NewFile(stdin);
	bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdOut(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* file = NewFile(stdout);
	bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeGetStdErr(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* file = NewFile(stderr);
	bc_PushVector(fr->ValueStack, file);
}

static void bc_file_nativeClose(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	FILE* fp = GetFilePointer(self);
	assert(fp != NULL);
	fclose(fp);
}