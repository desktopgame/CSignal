//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file defer_context.h
 * @brief deferが実行された時点でのコンテキストを保存するオブジェクトを定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_VM_DEFER_CONTEXT_H
#define BEACON_VM_DEFER_CONTEXT_H
#include "label.h"
#include "../util/vector.h"
/**
 * deferステートメントが実行された時、
 * その時点でのpcと名前束縛を記録しておく構造体です.
 */
typedef struct bc_DeferContext {
	bc_Label* Offset;
	bc_Vector* VariableTable;
} bc_DeferContext;

/**
 * 新しい DeferContext を作成します.
 * @return
 */
bc_DeferContext* bc_NewDeferContext();

/**
 * DeferContext を解放します.
 * @param self
 */
void bc_DeleteDeferContext(bc_DeferContext* self);
#endif