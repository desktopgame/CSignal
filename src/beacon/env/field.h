// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file field.h
 * @brief フィールドを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_FIELD_H
#define BEACON_ENV_FIELD_H
#include "../ast/access_level.h"
#include "../ast/modifier_type.h"
#include "../util/string_pool.h"
#include "member.h"
//#include "virtual_type.h"
struct bc_Type;
struct bc_GenericType;
struct bc_Object;
struct bc_Enviroment;
struct bc_ILFactor;
/**
 * フィールドを表す構造体.
 */
typedef struct bc_Field {
        bc_Member Super;
        bc_StringView Name;
        struct bc_GenericType* GType;
        struct bc_Object* StaticValue;
        struct bc_ILFactor* InitialValue;
        struct bc_Enviroment* InitialValueEnv;
        bool IsNotInitializedAtCtor;
} bc_Field;

/**
 * 新しいフィールドを作成します.
 * @param namev
 * @return
 */
bc_Field* bc_NewField(bc_StringView namev);

/**
 * フィールドを開放します.
 * @param self
 */
void bc_DeleteField(bc_Field* self);
#endif  // !SIGNAL_ENV_FIELD_H