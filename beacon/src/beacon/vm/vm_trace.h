#pragma once
#ifndef BEACON_VM_TRACE_H
#define BEACON_VM_TRACE_H
#include <stdint.h>
struct vm;
/**
 * 実行中のVMの実行位置を保存する構造体.
 */
typedef struct vm_trace {
	struct vm* v;
	int32_t pc;
	int32_t jump_level;
} vm_trace;

/**
 * 指定のVMでトレースを作成します.
 * @param v
 * @return
 */
vm_trace* vm_trace_new(struct vm* v);

/**
 * トレースを解放します.
 * @param self
 */
void vm_trace_delete(vm_trace* self);
#endif // !SIGNAL_VM_TRACE_H
