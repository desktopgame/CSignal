//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file constructor.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_CONSTRUCTOR_H
#define BEACON_ENV_CONSTRUCTOR_H
#include "../ast/access_level.h"
#include "../util/vector.h"
struct Type;
struct Class;
struct Enviroment;
struct Object;
struct Frame;
/**
 * コンストラクタを表す構造体.
 */
typedef struct Constructor {
	struct Type* Parent;
	struct Enviroment* Env;
	Vector* Parameters;
	AccessLevel Access;
} Constructor;

/**
 * コンストラクタを作成します.
 * @return
 */
Constructor* NewConstructor();

/**
 * このコンストラクタを使用してオブジェクトを生成します.
 * @param self
 * @param args
 * @param parent
 * @return
 */
struct Object* NewInstanceConstructor(Constructor* self, Vector* args, struct Frame* parent);

/**
 * コンストラクタを開放します.
 * @param self
 */
void DeleteConstructor(Constructor* self);
#endif // !SIGNAL_ENV_CONSTRUCTOR_H
