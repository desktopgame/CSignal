#include "bc_exception.h"
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
static void bc_exception_nativeInit(Method* parent, Frame* fr, Enviroment* env);

void InitBCException() {
	Namespace* lang = GetLangNamespace();
	Type* exceptionType = NewPreloadClass(InternString("Exception"));
	class_* exceptionClass = TYPE2CLASS(exceptionType);
	AddTypeNamespace(lang, exceptionType);
	DefineNativeMethodClass(exceptionClass, "nativeInit", bc_exception_nativeInit);
}

Type* GetBCExceptionType() {
	Namespace* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Exception"));
}
//private
static void bc_exception_nativeInit(Method* parent, Frame* fr, Enviroment* env) {
	Namespace* lang = GetLangNamespace();
	class_* stackTraceElementClass = FindClassFromNamespace(lang, InternString("StackTraceElement"));
	class_* exceptionClass = FindClassFromNamespace(lang, InternString("Exception"));
	Object* self= (Object*)AtVector(fr->VariableTable, 0);
	//FXIME:???
	Heap* h = GetHeap();
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
		PushVector(args, Object_string_new(temp->ContextRef->ContextRef->FileName));
		PushVector(args, Object_int_new(lineno));
		Object* trace = NewInstanceClass(
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
	Object* arr = NewBCArray(stackTraceElementClass->parent->GenericSelf, stackTraceElementVec->Length, fr);
	for (int i = 0; i < stackTraceElementVec->Length; i++) {
		SetBCArray(arr, i, AtVector(stackTraceElementVec, i));
	}
	//Exception#stackTraceをここで初期化する
	int tempi = 0;
	Field* stackTraceF = FindFieldClass(exceptionClass, InternString("stackTrace"), &tempi);
	AssignVector(self->u.field_vec, tempi, arr);
	DeleteVector(stackTraceElementVec, VectorDeleterOfNull);
	h->CollectBlocking--;
}