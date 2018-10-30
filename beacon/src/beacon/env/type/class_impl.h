//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file class_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_CLASS_H
#define BEACON_ENV_CLASS_H
#include "../namespace.h"
#include "../native_method_ref.h"
#include "../vtable.h"
#include "../type_interface.h"
#include "../../ast/operator_type.h"
#include "../../vm/enviroment.h"
#include "../../util/vector.h"
#include "../../il/call_context.h"
#include "../../util/numeric_map.h"
#include "../../util/string_pool.h"
#include "../operator_vt.h"
#include "class_validate.h"
//#include "../access_domain.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
//struct field_list;
//struct method_list;
struct Object;
struct Field;
struct Property;
struct PropertyBody;
struct Method;
struct Constructor;
struct GenericType;
struct OperatorOverload;
/**
 * クラスを表す構造体です.
 */
typedef struct Class {
	Type* Parent;
	StringView Name;
	Namespace* Location;
	struct GenericType* SuperClass;
	Vector* Implements;
	Vector* Fields;
	Vector* StaticFields;
	Vector* Properties;
	Vector* StaticProperties;
	Vector* Methods;
	Vector* StaticMethods;
	Vector* Constructors;
	Vector* OperatorOverloads;
	//class_type type;
	uint32_t RefCount;
	NumericMap* NativeMethodRefMap;
	Vector* TypeParameters;
	//インターフェースに対応した
	//実装メソッドのテーブルのベクター
	//http://d.hatena.ne.jp/tetz42/20120205/1328449750
	Vector* VTTable;
	//Vector* static_fieldval_vec;
	VTable* VT;
	OperatorVT* OVT;
	bool IsAbstract;
} Class;
#include "class_find.h"

/**
 * クラスをスーパーセットにラップします.
 * @param self
 * @return
 */
Type* WrapClass(Class* self);

/**
 * 新しいクラスを作成します.
 * 呼び出し側で対応する名前空間を紐づけてください。
 * @param namev
 * @return
 */
Class* NewClass(StringView namev);

/**
 * 指定のインターフェイスを実装するクラスを作成します.
 * @param gt
 * @param namev
 * @return
 */
Class* NewClassProxy(struct GenericType* gt, StringView namev);

/**
 * 事前に読みこまれる必要があるクラスを作成します.
 * @param namev
 */
Type* NewPreloadClass(StringView namev);

/**
 * 指定のオブジェクトにこのクラスのフィールドを表す
 * オブジェクトの一覧を追加します。
 * この関数は親クラスから順番に呼び出してください。
 * 以下の副作用をもたらします。
 * - o->classz は self で上書きされます。
 * - o->vptr は self->vt で上書きされます。
 * @param self
 * @param o
 * @param fr
 */
void AllocFieldsClass(Class* self, struct Object* o, Frame* fr);

/**
 * 指定のオブジェクトに追加されたフィールドの一覧を開放します.
 * このメソッドは子クラスから順番に呼び出してください。
 * @param self
 * @param o
 */
void FreeClassFields(Class* self, struct Object* o);

/**
 * このクラスにフィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldClass(Class* self, struct Field* f);

/**
 * このクラスにプロパティを追加します.
 * @param self
 * @param p
 */
void AddPropertyClass(Class* self, struct Property* p);

/**
 * このクラスにメソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodClass(Class* self, struct Method* m);

/**
 * このクラスにコンストラクタを追加します.
 * @param self
 * @param c
 */
void AddConstructorClass(Class* self, struct Constructor* c);

/**
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param name
 * @param impl
 */
void DefineNativeMethodClass(Class* self, const char* name, NativeImpl impl);

/**
 * 指定の名前に対応するネイティブ関数を登録します.
 * @param self
 * @param namev
 * @param impl
 */
void DefineNativeMethodByRefClass(Class* self, StringView namev, NativeImpl impl);

/**
 * super と sub の距離を返します.
 * @param super
 * @param sub
 * @return 同じクラスなら 0
 *         otherがselfのサブクラスなら正の数(階層の深さ)
 *         継承関係が異なるなら -1
 */
int DistanceClass(Class* super, Class* sub);

/**
 * このクラスの VTable を、現在のメソッド一覧に基づいて作成します.
 * このメソッドが呼び出されるまでメンバの vt は NULL です。
 * また、この関数は全てのメソッドが登録されてから呼び出してさい。
 * @param self
 */
void CreateVTableClass(Class* self);
/**
 * このクラスの operator_Vt を、現在のメソッド一覧に基づいて作成します.
 * @param self
 */
void CreateOperatorVTClass(Class* self);

/**
 * このクラスとその親全てに定義されたフィールドの合計を返します.
 * @param self
 * @return
 */
int CountAllFieldClass(Class* self);

/**
 * このクラスとその親全てに定義された静的フィールドの合計を返します.
 * @param self
 * @return
 */
int CountAllSFieldClass(Class* self);

/**
 * このクラスとその親全てに定義されたプロパティの合計を返します.
 * @return
 */
int CountAllPropertyClass(Class* self);

/**
 * このクラスとその親全てに定義された静的プロパティの合計を返します.
 * @param self
 * @return
 */
int CountAllSPropertyClass(Class* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int CountAllMethodClass(Class* self);

/**
 * このクラスとその親全てに定義されたメソッドの合計を返します.
 * @param self
 * @return
 */
int CountAllSMethodClass(Class* self);

/**
 * @param self
 * @param ilctx
 * @param fr
 * @param count
 * @param args
 * @param type_args
 * @return
 */
struct Object* NewInstanceClass(Class* self, Frame* fr, Vector* args, Vector* type_args);

/**
 * 全てのメンバーがこのクラスを参照できるようにします.
 * @param self
 */
void LinkAllClass(Class* self);

/**
 * 型情報を残してメソッドやフィールドなどのみを開放します.
 * @param self
 */
void UnlinkClass(Class* self);

/**
 * このクラスを開放します.
 * ただし先にこのクラスを参照するサブクラスを開放する必要があります。
 * @param self
 */
void DeleteClass(Class* self);
#endif // !SIGNAL_ENV_CLASS_H
