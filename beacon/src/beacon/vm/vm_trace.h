#pragma once
#ifndef BEACON_VM_TRACE_H
#define BEACON_VM_TRACE_H
#include <stdint.h>
struct frame;
/**
 * 実行中のVMの実行位置を保存する構造体.
 */
typedef struct VMTrace {
	struct frame* SnapShot;
	int PC;
	int JumpLevel;
} VMTrace;

/**
 * 指定のVMでトレースを作成します.
 * @param v
 * @return
 */
VMTrace* NewVMTrace(struct frame* snapShot);

/**
 * トレースを解放します.
 * @param self
 */
void DeleteVMTrace(VMTrace* self);
#endif // !SIGNAL_VM_TRACE_H
