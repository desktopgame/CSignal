// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_loader_ilload_stmt_module_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_ILLOAD_STMT_MODULE_IMPL_H
#include "../../util/vector.h"
struct bc_ClassLoader;
struct bc_AST;
struct bc_ILStatement;

struct bc_ILStatement* CLILStmt(struct bc_ClassLoader* self,
                                struct bc_AST* source);

void CLILBody(struct bc_ClassLoader* self, bc_Vector* list,
              struct bc_AST* source);
#endif