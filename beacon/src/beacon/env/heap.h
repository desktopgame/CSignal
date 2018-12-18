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
#include "../util/cache.h"
#include "../util/vector.h"
#include "object.h"

/**
 * オブジェクトの一覧を格納します.
 */
typedef struct bc_Heap {
        bc_Cache* Objects;
        bc_Cache* Roots;
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
 * ヒープを初期化します。
 */
void bc_InitHeap();

/**
 * ヒープを破棄します。
 */
void bc_DestroyHeap();

/**
 * 現在のスクリプトコンテキストでヒープを返します.
 * @return
 */
bc_Heap* bc_GetHeap();

/**
 * ヒープにオブジェクトを追加します.
 * obj#blockingがtrueなら、
 * 追加せずに obj#paint を PAINT_ONEXIT_T へ変更します。
 * @param obj
 */
void bc_AddHeap(bc_Object* obj);

/**
 * ルートの一覧に obj を追加します。
 * @param obj
 */
void bc_AddRoot(bc_Object* obj);

/**
 * 指定のオブジェクトをヒープから取り除きます.
 * @param o
 */
void bc_IgnoreHeap(bc_Object* o);

/**
 * ヒープの中身をダンプします.
 */
void bc_DumpHeap();

/**
 * GCが完全に実行されるまでウェイトします。
 */
void bc_WaitFullGC();

/**
 * STWが要求されているならウェイトします。
 */
void bc_CheckSTWRequest();
#endif  // !SIGNAL_ENV_HEAP_H
