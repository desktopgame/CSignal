#pragma once
#ifndef BEACON_ENV_TYPE_IINTERFACE_H
#define BEACON_ENV_TYPE_IINTERFACE_H
#include "../type_interface.h"
#include "../namespace.h"
#include "../vtable.h"
#include "../../util/vector.h"
struct method;
struct enviroment;
struct generic_type;
struct type;
/**
 * インターフェースを表す構造体.
 */
typedef struct interface_ {
	struct type* parent;
	char* name;
	vector* impl_list;
	vector* method_list;
	namespace_* location;
	vtable* vt;
	vector* type_parameter_list;
} interface_;

/**
 * インターフェイスをスーパーセットにラップします.
 * @param self
 * @return
 */
type* type_wrap_interface(interface_* self);

/** 
 * インターフェイスを作成します.
 * @param name
 * @return
 */
interface_* interface_new(const char* name);

/**
 * インターフェイスにメソッドを追加します.
 * @param self
 * @param m
 */
void interface_add_method(interface_* self, struct method* m);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param name
 * @param args
 * @param env
 * @param cache
 * @param outIndex
 * @return
 */
struct method* interface_ilfind_method(interface_* self, const char * name, vector * args, struct enviroment * env, int * outIndex);

/**
 * インターフェイスからメソッドを検索します.
 * @param self
 * @param name
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* interface_gfind_method(interface_* self, const char* name, vector* gargs, int* outIndex);

/**
 * 全てのインターフェイスに定義されたメソッドをフラットにして返します.
 * @param inter_list
 * @return
 */
vector* interface_method_flatten_list(vector* inter_list);

/**
 * あるインターフェイスとそれ自体が実装しているインターフェイスの一覧の
 * メソッドを一つのリストにして返します.
 * @param self
 * @return 呼び出し側で開放してください
 */
vector* interface_method_flatten(interface_* self);

/**
 * インターフェイスをダンプします.
 * @param self
 * @param depth
 */
void interface_dump(interface_* self, int depth);

/**
 * メソッドの一覧から vtable を作成します.
 * @param self
 */
void interface_create_vtable(interface_* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void interface_unlink(interface_* self);

/**
 * インターフェイスを開放します.
 * @param self
 */
void interface_delete(interface_* self);

/**
 * self に find が含まれるなら NULL 以外の値を返します.
 * @param source
 * @param find
 * @return
 */
struct generic_type* interface_contains(struct generic_type* source, interface_* find);

/**
 * 関数型インターフェイスであるならtrue.
 * @param self
 * @return
 */
bool interface_is_functional(interface_* self);
#endif // !SIGNAL_ENV_TYPE_IINTERFACE_H
