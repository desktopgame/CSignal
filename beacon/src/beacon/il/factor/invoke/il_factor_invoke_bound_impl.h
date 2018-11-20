//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_invoke_bound_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#define BEACON_IL_IL_FACTOR_INVOKE_BOUND_H
#include "../../il_factor_interface.h"
#include "../../../util/string_pool.h"
#include "subscript_descriptor.h"

struct bc_Enviroment;
struct bc_GenericType;
struct bc_OperatorOverload;
struct bc_Method;
//binded? bound?

typedef enum BoundInvokeTag {
	BOUND_INVOKE_METHOD_T,
	BOUND_INVOKE_SUBSCRIPT_T,
	BOUND_INVOKE_UNDEFINED_T
} BoundInvokeTag;

typedef struct ILInvokeBound {
	bc_StringView Name;
	bc_Vector* TypeArgs;
	bc_Vector* Arguments;
	union {
		struct bc_Method* Method;
		SubscriptDescriptor Subscript;
	} Kind;
	int Index;
	struct bc_GenericType* Resolved;
	BoundInvokeTag Tag;
} ILInvokeBound;

ILInvokeBound* NewILInvokeBound(bc_StringView namev);

void GenerateILInvokeBound(ILInvokeBound* self, bc_Enviroment* env, CallContext* cctx);

void LoadILInvokeBound(ILInvokeBound * self, bc_Enviroment * env, CallContext* cctx);

struct bc_GenericType* EvalILInvokeBound(ILInvokeBound * self, bc_Enviroment * env, CallContext* cctx);

char* ILInvokeBoundToString(ILInvokeBound* self, bc_Enviroment* env);

void DeleteILInvokeBound(ILInvokeBound* self);

struct bc_OperatorOverload* FindSetILInvokeBound(ILInvokeBound* self, ILFactor* value, bc_Enviroment* env, CallContext* cctx, int* outIndex);
#endif