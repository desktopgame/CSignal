//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_class_impl.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_IL_IL_CLASS_H
#define BEACON_IL_IL_CLASS_H
#include "../../util/vector.h"
#include "../../util/string_pool.h"
#include "../../env/fqcn_cache.h"
#include "../il_type_interface.h"
#include <stdbool.h>
struct ILField;
struct ILMethod;
/**
 * クラスを表す要素.
 */
typedef struct ILClass {
	StringView Name;
	Vector* Extends;
	Vector* Fields;
	Vector* StaticFields;
	Vector* Methods;
	Vector* StaticMethods;
	Vector* Constructors;
	Vector* TypeParameters;
	Vector* OperatorOverloads;
	Vector* Properties;
	Vector* StaticProperties;
	bool IsAbstract;
} ILClass;

/**
 * この型をスーパーセットにラップします.
 * @param self
 * @return
 */
ILType* WrapILClass(ILClass* self);

/**
 * クラスを表す要素を作成します.
 * @param namev
 * @return
 */
ILClass* NewILClass(StringView namev);

/**
 * フィールドを追加します.
 * @param self
 * @param f
 */
void AddFieldILClass(ILClass* self, struct ILField* f);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void AddPropertyILClass(ILClass* self, struct ILProperty* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param m
 */
void AddMethodILClass(ILClass* self, struct ILMethod* m);

/**
 * クラスと含まれるメンバー宣言の一覧を解放します.
 * @param self
 */
void DeleteILClass(ILClass* self);
#endif // !SIGNAL_IL_IL_CLASS_H
