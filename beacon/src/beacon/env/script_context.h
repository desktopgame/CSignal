//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file script_context.h
 * @brief beaconの実行環境を定義します。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_ENV_SCRIPT_CONTEXT_H
#define BEACON_ENV_SCRIPT_CONTEXT_H
#include <stdbool.h>
#include "../util/stack.h"
#include "../util/tree_map.h"
#include "../util/vector.h"
#include "../util/numeric_map.h"
struct bc_Heap;
struct bc_Object;
struct bc_ClassLoader;
struct bc_Field;

/**
 * 静的フィールドを訪問するための関数ポインタ.
 * @param item
 */
typedef void(*bc_StaticEach)(struct bc_Field* item);

/**
 * beacon言語のあらゆるオブジェクトのトップレベル.
 * ホスト言語から異なる環境のスクリプトを実行するためにこの方法を使用します。
 */
typedef struct bc_ScriptContext {
	bc_NumericMap* NamespaceMap;
	bc_TreeMap* ClassLoaderMap;
	bc_Vector* ThreadList;
	bc_Vector* IncludeList;
	struct bc_ClassLoader* BootstrapClassLoader;
	//通し番号でクラスを参照するためのベクター
	bc_Vector* TypeList;
	bc_Vector* AllGenericList;
	//整数のキャッシュ
	bc_Vector* PositiveIntegerCacheList;
	bc_Vector* NegativeIntegerCacheList;
	bc_NumericMap* IntegerCacheMap;
	bool IsPrintError;
	bool IsAbortOnError;
	struct bc_Heap* Heap;
	struct bc_Object* True;
	struct bc_Object* False;
	struct bc_Object* Null;
} bc_ScriptContext;

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストを作成します.
 * このとき現在のコンテキストは上書きされます。
 * 既に作成されている場合は何もしません。
 * @return
 */
bc_ScriptContext* bc_OpenScriptContext();

/**
 * 現在のスクリプトコンテキストを返します.
 * この呼び出しは同期される必要があります。
 * @return
 */
bc_ScriptContext* bc_GetCurrentScriptContext();

/**
 * スクリプトコンテキストを登録するためのスクリプトコンテキストと、
 * そこから参照可能な全てのスクリプトコンテキストを開放します.
 */
void bc_CloseScriptContext();

/**
 * まだブートストラップクラスローダが起動していないなら起動します.
 * @param self
 */
void bc_BootstrapScriptContext(bc_ScriptContext* self);

/**
 * 全ての静的フィールドを訪問します.
 * @param self
 * @param act
 */
void bc_EachStaticScriptContext(bc_ScriptContext* self, bc_StaticEach act);

/**
 * 全ての静的フィールドをクリアします.
 * 一つのコンテキストで複数回プログラムを実行する場合には、
 * これを呼び出す必要がある...場合もあります。
 * 一つのコンテキストで複数回実行するということは、
 * その回数分エントリポイントの定数プールも作成/破棄されることになります。
 * 静的フィールドが定数プールの値を参照したまま実行を終了した場合、
 * 次の実行でそのポインタがGCによってマークされることになります。
 * これはすでに解放されたポインタへのアクセスになってしまいます。
 * なので、複数回実行する場合にはこれを使用して静的フィールドをクリアします。
 * @param self
 */
void bc_ClearScriptContext(bc_ScriptContext* self);

/**
 * 指定の整数をキャッシュします.
 * @param self
 * @param i
 * @return
 */
struct bc_Object* bc_IInternScriptContext(bc_ScriptContext* self, int i);

/**
 * 現在のコンテキストでリテラルをキャッシュします.
 */
void bc_CacheScriptContext();
#endif // !SIGNAL_ENV_SCRIPT_CONTEXT_H
