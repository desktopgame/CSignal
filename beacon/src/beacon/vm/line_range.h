//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file line_range.h
 * @brief ここに概要を記述します
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#pragma once
#ifndef BEACON_VM_LINE_RANGE_H
#define BEACON_VM_LINE_RANGE_H
#include <stdint.h>
#include "../util/vector.h"

/**
 * オペコードのどこからどこまでが何行目なのかを表す構造体.
 */
typedef struct LineRange {
	int StartOffset;
	int EndOffset;
	int Lineno;
} LineRange;
/**
 * 新しい範囲を作成します.
 * @return
 */
LineRange* NewLineRange();

/**
 * line_rangeの一覧から、指定の pc を含むレンジを返します.
 * @param line_rangeVec
 * @param pc
 * @return 見つからなければ NULL
 */
LineRange* FindLineRange(Vector* line_rangeVec, int pc);

void DeleteLineRange(LineRange* self);
#endif // !SIGNAL_VM_LINE_RANGE_H
