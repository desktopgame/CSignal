// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file heap.h
 * @brief オブジェクトを格納するヒープです。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_HEAP_H
#define BEACON_ENV_HEAP_H
#include <stdbool.h>
#include "../util/vector.h"
#include "object.h"

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct bc_Heap {
        bc_Vector* Objects;
        //この値が 1以上 なら、新しく確保されたオブジェクトは
        //ヒープに関連づけられません。
        //つまり、オブジェクトを自分で解放する必要があります。
        //これはリテラルのための機構です。
        int AcceptBlocking;
        //この値が 1以上 なら、新しくオブジェクトを確保した時に
        //オブジェクトの総数が閾値を上回っていてもGCを施工しません。
        int CollectBlocking;
} bc_Heap;

/**
 * ヒープを作成します.
 * @return
 */
bc_Heap* bc_NewHeap();

/**
 * 現在のスクリプトコンテキストでヒープを返します.
 * @return
 */
bc_Heap* bc_GetHeap();

/**
 * ヒープにオブジェクトを追加します.
 * obj#blockingがtrueなら、
 * 追加せずに obj#paint を PAINT_ONEXIT_T へ変更します。
 * @param self
 * @param obj
 */
void bc_AddHeap(bc_Heap* self, bc_Object* obj);

/**
 * GCを実行します.
 * @param self
 */
void bc_CollectHeap(bc_Heap* self);

/**
 * 指定のオブジェクトをヒープから取り除きます.
 * @param self
 * @param o
 */
void bc_IgnoreHeap(bc_Heap* self, bc_Object* o);

/**
 * ヒープを開放します.
 * @param self
 */
void bc_DeleteHeap(bc_Heap* self);

/**
 * ヒープの中身をダンプします.
 * @param self
 */
void bc_DumpHeap(bc_Heap* self);
#endif  // !SIGNAL_ENV_HEAP_H
