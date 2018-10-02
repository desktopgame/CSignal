#include "bc_time.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <time.h>
#include <assert.h>

#if defined(_MSC_VER)
#pragma warning(disable:4996)
#endif

static void bc_time_nativeGetRawTime(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeToString(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetSecond(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetMinute(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetHour(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDay(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetYear(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDayOfWeek(method* parent, frame* fr, enviroment* env);
static void bc_time_nativeGetDayOfYear(method* parent, frame* fr, enviroment* env);

void bc_time_init() {
	namespace_* unsafe = GetUnsafeNamespace();
	type* timeType = class_new_preload(InternString("Time"));
	class_* timeClass = TYPE2CLASS(timeType);
	AddTypeNamespace(unsafe, timeType);
	class_define_native_method(timeClass, "nativeRawTime", bc_time_nativeGetRawTime);
	class_define_native_method(timeClass, "nativeToString", bc_time_nativeToString);
	class_define_native_method(timeClass, "nativeGetSecond", bc_time_nativeGetSecond);
	class_define_native_method(timeClass, "nativeGetMinute", bc_time_nativeGetMinute);
	class_define_native_method(timeClass, "nativeGetHour", bc_time_nativeGetHour);
	class_define_native_method(timeClass, "nativeGetDay", bc_time_nativeGetDay);
	class_define_native_method(timeClass, "nativeGetYear", bc_time_nativeGetYear);
	class_define_native_method(timeClass, "nativeGetDayOfWeek", bc_time_nativeGetDayOfWeek);
	class_define_native_method(timeClass, "nativeGetDayOfYear", bc_time_nativeGetDayOfYear);
}

type* bc_time_type() {
	namespace_* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("Time"));
}
//private
static void bc_time_nativeGetRawTime(method* parent, frame* fr, enviroment* env) {
	time_t tref;
	time(&tref);
	//FIXME:long型を導入する
	PushVector(fr->value_stack, object_long_new(tref));
}

static void bc_time_nativeToString(method* parent, frame* fr, enviroment* env) {
	object* self = AtVector(fr->ref_stack, 0);
	int temp;
	class_find_field(TYPE2CLASS(bc_time_type()), InternString("rawTime"), &temp);
	object* rawTime = (object*)AtVector(self->u.field_vec, temp);
	PushVector(fr->value_stack, object_string_new(ctime(&(rawTime->u.long_))));
}

static void bc_time_nativeGetSecond(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_sec));
}

static void bc_time_nativeGetMinute(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_min));
}

static void bc_time_nativeGetHour(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_hour));
}

static void bc_time_nativeGetDay(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_mday));
}

static void bc_time_nativeGetYear(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_year));
}

static void bc_time_nativeGetDayOfWeek(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_wday));
}

static void bc_time_nativeGetDayOfYear(method* parent, frame* fr, enviroment* env) {
	object* rawTime = AtVector(fr->ref_stack, 1);
	PushVector(fr->value_stack, GetIntObject(localtime(&(rawTime->u.long_))->tm_yday));
}
