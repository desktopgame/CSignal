// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file yield_context.h
 * @brief 'yield
 * return'が実行された時点でのコンテキストを保存する構造体を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_VM_YIELD_CONTEXT_H
#define BEACON_VM_YIELD_CONTEXT_H
#include "../util/vector.h"
struct bc_Object;

typedef struct bc_YieldContext {
        bc_Vector* BackupVariableTable;
        bc_Vector* BackupValueStack;
        bc_Vector* VariableTable;
        bc_Vector* ValueStack;
        bc_Vector* Parameters;
        struct bc_Object* Source;
        struct bc_Object* Stock;
        bool IsCached;
        int YieldCount;
        int YieldOffset;
        int Length;
} bc_YieldContext;

#define bc_NewYieldContext() (bc_MallocYieldContext(__FILE__, __LINE__))
bc_YieldContext* bc_MallocYieldContext(const char* filename, int lineno);

void bc_ClearBackupYieldContext(bc_YieldContext* self);

void bc_DeleteYieldContext(bc_YieldContext* self);
#endif