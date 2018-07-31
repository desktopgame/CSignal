#ifndef BEACON_TYPE_FIND_H
#define BEACON_TYPE_FIND_H
#include "../../util/string_pool.h"
#include "class_impl.h"
/**
 * 指定の名前を持つフィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_field(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つフィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param domain
 * @param outIndex
 * @return
 */
struct field* class_find_field_tree(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield(class_* self, string_view namev, int* outIndex);

/**
 * 指定の名前を持つ静的フィールドを返します.
 * selfの中に見つけられなかった場合には親クラスも検索します。
 * @param self
 * @param namev
 * @param outIndex
 * @return 無ければ NULL
 */
struct field* class_find_sfield_tree(class_* self, string_view namev, int* outIndex);

/**
 * 指定位置のフィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* class_get_field(class_* self, int index);

/**
 * 指定位置の静的フィールドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのフィールドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct field* class_get_sfield(class_* self, int index);





/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<object*> 呼び出し側で開放してください.
 * @param typeargs
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* class_rfind_constructor(class_* self, vector* args, vector* typeargs, frame* fr, int* outIndex);

/**
 * もっとも一致するコンストラクタを返します.
 * @param self
 * @param args<il_argument*> 呼び出し側で開放してください.
 * @param env
 * @param cctx
 * @param outIndex
 * @return 無ければ空
 */
struct constructor* class_ilfind_constructor(class_* self, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * 引数が一つもないコンストラクタを検索して返します.
 * @param self
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct constructor* class_ilfind_empty_constructor(class_* self, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param env
 * @param cctx
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_ilfind_method(class_* self, string_view namev, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致するメソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* class_gfind_method(class_* self, string_view namev, vector* gargs, int* outIndex);

/**
 * equalsメソッドを検索します.
 * @param self
 * @param outIndex
 * @return
 */
struct method* class_gfind_eqmethod(class_* self, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param env
 * @param cctx
 * @param args<il_argument*>
 * @param outIndex メソッドへのインデックス
 * @return
 */
struct method* class_ilfind_smethod(class_* self, string_view namev, vector* args, enviroment* env, call_context* cctx, int* outIndex);

/**
 * もっとも一致する静的メソッドを返します.
 * @param self
 * @param namev
 * @param gargs
 * @param outIndex
 * @return
 */
struct method* class_gfind_smethod(class_* self, string_view namev, vector* gargs, int* outIndex);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param o
 * @param index
 * @return
 */
struct method* class_get_method(struct object* o, int index);

/**
 * 指定位置のメソッドを返します.
 * このクラスの上や下も含めて検索します。
 * つまりこの index は self の最上位クラスから self までに現れる全てのメソッドの通し番号です。
 * @param self
 * @param index
 * @return
 */
struct method* class_get_smethod(class_* self, int index);

/**
 * selfから、 interTypeの仮想関数テーブルの interIndex番目に属するメソッド
 * を実装するために定義されたメソッドを検索して返します。
 * @param self
 * @param interType
 * @param interIndex
 * @return
 */
struct method* class_get_impl_method(class_* self, type* interType, int interMIndex);




/**
 * @param self
 * @param type
 * @param args
 * @param env
 * @param outIndex
 * @return
 */
struct operator_overload* class_find_operator_overload(class_* self, operator_type type, vector* args, enviroment* env, int* outIndex);

/**
 * @param self
 * @param index
 * @return
 */
struct operator_overload* class_get_operator_overload(class_* self, int index);

/**
 * 指定のクラスから Object クラスまでのいずれかの階層に m が含まれるなら true.
 * @param self
 * @param m
 * @return
 */
bool class_contains_method_tree(class_* self, method* m);

/**
 * 指定のメソッド一覧に指定のメソッドが含まれるなら true.
 * 静的メソッドの場合はエラーを発生させます。
 * @param method_list
 * @param m
 */
bool class_contains_method(vector* method_list, method* m);
#endif