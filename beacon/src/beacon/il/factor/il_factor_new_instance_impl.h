//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_new_instance_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#define BEACON_IL_IL_FACTOR_NEW_INSTANCE_H
#include "../../util/vector.h"
#include "../../env/fqcn_cache.h"
#include "../../env/generic_cache.h"
#include "../il_factor_interface.h"

struct bc_Enviroment;
struct bc_Type;
struct bc_Constructor;
/**
 * コンストラクタの呼び出しを表す要素.
 */
typedef struct ILNewInstance {
	bc_Vector* Arguments;
	bc_FQCNCache* FQCNCache;
	bc_Vector* TypeArgs;
//	GenericCache* fqcn;
	bc_GenericType* InstanceGType;
	struct bc_Constructor* Constructor;
	int ConstructorIndex;
} ILNewInstance;

ILFactor* WrapILNewInstance(ILNewInstance* self);

ILNewInstance* NewILNewInstance();

void GenerateILNewInstance(ILNewInstance* self, bc_Enviroment* env, CallContext* cctx);

void LoadILNewInstance(ILNewInstance* self, bc_Enviroment* env, CallContext* cctx);

bc_GenericType* EvalILNewInstance(ILNewInstance* self, bc_Enviroment* env, CallContext* cctx);

char* ILNewInstanceToString(ILNewInstance* self, bc_Enviroment* env);

void DeleteILNewInstance(ILNewInstance* self);

#endif // !SIGNAL_IL_IL_FACTOR_NEW_INSTANCE_H
