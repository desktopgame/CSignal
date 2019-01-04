// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_negative_op_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#define BEACON_IL_FACTOR_UNARY_IL_FACTOR_NEGATIVE_OP_IMPL_H
#include "../../../ast/operator_type.h"
#include "../../call_context.h"
struct bc_ILUnaryOp;
struct bc_GenericType;
struct bc_Enviroment;

typedef struct bc_ILNegativeOp {
        struct bc_ILUnaryOp* Parent;
        bc_OperatorType Type;
        int OperatorIndex;
} bc_ILNegativeOp;

#define bc_NewILNegativeOp(type) \
        (bc_MallocILNegativeOp(type, __FILE__, __LINE__))
bc_ILNegativeOp* bc_MallocILNegativeOp(bc_OperatorType type,
                                       const char* filename, int lineno);

struct bc_GenericType* bc_EvalILNegativeOp(bc_ILNegativeOp* self,
                                           struct bc_Enviroment* env,
                                           bc_CallContext* cctx);

void bc_GenerateILNegativeOp(bc_ILNegativeOp* self, struct bc_Enviroment* env,
                             bc_CallContext* cctx);

void bc_LoadILNegativeOp(bc_ILNegativeOp* self, struct bc_Enviroment* env,
                         bc_CallContext* cctx);

void bc_DeleteILNegativeOp(bc_ILNegativeOp* self);

char* bc_ILNegativeOpToString(bc_ILNegativeOp* self, struct bc_Enviroment* env);
#endif