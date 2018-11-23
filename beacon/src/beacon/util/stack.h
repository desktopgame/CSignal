// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file stack.h
 * @brief スタックを定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_UTIL_STACK_H
#define BEACON_UTIL_STACK_H
#include <stdbool.h>

/**
 * スタックに格納出来るデータの型.
 */
typedef void* bc_StackItem;

/**
 * スタックを表す構造体.
 */
typedef struct bc_Stack {
        bc_StackItem Item;
        struct Stack_t* Prev;
        struct Stack_t* Next;
} bc_Stack;

/**
 * スタックのデリータ関数です.
 * @param item
 */
typedef void (*bc_StackElementDeleter)(bc_StackItem item);

/**
 * 新しいスタックを作成します.
 * @return
 */
bc_Stack* bc_NewStack();

/**
 * 末尾へ値を追加します.
 * @param self
 * @param item
 */
void bc_PushStack(bc_Stack* self, bc_StackItem item);

/**
 * 末尾の値を返しましす.
 * @param self
 * @return
 */
bc_StackItem bc_TopStack(bc_Stack* self);

/**
 * 末尾の値を返して削除します.
 * @param self
 * @return
 */
bc_StackItem bc_PopStack(bc_Stack* self);

/**
 * スタックが空なら true.
 * @param self
 * @return
 */
bool bc_IsEmptyStack(bc_Stack* self);

/**
 * スタックとその中身を開放します.
 * @param self
 * @param deleter
 */
void bc_DeleteStack(bc_Stack* self, bc_StackElementDeleter deleter);

/**
 * free によって解放するデリータです.
 * @param item
 */
void bc_StackDeleterByFree(bc_StackItem item);

/**
 * 何も行わないデリータです.
 * @param item
 */
void bc_StackDeleterOfNull(bc_StackItem item);
#endif  // !SIGNAL_UTIL_STACK_H
