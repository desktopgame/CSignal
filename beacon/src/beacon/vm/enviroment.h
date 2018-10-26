#pragma once
#ifndef BEACON_VM_ENVIROMENT_H
#define BEACON_VM_ENVIROMENT_H
#include "../util/vector.h"
#include "../util/string_pool.h"
#include "opcode_buf.h"
#include "symbol_table.h"
#include <stdbool.h>
struct class_;
struct Object;
struct ClassLoader;
struct FQCNCache;
/**
 * プログラムの実行環境です.
 * スタックや変数は実行時に変化しますが、
 * 定数プールやオペランドのようなコンパイル時に決定して
 * 不変なものをここでは Enviroment と呼称します。
 */
typedef struct Enviroment {
	struct ClassLoader* ContextRef;
	OpcodeBuf* Bytecode;
	SymbolTable* Symboles;
	Vector* ConstantPool;
	Vector* LineRangeTable;
} Enviroment;

/**
 * 環境を生成します.
 * @return
 */
Enviroment* NewEnviroment();

/**
 * 指定の行番号を開始します.
 * @param self
 * @param lineno
 */
void AddRangeEnviroment(Enviroment* self, int lineno);

/**
 * この Enviroment に含まれるオペコードの一覧をダンプします.
 * DumpOpcodeBuf との違いは、行番号を出力できる点です。
 * @param self
 * @param depth
 */
void DumpEnviromentOp(Enviroment* self, int depth);

/**
 * 定数プールに整数を追加して、その位置を返します.
 * @param i
 * @return
 */
int AddCIntEnviroment(Enviroment* self, int i);

/**
 * 定数プールに浮動小数を追加して、その位置を返します.
 * @param d
 * @return
 */
int AddCDoubleEnviroment(Enviroment* self, double d);

/**
 * 定数プールに文字を追加して、その位置を返します.
 * @param c
 * @return
 */
int AddCCharEnviroment(Enviroment* self, char c);

/**
 * 定数プールに文字列を追加して、その位置を返します.
 * @param sv
 * @return
 */
int AddCStringEnviroment(Enviroment* self, StringView sv);

/**
 * 指定位置のオペコード/オペランドを返します.
 * @param self
 * @param index
 * @return
 */
VectorItem GetEnviromentSourceAt(Enviroment* self, int index);

/**
 * 指定位置の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct Object* GetEnviromentConstantAt(Enviroment* self, int index);

/**
 * 指定位置の整数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct Object* GetEnviromentCIntAt(Enviroment* self, int index);

/**
 * 指定位置の浮動小数型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct Object* GetEnviromentCDoubleAt(Enviroment* self, int index);

/**
 * 指定位置の文字型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct Object* GetEnviromentCCharAt(Enviroment* self, int index);

/**
 * 指定位置の文字列型の定数を返します.
 * @param self
 * @param index
 * @return
 */
struct Object* GetEnviromentCStringAt(Enviroment* self, int index);

/**
 * 環境を開放します.
 * @return
 */
void DeleteEnviroment(Enviroment* self);
#endif // !SIGNAL_VM_ENVIROMENT_H
