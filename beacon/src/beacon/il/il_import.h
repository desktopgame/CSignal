#ifndef BEACON_IL_IL_IMPORT_H
#define BEACON_IL_IL_IMPORT_H
#include "../util/string_pool.h"
/**
 * インポート宣言を表す要素.
 */
typedef struct ILImport {
	StringView Path;
} ILImport;

/**
 * 指定のパスをインポートするインポート宣言を作成します.
 * 引数は呼び出し側で解放してください。
 * @param path
 * @return
 */
ILImport* NewILImport(StringView path);

/**
 * このインポート宣言と包含された文字列を解放します.
 * @param self
 */
void DeleteILImport(ILImport* self);
#endif // !SIGNAL_IL_IL_IMPORT_H
