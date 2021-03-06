#pragma once
#ifndef BEACON_ENV_METHOD_H
#define BEACON_ENV_METHOD_H
#include "script_method.h"
#include "native_method.h"
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include <stdbool.h>
struct type;
struct interface_;
struct frame;
struct enviroment;
struct call_context;
struct class_loader;

/**
 * メソッドの種類を表す列挙.
 */
typedef enum method_type {
	method_type_script_T,
	method_type_native_T,
	method_type_abstract_T,
} method_type;

/**
 * メソッドを表す構造体.
 */
typedef struct method {
	string_view namev;
	method_type type;
	//struct class_* decleared_type;
	struct type* parent;
	struct generic_type* return_gtype;
	vector* parameters;
	vector* type_parameters;
	access_level access;
	modifier_type modifier;
	union {
		script_method* script_method;
		native_method* native_method;
	} u;
} method;

/**
 * メソッドを作成します.
 * @param namev
 * @param filename
 * @param lineno
 * @return
 */
method* method_malloc(string_view namev, const char* filename, int lineno);
#define method_new(namev) (method_malloc(namev, __FILE__, __LINE__))

/**
 * メソッドを実行します.
 * @param self
 * @param frame
 * @param env
 */
void method_execute(method* self, struct frame* fr, struct enviroment* env);

/**
 * メソッドa とb が完全に等価である場合に true を返します.
 * もしくは戻り値がサブクラス型でオーバライドされている場合でも true です。
 * @see http://www.ne.jp/asahi/hishidama/home/tech/java/covariant.html
 * @param superM
 * @param subM
 * @param cctx
 * @return
 */
bool method_override(method* superM, method* subM, struct call_context* cctx);

/**
 * @param self
 * @param name
 * @return
 */
int method_for_generic_index(method* self, string_view namev);

/**
 * メソッドを開放します.
 * @param self
 */
void method_delete(method* self);

/**
 * このメソッドのマングル表現を返します.
 * @param self
 * @return
 */
string_view method_mangle(method* self);

/**
 * 型の完全名とマングル表現を連結して返します.
 * @param self
 * @return
 */
string_view method_unique(method* self);

/**
 * メソッドがコルーチンとして機能できるなら true.
 * @param self
 * @return
 */
bool method_coroutine(method* self);

/**
 * メソッドがイールドパターンで実装されているなら true.
 * @param self
 * @param error
 * @return
 */
bool method_yield(method* self, vector* stmt_list, bool* error);

/**
 * このメソッドのためのユニークなイテレータ型を作成します.
 * 戻り値が Iterator である必要があります。
 * @param self
 * @param cll
 * @param stmt_list
 * @return
 */
struct type* method_create_iterator_type(method* self, struct class_loader* cll, vector* stmt_list);

/**
 * @param abstract
 * @param concrete
 * @return
 */
struct generic_type* method_diff(method* abstract, method* concrete);

/**
 * メソッドのシグネチャのみを複製した新しいメソッドを作成します.
 * @param self
 * @return
 */
method* method_clone(method* self);
#endif // !SIGNAL_ENV_METHOD_H
