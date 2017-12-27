#pragma once
#ifndef SIGNAL_ENV_NAMESPACE_H
#define SIGNAL_ENV_NAMESPACE_H
#include "../util/tree_map.h"
#include <stdint.h>
#define CL_INT namespace_int_class()
#define CL_DOUBLE namespace_double_class()
#define CL_CHAR namespace_char_class()
#define CL_STRING namespace_string_class()

struct class_;
/**
 * 名前空間を表す構造体.
 */
typedef struct namespace_ {
	char* name;
	struct namespace_* parent;
	tree_map* namespace_map;
	tree_map* class_map;
	uint32_t ref_count;
} namespace_;

/**
 * 指定の名前でトップレベルに新しい名前空間を定義します.
 * @param name
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_create_at_root(char* name);

/**
 * 指定の名前でトップレベルから名前空間を検索します.
 * @param name
 * @return
 */
namespace_* namespace_get_at_root(char* name);

/**
 * 指定の名前空間に新しい名前空間を定義します.
 * @param self
 * @param name
 * @return 既に存在するならそれを返します.
 */
namespace_* namespace_add_namespace(namespace_* self, char* name);

/**
 * この名前空間にクラスを含めます.
 * クラスのカウントは +1 されます。
 * @param self
 * @param classz
 */
struct class_* namespace_add_class(namespace_* self, struct class_* classz);

/**
 * 指定の名前空間から指定の名前の名前空間を検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
namespace_* namespace_get_namespace(namespace_* self, const char* name);

/**
 * 指定の名前空間で指定の名前のクラスを検索します.
 * @param self
 * @param name
 * @return 見つからないなら NULL
 */
struct class_* namespace_get_class(namespace_* self, const char* name);

/**
 * signal 名前空間を返します.
 * @return
 */
namespace_* namespace_signal();

/**
 * signal.lang 名前空間を返します.
 * @return
 */
namespace_* namespace_lang();

/**
 * 現在のスクリプトコンテキストで int クラスを返します.
 * @return
 */
struct class_* namespace_int_class();

/**
 * 現在のスクリプトコンテキストで double クラスを返します.
 * @return
 */
struct class_* namespace_double_class();

/**
 * 現在のスクリプトコンテキストで char クラスを返します.
 * @return
 */
struct class_* namespace_char_class();

/**
 * 現在のスクリプトコンテキストで string クラスを返します.
 * @return
 */
struct class_* namespace_string_class();

/**
 * 全ての名前空間を出力します.
 */
void namespace_dump();
#endif // !SIGNAL_ENV_NAMESPACE_H
