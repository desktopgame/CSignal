#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"

struct enviroment;
struct generic_type;
struct operator_overload;
struct method;
//binded? bound?

typedef enum bound_invoke {
	BOUND_INVOKE_METHOD_T,
	BOUND_INVOKE_SUBSCRIPT_T,
	BOUND_INVOKE_UNDEFINED_T
} bound_invoke;

typedef struct il_factor_invoke_bound {
	string_view namev;
	Vector* type_args;
	Vector* args;
	union {
		struct method* m;
		subscript_descriptor subscript;
	} u;
	int index;
	struct generic_type* resolved;
	bound_invoke tag;
} il_factor_invoke_bound;

il_factor_invoke_bound* NewILInvokeBound(string_view namev);

void GenerateILInvokeBound(il_factor_invoke_bound* self, struct enviroment* env, call_context* cctx);

void LoadILInvokeBound(il_factor_invoke_bound * self, struct enviroment * env, call_context* cctx);

struct generic_type* EvalILInvokeBound(il_factor_invoke_bound * self, struct enviroment * env, call_context* cctx);

char* ILInvokeBoundToString(il_factor_invoke_bound* self, struct enviroment* env);

void DeleteILInvokeBound(il_factor_invoke_bound* self);

struct operator_overload* FindSetILInvokeBound(il_factor_invoke_bound* self, il_factor* value, struct enviroment* env, call_context* cctx, int* outIndex);
#endif