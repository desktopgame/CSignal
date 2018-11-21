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
struct bc_ILField;
struct bc_ILMethod;
/**
 * クラスを表す要素.
 */
typedef struct bc_ILClass {
	bc_StringView Name;
	bc_Vector* Extends;
	bc_Vector* Fields;
	bc_Vector* StaticFields;
	bc_Vector* Methods;
	bc_Vector* StaticMethods;
	bc_Vector* Constructors;
	bc_Vector* TypeParameters;
	bc_Vector* OperatorOverloads;
	bc_Vector* Properties;
	bc_Vector* StaticProperties;
	bool IsAbstract;
} bc_ILClass;

/**
 * この型をスーパーセットにラップします.
 * @param self
 * @return
 */
bc_ILType* bc_WrapILClass(bc_ILClass* self);

/**
 * クラスを表す要素を作成します.
 * @param namev
 * @return
 */
bc_ILClass* bc_NewILClass(bc_StringView namev);

/**
 * フィールドを追加します.
 * @param self
 * @param f
 */
void bc_AddFieldILClass(bc_ILClass* self, struct bc_ILField* f);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void bc_AddPropertyILClass(bc_ILClass* self, struct bc_ILProperty* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param m
 */
void bc_AddMethodILClass(bc_ILClass* self, struct bc_ILMethod* m);

/**
 * クラスと含まれるメンバー宣言の一覧を解放します.
 * @param self
 */
void bc_DeleteILClass(bc_ILClass* self);
#endif // !SIGNAL_IL_IL_CLASS_H
