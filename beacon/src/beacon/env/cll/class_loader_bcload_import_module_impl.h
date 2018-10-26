#ifndef BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_IMPORT_MODULE_IMPL_H
#define BEACON_ENV_CLL_CLASS_LOADER_BCLOAD_IMPORT_MODULE_IMPL_H
#include "../class_loader.h"

/**
 * インポートの一覧を確認して、読み込むべきファイルがあるなら読み込みます.
 * @param self
 * @param ilimports
 */
void CLBC_import(ClassLoader* self, Vector* ilimports);
/**
 * selfを親として fullPath のファイルを読み込みます.
 * @param self
 * @param fullPath
 */
void CLBC_new_load(ClassLoader* self, char* fullPath);

/**
 * fullPathをロードするためのローダを作成して返します.
 * @param self
 * @param fullPath
 * @return
 */
ClassLoader* CLBC_import_new(ClassLoader* self, char* fullPath);
#endif