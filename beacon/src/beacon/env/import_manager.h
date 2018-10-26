#pragma once
#ifndef BEACON_ENV_IMPORT_MANAGER_H
#define BEACON_ENV_IMPORT_MANAGER_H
#include "../util/vector.h"
//#include "virtual_type.h"
//#include "fqcn_cache.h"
struct GenericCache;
struct GenericType;
struct FQCNCache;
struct Namespace;
struct class_loader;
struct ImportInfo;
struct CallContext;

/**
 * あるファイルが参照しているファイルの一覧を管理します.
 */
typedef struct ImportManager {
	Vector* Items;
} ImportManager;

/**
 * インポートマネージャを作成します.
 * @return
 */
ImportManager* NewImportManager();

/**
 * 指定のクラスローダをインポートの一覧に含めます.
 * @param self
 * @param target
 * @return
 */
struct ImportInfo* ImportImportManager(ImportManager* self, struct class_loader* target);

/**
 * 既に読み込まれたなら true.
 * @param self
 * @param index
 * @return
 */
bool IsLoadedImportManager(ImportManager* self, int index);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param scope
 * @param fqcn
 * @param cctx
 * @return 解決出来なかったなら NULL を返します.
 */
struct GenericType* ResolveImportManager(struct Namespace* scope, struct GenericCache* fqcn, struct CallContext* cctx);

/**
 * 指定の名前から型を解決します.
 * @param self
 * @param scope
 * @param fqcn
 * @param cctx
 * @return 解決出来なかったなら NULL を返します.
 */
struct GenericType* ResolvefImportManager(struct Namespace* scope, struct FQCNCache* fqcn, struct CallContext* cctx);

/**
 * インポートマネージャを開放します.
 * @param self
 */
void DeleteImportManager(ImportManager* self);
#endif // !SIGNAL_ENV_IMPORT_MANAGER_H
