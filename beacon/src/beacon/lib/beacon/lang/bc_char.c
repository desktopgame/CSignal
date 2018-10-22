#include "bc_char.h"
#include "../../bc_library_impl.h"

//proto
static void bc_char_nativeInit(method* parent, Frame* fr, Enviroment* env);
static void bc_char_nativeToInt(method* parent, Frame* fr, Enviroment* env);

void InitBCChar() {
	namespace_* lang = GetLangNamespace();
	type* charType = NewPreloadClass(InternString("Char"));
	class_* charClass = TYPE2CLASS(charType);
	AddTypeNamespace(lang, charType);
	DefineNativeMethodClass(charClass, "nativeInit", bc_char_nativeInit);
	DefineNativeMethodClass(charClass, "nativeToInt", bc_char_nativeToInt);
}

type* GetBCCharType() {
	namespace_* lang = GetLangNamespace();
	return FindTypeFromNamespace(lang, InternString("Char"));
}

//private
static void bc_char_nativeInit(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	object* ch = AtVector(fr->VariableTable, 1);

	self->u.char_ = ch->u.char_;
	self->tag = OBJECT_CHAR_T;
}

static void bc_char_nativeToInt(method* parent, Frame* fr, Enviroment* env) {
	object* self = AtVector(fr->VariableTable, 0);
	PushVector(fr->ValueStack, GetIntObject((int)self->u.char_));
}