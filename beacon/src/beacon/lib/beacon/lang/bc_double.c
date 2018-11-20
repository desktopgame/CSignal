#include "bc_double.h"
#include "../../bc_library_impl.h"

//proto
static void bc_double_nativeInit(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeEquals(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeAdd(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeSub(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeMul(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeDiv(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeGT(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeGE(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeLT(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeLE(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);
static void bc_double_nativeEQ(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env);

bc_Object* NewDouble(double value) {
	Double* ret = bc_ConstructObject(sizeof(Double), BC_GENERIC_DOUBLE);
	ret->Value = value;
	return (bc_Object*)ret;
}

void InitDouble() {
	bc_Namespace* lang = bc_GetLangNamespace();
	bc_Type* doubleType = bc_NewPreloadClass(bc_InternString("Double"));
	bc_Class* doubleClass = BC_TYPE2CLASS(doubleType);
	doubleType->AllocSize = sizeof(Double);
	bc_AddTypeNamespace(lang, doubleType);
	bc_DefineNativeMethodClass(doubleClass, "nativeInit", bc_double_nativeInit);
	bc_DefineNativeMethodClass(doubleClass, "nativeEquals", bc_double_nativeEquals);
	bc_DefineNativeMethodClass(doubleClass, "nativeAdd", bc_double_nativeAdd);
	bc_DefineNativeMethodClass(doubleClass, "nativeSub", bc_double_nativeSub);
	bc_DefineNativeMethodClass(doubleClass, "nativeMul", bc_double_nativeMul);
	bc_DefineNativeMethodClass(doubleClass, "nativeDiv", bc_double_nativeDiv);
	bc_DefineNativeMethodClass(doubleClass, "nativeGT", bc_double_nativeGT);
	bc_DefineNativeMethodClass(doubleClass, "nativeGE", bc_double_nativeGE);
	bc_DefineNativeMethodClass(doubleClass, "nativeLT", bc_double_nativeLT);
	bc_DefineNativeMethodClass(doubleClass, "nativeLE", bc_double_nativeLE);
	bc_DefineNativeMethodClass(doubleClass, "nativeEQ", bc_double_nativeEQ);
}

bc_Type* GetDoubleType() {
	bc_Namespace* lang = bc_GetLangNamespace();
	return bc_FindTypeFromNamespace(lang, bc_InternString("Double"));
}
//private
#define DOUBLE_VALUE(obj) (((Double*)obj)->Value)
static void bc_double_nativeInit(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* d = bc_AtVector(fr->VariableTable, 1);

	DOUBLE_VALUE(self) = DOUBLE_VALUE(d);
	//self->Tag = OBJECT_DOUBLE_T;
}

static void bc_double_nativeEquals(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* d = bc_AtVector(fr->VariableTable, 1);
	bc_PushVector(fr->ValueStack, bc_BoolToObject(bc_ObjectToDouble(self) == bc_ObjectToDouble(d)));
}

static void bc_double_nativeAdd(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = (bc_Object*)NewDouble(DOUBLE_VALUE(self) + DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeSub(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = (bc_Object*)NewDouble(DOUBLE_VALUE(self) - DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeMul(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = (bc_Object*)NewDouble(DOUBLE_VALUE(self) * DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeDiv(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = (bc_Object*)NewDouble(DOUBLE_VALUE(self) / DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeGT(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(DOUBLE_VALUE(self) > DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeGE(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(DOUBLE_VALUE(self) >= DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeLT(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(DOUBLE_VALUE(self) < DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeLE(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(DOUBLE_VALUE(self) <= DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}

static void bc_double_nativeEQ(bc_Method* parent, bc_Frame* fr, bc_Enviroment* env) {
	bc_Object* self = bc_AtVector(fr->VariableTable, 0);
	bc_Object* a = bc_AtVector(fr->VariableTable, 1);
	bc_Object* ret = bc_GetBoolObject(DOUBLE_VALUE(self) == DOUBLE_VALUE(a));
	bc_PushVector(fr->ValueStack, ret);
}