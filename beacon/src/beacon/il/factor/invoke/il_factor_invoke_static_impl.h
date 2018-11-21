//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_invoke_static_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#define BEACON_IL_IL_FACTOR_INVOKE_STATIC_H
#include "../../il_factor_interface.h"
#include "../../../env/fqcn_cache.h"
#include "../../../util/string_pool.h"
struct bc_Enviroment;
struct bc_GenericType;
struct bc_Method;

typedef struct ILInvokeStatic {
	bc_StringView Name;
	bc_FQCNCache* FQCN;
	bc_Vector* Arguments;
	bc_Vector* TypeArgs;
	struct bc_Method* Method;
	int Index;
	struct bc_GenericType* Resolved;
} ILInvokeStatic;

ILInvokeStatic* NewILInvokeStatic(bc_StringView namev);

void GenerateILInvokeStatic(ILInvokeStatic* self, bc_Enviroment* env, bc_CallContext* cctx);

void LoadILInvokeStatic(ILInvokeStatic * self, bc_Enviroment * env, bc_CallContext* cctx);

struct bc_GenericType* EvalILInvokeStatic(ILInvokeStatic * self, bc_Enviroment * env, bc_CallContext* cctx);

char* ILInvokeStaticToString(ILInvokeStatic* self, bc_Enviroment* env);

void DeleteILInvokeStatic(ILInvokeStatic* self);
#endif