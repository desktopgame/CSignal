#pragma once
#ifndef BEACON_UTIL_VECTOR_H
#define BEACON_UTIL_VECTOR_H
#include <stdlib.h>
#include <stdbool.h>

/**
 * ベクターの要素を表す型.
 */
typedef void* VectorItem;

/**
 * 再帰を使用せずに実装された可変長配列です.
 * 0/NULLを格納することが出来ます。
 */
typedef struct Vector_t {
	//使用されている長さ
	int Length;
	//余分に確保された分も含めた長さ
	int Capacity;
	//要素一つ分のサイズ
	//vector_slot_size_t slotSize;
	VectorItem* Memory;
} Vector;

/**
 * ベクターのデリータ関数です.
 * @param item
 */
typedef void(*VectorElementDeleter)(VectorItem item);

typedef void(*VectorAction)(VectorItem item);

/**
 * ベクターを作成します.
 */
#define NewVector() (MallocVector(__FILE__, __LINE__))

/**
 * ベクターを作成します.
 * @param filename
 * @param lineno
 */
Vector* MallocVector(const char* filename, int lineno);

/**
 * 末尾に要素を追加します.
 * @param self
 * @param item
 */
void PushVector(Vector* self, VectorItem item);

/**
 * selfが空なら新規作成して返します.
 * @param self
 * @param item
 * @return
 */
Vector* AppendVector(Vector* self, VectorItem item);

/**
 * 末尾の要素を削除せずに返します.
 * @param self
 * @return
 */
VectorItem TopVector(Vector* self);

/**
 * 末尾の要素を削除して返します.
 * @param self
 * @return
 */
VectorItem PopVector(Vector* self);

/**
 * 指定位置に値を挿入します.
 * indexから末尾までの要素を一つ右にシフトします。
 * 次に index を item で上書きします。
 * @param self
 * @param index
 * @param item
 */
void InsertVector(Vector* self, int index, VectorItem item);

/**
 * 指定位置の要素を削除します.
 * @param self
 * @param index
 */
VectorItem RemoveVector(Vector* self, int index);

/**
 * 容量を圧縮します.
 * @param self
 */
void PackVector(Vector* self);

/**
 * 容量を拡張します.
 * @param self
 * @return 新しいキャパシティサイズ
 */
int ReserveVector(Vector* self);

/**
 * 指定位置の要素を上書きします.
 * 長さが足りない場合は 0 で伸ばします。
 * @param self
 * @param index
 * @param item
 */
void AssignVector(Vector* self, int index, VectorItem item);

/**
 * 指定位置の要素を返します.
 * @param self
 * @param index
 * @return
 */
VectorItem AtVector(Vector* self, int index);

/**
 * @param self
 * @param offset
 * @param len
 * @return
 */
Vector* SubVector(Vector* self, int offset, int len);

/**
 * 空なら true.
 * @param self
 * @return
 */
bool IsEmptyVector(Vector* self);

/**
 * 先頭から検索して一致するものがあるなら添え字を返します.
 * @param self
 * @param item
 * @return 見つからなければ -1
 */
int FindVector(Vector* self, VectorItem item);

/** 
 * 先頭から検索して一致するものがあるなら true を返します.
 * @param self
 * @param item
 * @return 見つからなければ false
 */
bool IsContainsVector(Vector* self, VectorItem item);

/**
 * 中身を空にします.
 * @param self
 */
void ClearVector(Vector* self);

/**
 * ベクターを開放します.
 * @param self
 * @param deleter
 */
void DeleteVector(Vector* self, VectorElementDeleter deleter);

/**
 * free によって解放するデリータ.
 * @param item
 */
void VectorDeleterByFree(VectorItem item);

/**
 * 何も行わないデリータ.
 * @param item
 */
void VectorDeleterOfNull(VectorItem item);

/**
 * @param source
 * @return
 */
Vector* CloneVector(Vector* source);

/**
 * srcからdestへコピーします.
 * @param src
 * @param dest
 */
void CopyVector(Vector* src, Vector* dst);

/**
 * @param self
 * @param a
 */
void EachVector(Vector* self, VectorAction a);

/**
 * @param src
 * @param dst
 */
void MergeVector(Vector* src, Vector* dst);
#endif // !SIGNAL_UTIL_VECTOR_H
