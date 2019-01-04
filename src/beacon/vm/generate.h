// BEGIN-AUTOGENERATED-BLOCK
/**
 * @file generate.h
 * @brief オペコードの生成を簡単にするための関数を定義します。
 * @author koya
 * @date 2018/10/31
 */
// END-AUTOGENERATED-BLOCK

#ifndef BEACON_VM_GENERATE_H
#define BEACON_VM_GENERATE_H
#include "../env/field.h"
#include "../env/method.h"
#include "../env/property.h"
#include "opcode_buf.h"

/**
 * フィールドを取得するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void bc_GenerateGetField(bc_OpcodeBuf* buf, bc_Field* fi, int index);

/**
 * プロパティを取得するオペコードを生成します.
 * @param buf
 * @param prop
 * @param index
 */
void bc_GenerateGetProperty(bc_OpcodeBuf* buf, bc_Property* prop, int index);

/**
 * フィールドに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void bc_GeneratePutField(bc_OpcodeBuf* buf, bc_Field* fi, int index);
/**
 * プロパティに代入するオペコードを生成します.
 * @param buf
 * @param fi
 * @param index
 */
void bc_GeneratePutProperty(bc_OpcodeBuf* buf, bc_Property* prop, int index);
#endif