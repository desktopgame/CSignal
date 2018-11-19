#include "bc_exception.h"
#include "../../bc_library_interface.h"
#include "../../bc_library_impl.h"
#include "../../../env/constructor.h"
#include "../../../env/class_loader.h"
#include "../../../vm/line_range.h"
#include "../../../vm/frame.h"
#include "../../../env/field.h"
#include "../../../env/heap.h"
#include "bc_array.h"
#include <string.h>
#include <assert.h>
//proto
static void bc_exception_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env);

void InitException() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* exceptionType = NewPreloadClass(InternString("Exception"));
	Class* exceptionClass = BC_TYPE2CLASS(exceptionType);
	bc_AddTypeNamespace(lang, exceptionType);
	DefineNativeMethodClass(exceptionClass, "nativeInit", bc_exception_nativeInit);
}

bc_Type* GetExceptionType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, InternString("Exception"));
}
//private
static void bc_exception_nativeInit(bc_Method* parent, Frame* fr, Enviroment* env) {
	bc_Namespace* lang = bc_GetLangNamespace();
	Class* stackTraceElementClass = bc_FindClassFromNamespace(lang, InternString("StackTraceElement"));
	Class* exceptionClass = bc_FindClassFromNamespace(lang, InternString("Exception"));
	bc_Object* self= (bc_Object*)AtVector(fr->VariableTable, 0);
	//FXIME:???
	bc_Heap* h = bc_GetHeap();
	h->CollectBlocking++;
	//スタックトレースを作成する
	Frame* temp = fr;
	Vector* stackTraceElementVec = NewVector();
	char* lfilename = NULL;
	int llineno = -1;
	do {
		//実行中のインストラクションの行番号を取得
		LineRange* lr = FindLineRange(temp->ContextRef->LineRangeTable, temp->PC);
		int lineno = lr == NULL ? -1 : lr->Lineno;
		//assert(lineno != -1);
		//直前の表示と同じ
		if(lfilename != NULL &&
		   !strcmp(temp->ContextRef->ContextRef->FileName, lfilename) &&
		   llineno == lineno) {
			temp = temp->Parent;
			continue;
		}
		//スタックトレースを作成
		//assert(lineno >= 0);
		Vector* args = NewVector();
		PushVector(args, NewString(temp->ContextRef->ContextRef->FileName));
		PushVector(args, NewInteger(lineno));
		bc_Object* trace = NewInstanceClass(
			stackTraceElementClass,
			//ilctx,
			fr,
			args,
			NULL
		);
		DeleteVector(args, VectorDeleterOfNull);
		PushVector(stackTraceElementVec, trace);
		temp = temp->Parent;
		//今回の表示情報を記録
		if(temp != NULL) {
			lfilename = temp->ContextRef->ContextRef->FileName;
			llineno = lineno;
		}
	} while (temp != NULL);
	//配列へ
	bc_Object* arr = DynamicNewArray(stackTraceElementClass->Parent->GenericSelf, stackTraceElementVec->Length, fr);
	for (int i = 0; i < stackTraceElementVec->Length; i++) {
		SetElementAt(arr, i, AtVector(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	bc_Field* stackTraceF = FindFieldClass(exceptionClass, InternString("stackTrace"), &tempi);
	AssignVector(self->Fields, tempi, arr);
	DeleteVector(stackTraceElementVec, VectorDeleterOfNull);
	h->CollectBlocking--;
}