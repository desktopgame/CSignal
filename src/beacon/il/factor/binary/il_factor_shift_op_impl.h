// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_shift_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#define BEACON_IL_FACTOR_BINARY_IL_FACTOR_SHIFT_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct bc_GenericType;
struct bc_Enviroment;
struct bc_ILBinaryOp;
typedef struct bc_ILShiftOp {
        struct bc_ILBinaryOp* Parent;
        bc_OperatorType Type;
        int OperatorIndex;
} bc_ILShiftOp;

bc_ILShiftOp* bc_NewILShiftOp(bc_OperatorType type);

struct bc_GenericType* bc_EvalILShiftOp(bc_ILShiftOp* self,
                                        struct bc_Enviroment* env,
                                        bc_CallContext* cctx);

void bc_GenerateILShiftOp(bc_ILShiftOp* self, struct bc_Enviroment* env,
                          bc_CallContext* cctx);

void bc_LoadILShiftOp(bc_ILShiftOp* self, struct bc_Enviroment* env,
                      bc_CallContext* cctx);

void bc_DeleteILShiftOp(bc_ILShiftOp* self);

char* bc_ILShiftOpToString(bc_ILShiftOp* self, struct bc_Enviroment* env);
#endif