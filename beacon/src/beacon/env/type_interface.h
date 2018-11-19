//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file type_interface.h
 * @brief クラスやインターフェイスなどの共通部分を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_TYPE_INTERFACE_H
#define BEACON_ENV_TYPE_INTERFACE_H
#include <stdbool.h>
#include <stdlib.h>
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "../il/call_context.h"

#define BC_TYPE2CLASS(type) (bc_CastClassType(type))
#define BC_TYPE2INTERFACE(type) (bc_CastInterfaceType(type))
/**
 * 型の種類を表すタグ.
 */
typedef enum bc_TypeTag {
	TYPE_CLASS_T,
	TYPE_INTERFACE_T,
	TYPE_ENUM_T
} bc_TypeTag;

struct bc_Namespace;
struct Class;
struct Interface;
struct bc_Field;
struct bc_Method;
struct bc_Property;
struct Enviroment;
struct bc_VTable;
struct bc_GenericType;

typedef enum bc_TypeState {
	/**
	 * 生成直後.
	 */
	TYPE_NONE = 1 << 0,
	/**
	 * 言語仕様のためにプリロードされるクラス.
	 * 後で正式に読み込まれるまで "保留" 状態とします。
	 */
	TYPE_PENDING = 1 << 1,
	/**
	 * 型宣言を発見し、名前空間へ登録されたことを示します.
	 */
	TYPE_REGISTER = 1 << 2,
	/**
	 * ある型のメンバ宣言を読み込んだことを示します.
	 */
	TYPE_DECL = 1 << 3,
	/**
	 * ある型のメンバ実装を読み込んだことを示します.
	 */
	TYPE_IMPL = 1 << 4
} bc_TypeState;

/**
 * 型を表す構造体.
 */
typedef struct bc_Type {
	bc_TypeTag Tag;
	struct bc_Namespace* Location;
	struct bc_GenericType* GenericSelf;
	int AbsoluteIndex;
	bc_TypeState State;
	size_t AllocSize;
	union {
		struct Class* Class;
		struct Interface* Interface;
	} Kind;
} bc_Type;

/**
 * 型を作成します.
 * @return
 */
bc_Type* bc_NewType();

/**
 * このタイプ自体を表すジェネリック型を初期化します.
 * @param self
 * @param count 型変数の個数
 * @return
 */
struct bc_GenericType* bc_InitGenericSelf(bc_Type* self, int counts);

/**
 * この型の名前を返します.
 * @param self
 * @return
 */
StringView bc_GetTypeName(bc_Type* self);

/**
 * この型の完全な名前を返します.
 * @param self
 * @return
 */
StringView bc_GetTypeFullName(bc_Type* self);

/**
 * この型にフィールドを追加します.
 * @param self
 * @param f
 */
void bc_AddFieldType(bc_Type* self, struct bc_Field* f);

/**
 * この型にプロパティを追加します.
 * @param self
 * @param p
 */
void bc_AddPropertyType(bc_Type* self, struct bc_Property* p);

/**
 * この型にメソッドを追加します.
 * @param self
 * @param m
 */
void bc_AddMethodType(bc_Type* self, struct bc_Method* m);

/**
 * この型からメソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct bc_Method* bc_ILFindMethodType(bc_Type* self, StringView namev, Vector* args, struct Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * この型から静的メソッドを検索します.
 * @param self
 * @param namev
 * @param args
 * @param env
 * @param cctx
 * @param outIndex
 * @return
 */
struct bc_Method* bc_ILFindSMethodType(bc_Type* self, StringView namev, Vector* args, struct Enviroment* env, CallContext* cctx, int* outIndex);

/**
 * 仮想関数の一覧を返します.
 * @param self
 * @return
 */
struct bc_VTable* bc_GetVTableType(bc_Type* self);

/**
 * 型の距離を返します.
 * @param super
 * @param sub
 * @return
 */
int bc_DistanceType(bc_Type* super, bc_Type* sub);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void bc_UnlinkType(bc_Type* self);

/**
 * 指定の名前の型変数が何番目に表れるかを返します.
 * @param self
 * @param namev
 * @return
 */
int bc_GetGenericIndexType(bc_Type* self, StringView namev);

/**
 * selfの継承クラスや実装インターフェイスに a が現れるなら型変数付きで返します.
 * 例えば
 *
 * class IntList : List<Int>
 * を表すクラスに List<T> を渡すと List<Int> が返ります。
 * @param self
 * @param a
 * @return
 */
struct bc_GenericType* bc_FindImplementType(bc_Type* self, bc_Type* a);

/**
 * この型の型引数の一覧を返します.
 * @param self
 * @return
 */
Vector* bc_GetParameterListType(bc_Type* self);

/**
 * この型の実装インターフェイスの一覧を返します.
 * @param self
 * @return
 */
Vector* bc_GetImplementList(bc_Type* self);

/**
 * この型がクラス/インターフェイスを表すとき、
 * 指定位置の型変数を返します.
 * @param self
 * @param index
 * @return
 */
struct bc_GenericType* bc_TypeParameterAtType(bc_Type* self, int index);

/**
 * 型を開放します.
 * @param self
 */
void bc_DeleteType(bc_Type* self);

/**
 * このタイプをクラスにキャストします.
 * @param self
 * @return
 */
struct Class* bc_CastClassType(bc_Type* self);
/**
 * このタイプをインターフェイスにキャストします.
 * @param self
 * @return
 */
struct Interface* bc_CastInterfaceType(bc_Type* self);

/**
 * abstractにはクラス/インターフェイスを渡します.
 * concreteの親クラス/実装インターフェイス一覧から abstract を検索し、 GenericType で返します。
 * @param abstract
 * @param concrete
 * @return
 */
struct bc_GenericType* bc_BaselineType(bc_Type* abstract, bc_Type* concrete);

/**
 * 同じインターフェイスが二回現れるなら NULL 以外.
 * @param self
 * @return
 */
struct Interface* bc_IsValidInterface(bc_Type* self);

/**
 * 抽象クラスかインターフェイスなら true.
 * @param self
 * @return
 */
bool bc_IsAbstractType(bc_Type* self);

/**
 * 可能なら self を class へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct Class* bc_TypeToClass(bc_Type* self);
/**
 * 可能なら self を interface へ変換します.
 * 失敗したなら NULL
 * @param self
 * @return
 */
struct Interface* bc_TypeToInterface(bc_Type* self);
#endif // !SIGNAL_ENV_TYPE_INTERFACE_H
