//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file fqcn_cache.h
 * @brief 型の完全名を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_FQCN_CACHE_H
#define BEACON_ENV_FQCN_CACHE_H
#include "../util/vector.h"
#include "../util/string_pool.h"
struct bc_Namespace;
struct bc_Type;
struct Class;
struct Interface;
//struct Enviroment;
/**
 * Full Quality Class Name を表す構造体.
 */
typedef struct bc_FQCNCache {
	Vector* Scope;
	StringView Name;
} bc_FQCNCache;

/**
 * FQCNキャッシュを作成します.
 * @return
 */
#define bc_NewFQCNCache() (bc_MallocFQCNCache(__FILE__, __LINE__))

/**
 * FQCNキャッシュを作成します.
 * @return
 */
bc_FQCNCache* bc_MallocFQCNCache(const char* filename, int lineno);

/**
 * FQCNキャッシュを出力します.
 * @param self
 * @param depth
 */
void bc_DumpFQCNCache(bc_FQCNCache* self, int depth);

/**
 * FQCNを切り詰めて改行せずに表示します.
 * @param self
 */
void bc_PrintFQCNCache(bc_FQCNCache* self);

/**
 * FQCNが示す名前空間を返します.
 * X::Y ではなく、 Y の場合は NULL を返します。
 * @param self
 * @param current
 * @return
 */
struct bc_Namespace* bc_GetScopeFQCN(bc_FQCNCache* self, struct bc_Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param stelf
 * @param current
 * @return
 */
struct bc_Type* bc_GetTypeFQCN(bc_FQCNCache* self, struct bc_Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct Interface* bc_GetInterfaceFQCN(bc_FQCNCache* self, struct bc_Namespace* current);

/**
 * X::Y の表すタイプを返します.
 * 絶対参照のときは引数 current は無視されます。
 * @param self
 * @param current
 * @return
 */
struct Class* bc_GetClassFQCN(bc_FQCNCache* self, struct bc_Namespace* current);

/**
 * 文字列に変換して返します.
 * @param self
 * @return
 */
char* bc_FQCNCacheToString(bc_FQCNCache* self);

/**
 * FQCNキャッシュを開放します.
 * @param self
 */
void bc_DeleteFQCNCache(bc_FQCNCache* self);

/**
 * 二つが同じなら true.
 * @param a
 * @param b
 * @return
 */
bool bc_EqualsFQCNCache(bc_FQCNCache* a, bc_FQCNCache* b);
#endif // !SIGNAL_ENV_FQCN_CACHE_H
