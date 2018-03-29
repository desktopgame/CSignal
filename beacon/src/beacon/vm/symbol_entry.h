#pragma once
#ifndef BEACON_VM_SYMBOL_ENTRY_H
#define BEACON_VM_SYMBOL_ENTRY_H
//#include "../env/class.h"
struct generic_type;
/**
 * シンボルを表す構造体.
 */
typedef struct symbol_entry {
	int index;
	struct generic_type* gtype;
} symbol_entry;

/**
 * エントリを作成します.
 * @param name
 * @return
 */
symbol_entry* symbol_entry_new(const char* name);

/**
 * エントリを開放します.
 * @param self
 */
void symbol_entry_delete(symbol_entry* self);
#endif // !SIGNAL_VM_SYMBOL_ENTRY_H
