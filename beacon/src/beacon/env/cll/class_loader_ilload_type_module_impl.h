//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_loader_ilload_type_module_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#define BEACON_ENV_CLL_CLASS_LOADER_MODULE_H
#include "../../util/vector.h"
//このファイルは非公開ヘッダーか .c からのみインクルードして下さい。
struct bc_AST;
struct FQCNCache;
struct GenericCache;
struct ClassLoader;

void CLILFQCNCache(struct bc_AST* afqcn, struct FQCNCache* fqcn);

void CLILGenericCache(struct bc_AST* afqcn, struct GenericCache* dest);

/**
 * 型名の一覧を dst へ出力します.
 * @param self
 * @param dst
 * @param typename_list
 */
void CLILTypenameList(struct ClassLoader* self, Vector* dst, struct bc_AST* atypename_list);


void CLILTypeParameter(struct ClassLoader* self, struct bc_AST* asource, Vector* dest);

void CLILTypeArgument(struct ClassLoader* self, struct bc_AST* atype_args, Vector* dest);

void CLILParameterList(struct ClassLoader* self, Vector* list, struct bc_AST* asource);

void CLILArgumentList(struct ClassLoader* self, Vector* list, struct bc_AST* asource);
#endif