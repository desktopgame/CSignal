#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct Enviroment;
struct GenericType;
struct Method;

typedef struct ILFactor_invoke_static {
	StringView namev;
	FQCNCache* fqcn;
	Vector* args;
	Vector* type_args;
	struct Method* m;
	int index;
	struct GenericType* resolved;
} ILFactor_invoke_static;

ILFactor_invoke_static* NewILInvokeStatic(StringView namev);

void GenerateILInvokeStatic(ILFactor_invoke_static* self, Enviroment* env, CallContext* cctx);

void LoadILInvokeStatic(ILFactor_invoke_static * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvokeStatic(ILFactor_invoke_static * self, Enviroment * env, CallContext* cctx);

char* ILInvokeStaticToString(ILFactor_invoke_static* self, Enviroment* env);

void DeleteILInvokeStatic(ILFactor_invoke_static* self);
#endif