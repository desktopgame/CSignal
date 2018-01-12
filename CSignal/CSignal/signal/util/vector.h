#pragma once
#ifndef SIGNAL_UTIL_VECTOR_H
#define SIGNAL_UTIL_VECTOR_H
#include <stdlib.h>

/**
 * ベクターの要素を表す型.
 */
typedef void* vector_item;

/**
 * 再帰を使用せずに実装された可変長配列です.
 * 0/NULLを格納することが出来ます。
 */
typedef struct vector {
	//使用されている長さ
	int length;
	//余分に確保された分も含めた長さ
	int capacity;
	//要素一つ分のサイズ
	//vector_slot_size_t slotSize;
	vector_item* memory;
} vector;

/**
 * ベクターのデリータ関数です.
 * @param item
 */
typedef void(*vector_element_deleter)(vector_item item);

/**
 * ベクターを作成します.
 * @return
 */
vector* vector_new();

/**
 * 末尾に要素を追加します.
 * @param self
 * @param item
 */
void vector_push(vector* self, vector_item item);

/**
 * 末尾の要素を削除せずに返します.
 * @param self
 * @return
 */
vector_item vector_top(vector* self);

/**
 * 末尾の要素を削除して返します.
 * @param self
 * @return
 */
vector_item vector_pop(vector* self);

/**
 * 指定位置に値を挿入します.
 * indexから末尾までの要素を一つ右にシフトします。
 * 次に index を item で上書きします。
 * @param self
 * @param index
 * @param item
 */
void vector_insert(vector* self, int index, vector_item item);

/**
 * 指定位置の要素を削除します.
 * @param self
 * @param index
 */
vector_item vector_remove(vector* self, int index);

/**
 * 容量を拡張します.
 * @param self
 * @return 新しいキャパシティサイズ
 */
int vector_reserve(vector* self);

/**
 * 指定位置の要素を上書きします.
 * 長さが足りない場合は 0 で伸ばします。
 * @param self
 * @param index
 * @param item
 */
void vector_assign(vector* self, int index, vector_item item);

/**
 * 指定位置の要素を返します.
 * @param self
 * @param index
 * @return
 */
vector_item vector_at(vector* self, int index);

/**
 * 中身を空にします.
 * @param self
 */
void vector_clear(vector* self);

/**
 * ベクターを開放します.
 * @param self
 * @param deleter
 */
void vector_delete(vector* self, vector_element_deleter deleter);

/**
 * free によって解放するデリータ.
 * @param item
 */
void vector_deleter_free(vector_item item);

/**
 * 何も行わないデリータ.
 * @param item
 */
void vector_deleter_null(vector_item item);
#endif // !SIGNAL_UTIL_VECTOR_H
