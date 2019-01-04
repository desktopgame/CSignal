// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_factor_instanceof_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#define BEACON_IL_IL_FACTOR_INSTANCEOF_IMPL_H
#include "../il_factor_interface.h"
struct bc_GenericCache;
struct bc_GenericType;
struct bc_FQCNCache;

typedef struct bc_ILInstanceOf {
        bc_ILFactor* Source;
        struct bc_GenericCache* GCache;
} bc_ILInstanceOf;

bc_ILFactor* bc_WrapILInstanceOf(bc_ILInstanceOf* self);

bc_ILInstanceOf* bc_NewILInstanceOf();

void bc_LoadILInstanceOf(bc_ILInstanceOf* self, bc_Enviroment* env,
                         bc_CallContext* cctx);

void bc_GenerateILInstanceOf(bc_ILInstanceOf* self, bc_Enviroment* env,
                             bc_CallContext* cctx);

struct bc_GenericType* bc_EvalILInstanceOf(bc_ILInstanceOf* self,
                                           bc_Enviroment* env,
                                           bc_CallContext* cctx);

char* bc_ILInstanceOfToString(bc_ILInstanceOf* self, bc_Enviroment* env);

void bc_DeleteILInstanceOf(bc_ILInstanceOf* self);
#endif