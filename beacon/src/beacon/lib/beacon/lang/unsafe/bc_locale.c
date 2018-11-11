#include "bc_locale.h"
#include "../../../../env/namespace.h"
#include "../../../../env/TYPE_IMPL.h"
#include "../../../../util/string_buffer.h"
#include "../../../../util/text.h"
#include "../../../bc_library_impl.h"
#include "../bc_string.h"
#include <assert.h>
#include <locale.h>

static void bc_locale_nativeSetLocale(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetDecimalPoint(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetThousandsSep(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetIntCurrSymbol(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetCurrencySymbol(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetMonDecimalPoint(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetMonThousandsSep(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetPositiveSign(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetNegativeSign(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetIntFracDigits(Method* parent, Frame* fr, Enviroment* env);
static void bc_locale_nativeGetFracDigits(Method* parent, Frame* fr, Enviroment* env);

void InitLocaleType() {
	Namespace* unsafe = GetUnsafeNamespace();
	Type* localeType = NewPreloadClass(InternString("Locale"));
	Class* localeClass = TYPE2CLASS(localeType);
	AddTypeNamespace(unsafe, localeType);
	DefineNativeMethodClass(localeClass, "nativeSetLocale", bc_locale_nativeSetLocale);
	DefineNativeMethodClass(localeClass, "nativeGetDecimalPoint", bc_locale_nativeGetDecimalPoint);
	DefineNativeMethodClass(localeClass, "nativeGetThousandsSep", bc_locale_nativeGetThousandsSep);
	DefineNativeMethodClass(localeClass, "nativeGetIntCurrSymbol", bc_locale_nativeGetIntCurrSymbol);
	DefineNativeMethodClass(localeClass, "nativeGetCurrencySymbol", bc_locale_nativeGetCurrencySymbol);
	DefineNativeMethodClass(localeClass, "nativeGetMonDecimalPoint", bc_locale_nativeGetMonDecimalPoint);
	DefineNativeMethodClass(localeClass, "nativeGetMonThousandsSep", bc_locale_nativeGetMonThousandsSep);
	DefineNativeMethodClass(localeClass, "nativeGetPositiveSign", bc_locale_nativeGetPositiveSign);
	DefineNativeMethodClass(localeClass, "nativeGetNegativeSign", bc_locale_nativeGetNegativeSign);
	DefineNativeMethodClass(localeClass, "nativeGetIntFracDigits", bc_locale_nativeGetIntFracDigits);
	DefineNativeMethodClass(localeClass, "nativeGetFracDigits", bc_locale_nativeGetFracDigits);
}

Type* GetLocaleType() {
	Namespace* unsafe = GetUnsafeNamespace();
	return FindTypeFromNamespace(unsafe, InternString("Locale"));
}
//private
static void bc_locale_nativeSetLocale(Method* parent, Frame* fr, Enviroment* env) {
	Object* categoryObj = AtVector(fr->VariableTable, 1);
	Object* localeObj = AtVector(fr->VariableTable, 2);
	int category = ObjectToInt(categoryObj);
	switch(category) {
		case 0:
			category = LC_ALL;
			break;
		case 1:
			category = LC_COLLATE;
			break;
		case 2:
			category = LC_CTYPE;
			break;
		case 3:
			category = LC_MONETARY;
			break;
		case 4:
			category = LC_NUMERIC;
			break;
		case 5:
			category = LC_TIME;
			break;
	}
	const char* locale = GetRawString(localeObj)->Text;
	assert(setlocale(category, locale) != NULL);
}

static void bc_locale_nativeGetDecimalPoint(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->decimal_point));
}

static void bc_locale_nativeGetThousandsSep(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->thousands_sep));
}

static void bc_locale_nativeGetIntCurrSymbol(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->int_curr_symbol));
}

static void bc_locale_nativeGetCurrencySymbol(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->currency_symbol));
}

static void bc_locale_nativeGetMonDecimalPoint(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->mon_decimal_point));
}

static void bc_locale_nativeGetMonThousandsSep(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->mon_thousands_sep));
}

static void bc_locale_nativeGetPositiveSign(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->positive_sign));
}

static void bc_locale_nativeGetNegativeSign(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, NewString(lc->negative_sign));
}

static void bc_locale_nativeGetIntFracDigits(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, GetIntObject(lc->int_frac_digits));
}

static void bc_locale_nativeGetFracDigits(Method* parent, Frame* fr, Enviroment* env) {
	struct lconv* lc = localeconv();
	PushVector(fr->ValueStack, GetIntObject(lc->frac_digits));
}
