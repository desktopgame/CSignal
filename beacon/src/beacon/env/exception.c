#include "exception.h"
#include "object.h"
#include "namespace.h"
#include "TYPE_IMPL.h"
#include <assert.h>
#include "../lib/bc_library_interface.h"
#include "../util/text.h"
#include "../vm/frame.h"
#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

//proto
static Class* exception_class();

Object * NewSimpleException(Frame* fr, const char* message) {
	Class* excClass = exception_class();
	Vector* args = NewVector();
	PushVector(args, NewString(message));
	Object* e = NewInstanceClass(excClass, fr, args, NULL);
	DeleteVector(args, VectorDeleterOfNull);
	return e;
}

Object * NewSimplefException(Frame* fr, const char * message, ...) {
	va_list ap;
	va_start(ap, message);
#define LEN 256
	char block[LEN];
	int res = vsprintf(block, message, ap);
	assert(res != -1);
#undef LEN
	va_end(ap);
	return NewSimpleException(fr, block);
}

//private
static Class* exception_class() {
	Namespace* lang = GetLangNamespace();
	Class* excClass = FindClassFromNamespace(lang, InternString("Exception"));
	assert(excClass != NULL);
	return excClass;
}