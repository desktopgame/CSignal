// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_loader_bcload_impl.h
 * @brief ILをBCヘ変換するための関数を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_CLASS_LOADER_SGLOAD_IMPL_H
#define BEACON_ENV_CLASS_LOADER_SGLOAD_IMPL_H
//このヘッダーは class_loader.h 以外からはインクルードしないでください。
#include "../class_loader.h"
#include "../link_type.h"

/**
 * 全ての中間言語をもっとも抽象的なモデルであるBCへ変換します.
 * BCは静的に型付けされたクラス階層をそのまま表現します。
 * @param self
 */
void BCLoadClassLoader(bc_ClassLoader* self);

/**
 * beacon/langを仮読み込みするための関数.
 * @param self
 */
void SpecialBCLoadClassLoader(bc_ClassLoader* self);
#endif