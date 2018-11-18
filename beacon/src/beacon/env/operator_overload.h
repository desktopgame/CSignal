//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file operator_overload.h
 * @brief オペレータオーバーロードを定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_ENV_OPERATOR_OVERLOAD_H
#define BEACON_ENV_OPERATOR_OVERLOAD_H
#include "../ast/operator_type.h"
#include "../util/vector.h"
#include "../ast/access_level.h"
struct Type;
struct Enviroment;
struct GenericType;
struct Frame;
/**
 * 演算子オーバーロードを表す構造体.
 */
typedef struct OperatorOverload {
	struct Type* Parent;
	struct GenericType* ReturnGType;
	bc_OperatorType Type;
	Vector* Parameters;
	struct Enviroment* Env;
	bc_AccessLevel Access;
} OperatorOverload;

/**
 * 新しい演算子オーバーロードを生成します.
 * @param type
 * @return
 */
OperatorOverload* NewOperatorOverload(bc_OperatorType type);

/**
 * 演算子オーバーロードを実行します.
 * @param self
 * @param fr
 * @param env
 */
void ExecuteOperatorOverload(OperatorOverload* self, struct Frame* fr, struct Enviroment* env);

/**
 * 演算子オーバーロードを解放します.
 * @param self
 */
void DeleteOperatorOverload(OperatorOverload* self);
#endif