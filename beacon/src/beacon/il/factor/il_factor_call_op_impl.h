//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_call_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_ILCallOp_H
#define BEACON_IL_ILCallOp_H
#include "../../util/vector.h"
#include "../il_factor_interface.h"
#include "invoke/il_factor_invoke_impl.h"
#include "invoke/il_factor_invoke_static_impl.h"
#include "invoke/il_factor_invoke_bound_impl.h"


struct Enviroment;
struct bc_GenericType;
/**
 * 関数呼び出し演算子の種類を表す列挙型.
 */
typedef enum ILCallType {
	ILCALL_TYPE_INVOKE_T,
	ILCALL_TYPE_INVOKE_STATIC_T,
	ILCALL_TYPE_INVOKE_BOUND_T,
	ILCALL_TYPE_UNDEFINED_T,
} ILCallType;

/**
 * 関数呼び出し演算子を表す構造体.
 */
typedef struct ILCallOp {
	ILFactor* Parent;
	ILFactor* Receiver;
	//Vector* type_argument_list;
	Vector* Arguments;
	ILCallType Type;
	union {
		ILInvoke* Invoke;
		ILInvokeStatic* InvokeStatic;
		ILInvokeBound* InvokeBound;
	} Kind;
} ILCallOp;

ILFactor* WrapCallOp(ILCallOp* self);

ILCallOp* NewILCallOp();

void LoadCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx);

struct bc_GenericType* EvalILCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx);

char* ILCallOpToString(ILCallOp* self, Enviroment* env);

void GenerateILCallOp(ILCallOp* self, Enviroment* env, CallContext* cctx);

void DeleteILCallOp(ILCallOp* self);

#endif
