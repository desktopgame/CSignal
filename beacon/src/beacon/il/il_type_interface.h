//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_type_interface.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_TYPE_INTERFACE_H
#define BEACON_IL_IL_TYPE_INTERFACE_H
#include "../util/vector.h"
/**
 * 型の種類を判別する列挙.
 */
typedef enum bc_ILTypeTag {
	ILTYPE_CLASS_T,
	ILTYPE_INTERFACE_T,
	ILTYPE_ENUM_T,
} bc_ILTypeTag;

struct bc_ILClass;
struct bc_ILInterface;
struct bc_ILEnum;
struct bc_ILField;
struct bc_ILMethod;
struct bc_ILProperty;
struct bc_ILConstructor;

/**
 * 名前空間に含めることが出来る型.
 */
typedef struct bc_ILType {
	bc_ILTypeTag Tag;
	union {
		struct bc_ILClass* Class;
		struct bc_ILInterface* Interface;
		struct bc_ILEnum* Enum;
	} Kind;
} bc_ILType;

/**
 * 型を作成します.
 * @return
 */
bc_ILType* bc_NewILType();

/**
 * メソッドの一覧を返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetMethodsILType(bc_ILType* self);

/**
 * 静的メソッドの一覧を返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetSMethodsILType(bc_ILType* self);

/**
 * コンストラクタを追加します.
 * @param self
 * @param ctor
 */
void bc_AddConstructorILType(bc_ILType* self, struct bc_ILConstructor* ctor);

/**
 * フィールドを追加します.
 * @param self
 * @param field
 */
void bc_AddFieldILType(bc_ILType* self, struct bc_ILField* field);

/**
 * プロパティを追加します.
 * @param self
 * @param prop
 */
void bc_AddPropertyILType(bc_ILType* self, struct bc_ILProperty* prop);

/**
 * メソッドを追加します.
 * @param self
 * @param field
 */
void bc_AddMethodILType(bc_ILType* self, struct bc_ILMethod* method);

/**
 * 型を開放します.
 * @param self
 */
void bc_DeleteILType(bc_ILType* self);

/**
 * 型変数の一覧を返します.
 * @param self
 * @return
 */
bc_Vector* bc_GetTypeParametersILType(bc_ILType* self);
#endif // !SIGNAL_IL_IL_TYPE_INTERFACE_H
