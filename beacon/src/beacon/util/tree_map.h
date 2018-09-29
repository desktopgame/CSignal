#pragma once
#ifndef BEACON_UTIL_TREE_MAP_H
#define BEACON_UTIL_TREE_MAP_H
/**
 * ツリーマップに格納可能なキーの型.
 */
typedef const char* tree_key;

/**
 * ツリーマップに格納可能な値の型.
 */
typedef void* tree_item;

/** 
 * キーと値を紐づけて管理するマップ.
 */
typedef struct tree_map {
	char* key;
	tree_item item;
	//struct tree_map* parent;
	struct tree_map* parent;
	struct tree_map* left;
	struct tree_map* right;
} tree_map;


/**
 * ツリーのアクション関数です.
 * @param item
 */
typedef void(*tree_action)(const char* name, tree_item item);

/**
 * ツリーのデリータ関数です.
 * @param item
 */
typedef void(*tree_element_deleter)(const char* name, tree_item item);

/**
 * 新しいツリーマップを作成します.
 * @return
 */
tree_map* NewTreeMap();

/**
 * 指定のツリーマップで指定のキーと値を紐づけます.
 * @param self
 * @param key
 * @param item
 */
tree_map* PutTreeMap(tree_map* self, tree_key key, tree_item item);

/**
 * 指定のツリーマップで指定のキーに紐づけられた値を返します.
 * @param self
 * @param key
 * @return
 */
tree_item GetTreeMapValue(tree_map* self, tree_key key);

/**
 * 要素を格納しているセルを返します.
 * @param self
 * @param key
 * @return
 */
tree_map* GetTreeMapCell(tree_map* self, tree_key key);

/**
 * ツリーのキーと引数のキーを比較します.
 * @param self
 * @param key
 * @return
 */
int CompareTreeMap(tree_map* self, tree_key key);

/**
 * ツリー内のすべての要素を訪問します.
 * @param self
 * @param act
 */
void EachTreeMap(tree_map* self, tree_action act);

/**
 * ツリーと全ての要素を削除します.
 * @param self
 * @param deleter
 */
void DeleteTreeMap(tree_map* self, tree_element_deleter deleter);

/**
 * freeによって解放するデリータの実装です.
 * @param item
 */
void DeleteTreeMapr_free(const char* key, tree_item item);

/**
 * 何も行わないデリータの実装です.
 * @param item
 */
void DeleteTreeMapr_null(const char* key, tree_item item);
#endif // !SIGNAL_UTIL_TREE_MAP_H
