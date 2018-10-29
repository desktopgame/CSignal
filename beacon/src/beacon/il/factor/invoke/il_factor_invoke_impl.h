#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct Enviroment;
struct GenericType;
struct OperatorOverload;
struct Method;

typedef enum InstanceInvokeTag {
	INSTANCE_INVOKE_METHOD_T,
	INSTANCE_INVOKE_SUBSCRIPT_T,
	INSTANCE_INVOKE_UNDEFINED_T
} InstanceInvokeTag;

typedef struct ILInvoke {
	ILFactor* receiver;
	Vector* args;
	Vector* type_args;
	StringView namev;
	int index;
	union {
		struct Method* m;
		struct OperatorOverload* opov;
	} u;
	struct GenericType* resolved;
	InstanceInvokeTag tag;
} ILInvoke;

ILInvoke* NewILInvoke(StringView namev);

void GenerateILInvoke(ILInvoke* self, Enviroment* env, CallContext* cctx);

void LoadILInvoke(ILInvoke * self, Enviroment * env, CallContext* cctx);

struct GenericType* EvalILInvoke(ILInvoke * self, Enviroment * env, CallContext* cctx);

char* ILInvokeToString(ILInvoke* self, Enviroment* env);

void DeleteILInvoke(ILInvoke* self);

struct OperatorOverload* FindSetILInvoke(ILInvoke* self, ILFactor* value, Enviroment* env, CallContext* cctx, int* outIndex);
#endif