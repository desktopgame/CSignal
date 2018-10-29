#pragma once
#ifndef BEACON_IL_IL_STMT_VARIABLE_INIT_H
#define BEACON_IL_IL_STMT_VARIABLE_INIT_H
#include "../../env/generic_cache.h"
#include "../../util/string_pool.h"
#include "../il_stmt_interface.h"
#include "../il_factor_interface.h"
struct Enviroment;
struct SymbolEntry;
/**
 * 変数の初期化を表す要素.
 */
typedef struct ILVariableInit {
	GenericCache* fqcn;
	StringView namev;
	ILFactor* fact;
	struct SymbolEntry* sym;
} ILVariableInit;

/**
 * 変数の初期化を表す要素をスーパーセットにラップします.
 * @param self
 * @return
 */
ILStatement* WrapILVariableInit(ILVariableInit* self);

/**
 * 変数の初期化を表す要素を作成します.
 * @param namev
 * @return
 */
ILVariableInit* NewILVariableInit(StringView namev);

/**
 * 変数の初期化を表す要素を出力します.
 * @param depth
 * @param env
 * @param ccctx
 */
void GenerateILVariableInit(ILVariableInit* self, Enviroment* env, CallContext* cctx);

/**
 * 変数の初期化を表す要素を読み込みます.
 * @param self
 * @param env
 * @param cctx
 */
void LoadILVariableInit(ILVariableInit* self, Enviroment* env, CallContext* cctx);

/**
 * 変数の初期化を表す要素を開放します.
 * @param self
 */
void DeleteILVariableInit(ILVariableInit* self);
#endif // !SIGNAL_IL_IL_STMT_VARIABLE_INIT_H
