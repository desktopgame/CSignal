#ifndef BEACON_VM_GENERATE_H
#define BEACON_VM_GENERATE_H
#include "opcode_buf.h"
#include "../env/field.h"
#include "../env/method.h"
#include "../env/property.h"

/**
 * フィールドを取得するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GenerateGetField(OpcodeBuf* buf, Field* fi, int index);

/**
 * プロパティを取得するオペコードを生成します.
 * @param buf
 * @param prop
 * @param index
 */
void GenerateGetProperty(OpcodeBuf* buf, Property* prop, int index);

/**
 * フィールドに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GeneratePutField(OpcodeBuf* buf, Field* fi, int index);
/**
 * プロパティに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void GeneratePutProperty(OpcodeBuf* buf, Property* prop, int index);
#endif