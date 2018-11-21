//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_invoke_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_FACTOR_INVOKE_H
#define BEACON_IL_IL_FACTOR_INVOKE_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"
struct bc_Enviroment;
struct bc_GenericType;
struct bc_OperatorOverload;
struct bc_Method;

typedef enum InstanceInvokeTag {
	INSTANCE_INVOKE_METHOD_T,
	INSTANCE_INVOKE_SUBSCRIPT_T,
	INSTANCE_INVOKE_UNDEFINED_T
} InstanceInvokeTag;

typedef struct ILInvoke {
	bc_ILFactor* receiver;
	bc_Vector* args;
	bc_Vector* type_args;
	bc_StringView namev;
	int index;
	union {
		struct bc_Method* m;
		struct bc_OperatorOverload* opov;
	} u;
	struct bc_GenericType* resolved;
	InstanceInvokeTag tag;
} ILInvoke;

ILInvoke* NewILInvoke(bc_StringView namev);

void GenerateILInvoke(ILInvoke* self, bc_Enviroment* env, bc_CallContext* cctx);

void LoadILInvoke(ILInvoke * self, bc_Enviroment * env, bc_CallContext* cctx);

struct bc_GenericType* EvalILInvoke(ILInvoke * self, bc_Enviroment * env, bc_CallContext* cctx);

char* ILInvokeToString(ILInvoke* self, bc_Enviroment* env);

void DeleteILInvoke(ILInvoke* self);

struct bc_OperatorOverload* FindSetILInvoke(ILInvoke* self, bc_ILFactor* value, bc_Enviroment* env, bc_CallContext* cctx, int* outIndex);
#endif