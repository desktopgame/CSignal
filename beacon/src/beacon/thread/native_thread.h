// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file native_thread.h
 * @brief OS固有スレッドのラッパーです。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_THREAD_NATIVE_THREAD_H
#define BEACON_THREAD_NATIVE_THREAD_H
#include <setjmp.h>

#if __APPLE__
#include <pthread.h>
#include <unistd.h>
typedef void* bc_ThreadStartArgument;
#define bc_NativeMutex pthread_mutex_t
typedef void* (*bc_Runnable)(bc_ThreadStartArgument a);
#define USE_PTHREAD
#elif defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
typedef void* bc_ThreadStartArgument;
typedef int bc_NativeMutex;
typedef void (*bc_Runnable)(bc_ThreadStartArgument a);
#define USE_WINTHREAD
#else
"unsupported your operating system."
#endif

/**
 * OSに組み込まれたスレッド機能を使用するためのラッパーです。
 * この構造体は Mac/pthread, Windows/Thread
 * の両方で動作するように定義されています。
 */
typedef struct bc_NativeThread {
#if defined(USE_PTHREAD)
        pthread_t t;
#elif defined(USE_WINTHREAD)

#endif
        jmp_buf Context;
        bc_Runnable Runnable;
        bc_ThreadStartArgument Arg;
        int Index;
} bc_NativeThread;

/**
 * NativeThreadシステムを初期化します。
 */
void bc_InitNativeThread();

/**
 * 新しいスレッドのための領域を確保します。
 * @param runnable
 * @param arg
 * @return
 */
bc_NativeThread* bc_AllocNativeThread(bc_Runnable runnable,
                                      bc_ThreadStartArgument arg);

/**
 * 新しいスレッドを作成して開始します。
 * 必ず DetachNativeThread によって終了する必要があります。
 * @param runnable
 * @param arg
 * @param outNativeThread
 * @return エラーコード
 */
int bc_StartNativeThread(bc_Runnable runnable, bc_ThreadStartArgument arg,
                         bc_NativeThread** outNativeThread);

/**
 * 指定のミューテックスを初期化します。
 * @param mtx
 */
void bc_InitNativeMutex(bc_NativeMutex* mtx);

/**
 * 現在のコンテキストでモニターをロックします。
 * 他のスレッドは実行中のコンテキストの直前で待機します。
 * @param mtx
 */
void bc_NativeMutexEnter(bc_NativeMutex* mtx);

/**
 * ロックを解放します。
 * 他のスレッドは実行中のコンテキストを開始できます。
 * @param mtx
 */
void bc_NativeMutexExit(bc_NativeMutex* mtx);

/**
 * ミューテックスを解放します。
 * @param mtx
 */
void bc_DestroyNativeMutex(bc_NativeMutex* mtx);

/**
 * 実行中のスレッドで指定の秒数だけ待機します。
 * @param seconds
 * @return 正常に完了したなら 0 を返す
 */
unsigned int bc_NativeSleep(unsigned int seconds);

/**
 * スレッドが終了するまで現在のコンテキストで待機します。
 * @param self
 */
void bc_JoinNativeThread(bc_NativeThread* self);

/**
 * スレッドと関連するリソースを全て解放します。
 * @param self
 */
void bc_DetachNativeThread(bc_NativeThread** self);

/**
 * 実行中のスレッドのうち、指定位置のスレッドを返します。
 * デタッチされたスレッドは取得できません。
 * @param index
 * @return
 */
bc_NativeThread* bc_GetNativeThreadAt(int index);

/**
 * 最初に起動したスレッドを返します。
 * @return
 */
bc_NativeThread* bc_GetMainThread();

/**
 * このメソッドを実行している時のスレッドを返します。
 * @return
 */
bc_NativeThread* bc_GetActiveThread();

/**
 * 実行中のスレッドの数を返します。
 * @return
 */
int bc_GetNativeThreadCount();

/**
 * NativeThreadシステムを終了します。
 */
void bc_DestroyNativeThread();
#endif