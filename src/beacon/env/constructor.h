// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file constructor.h
 * @brief コンストラクタを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_CONSTRUCTOR_H
#define BEACON_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
#include "member.h"
struct bc_Type;
struct bc_Class;
struct bc_Enviroment;
struct bc_Object;
struct bc_Frame;
/**
 * コンストラクタを表す構造体.
 */
typedef struct bc_Constructor {
        bc_Member Super;
        struct bc_Enviroment* Env;
        bc_Vector* Parameters;
} bc_Constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
bc_Constructor* bc_NewConstructor();

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct bc_Object* bc_NewInstanceConstructor(bc_Constructor* self,
                                            bc_Vector* args,
                                            struct bc_Frame* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void bc_DeleteConstructor(bc_Constructor* self);
#endif  // !SIGNAL_ENV_CONSTRUCTOR_H