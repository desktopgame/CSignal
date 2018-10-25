#ifndef BEACON_IL_IL_TOP_LEVEL_H
#define BEACON_IL_IL_TOP_LEVEL_H
#include "../util/vector.h"

/**
 * 中間言語ILのトップレベル要素です.
 */
typedef struct ILToplevel {
	Vector* ImportList;
	Vector* NamespaceList;
	Vector* StatementList;
	Vector* FunctionList;
} ILToplevel;
/**
 * トップレベルの要素を作成します.
 * @return
 */
ILToplevel* NewILToplevel();

/**
 * この要素と付随する全てを解放します.
 * @param self
 */
void DeleteILToplevel(ILToplevel* self);
#endif // !SIGNAL_IL_IL_TOP_LEVEL_H
