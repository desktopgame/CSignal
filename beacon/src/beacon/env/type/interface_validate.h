#ifndef BEACON_ENV_TYPE_INTERFACE_VALID_H
#define BEACON_ENV_TYPE_INTERFACE_VALID_H
#include "../../util/string_pool.h"
#include <stdbool.h>
struct Interface;
struct Method;
/**
 * 全てのメソッドを巡回して、全てにおいてパラメータ名の重複がないなら true.
 * @param inter
 * @param out
 * @return
 */
bool IsMethodParameterValidInterface(struct Interface* inter, struct Method** out_method, StringView* out_name);

/**
 * インターフェイスの型変数に重複する名前がないなら true.
 * @param inter
 * @param out_name
 * @return
 */
bool IsTypeParameterValidInterface(struct Interface* inter, StringView* out_name);

/**
 * メソッドの型変数に重複するものがないなら true.
 * @param self
 * @param out_method
 * @param out_name
 * @return
 */
bool IsMethodTypeParameterValidInterface(struct Interface* inter, struct Method** out_method, StringView* out_name);

#endif