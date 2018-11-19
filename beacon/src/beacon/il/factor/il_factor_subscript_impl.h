//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_subscript_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_SUBSCRIPT_H
#define BEACON_IL_FACTOR_SUBSCRIPT_H
#include "../il_factor_interface.h"

struct bc_OperatorOverload;

typedef struct ILSubscript {
	ILFactor* Receiver;
	ILFactor* Position;
	int OperatorIndex;
	struct bc_OperatorOverload* Operator;
} ILSubscript;

ILFactor* WrapILSubscript(ILSubscript* self);

#define NewILSubscript() (MallocILSubscript(__FILE__, __LINE__))
ILSubscript* MallocILSubscript(const char* filename, int lineno);

void GenerateILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

void LoadILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

bc_GenericType* EvalILSubscript(ILSubscript* self, Enviroment* env, CallContext* cctx);

char* ILSubscriptToString(ILSubscript* self, Enviroment* env);

void DeleteILSubscript(ILSubscript* self);
#endif