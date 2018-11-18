//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file il_constructor_chain.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_IL_IL_CONSTRUCTOR_CHAIN_H
#define BEACON_IL_IL_CONSTRUCTOR_CHAIN_H
#include "../util/vector.h"
#include "../ast/constructor_chain_type.h"
struct Constructor;
/**
 * コンストラクタの連鎖を表す要素.
 */
typedef struct ILConstructorChain {
	bc_ConstructorChainType Type;
	Vector* Arguments;
	struct Constructor* Constructor;
	int ConstructorIndex;
} ILConstructorChain;
/**
 * コンストラクタの連鎖を表す要素を作成します.
 * @return
 */
ILConstructorChain* NewILConstructorChain();

/**
 * コンストラクタの連鎖を表す要素を開放します.
 * @param self
 */
void DeleteILConstructorChain(ILConstructorChain* self);
#endif // !SIGNAL_IL_IL_CONSTRUCTOR_CHAIN_H
