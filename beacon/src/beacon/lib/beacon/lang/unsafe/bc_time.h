//BEGIN-AUTOGENERATED-BLOCK
/**
 * @file bc_time.h
 * @brief 時間に関する低レベルなラッパーです。
 * @author koya
 * @date 2018/10/31
 */
//END-AUTOGENERATED-BLOCK

#ifndef BEACON_LIB_BEACON_LANG_UNSAFE_BC_TIME_H
#define BEACON_LIB_BEACON_LANG_UNSAFE_BC_TIME_H
struct Type;

/**
 * beacon::unsafe::Timeクラスを初期化します。
 */
void InitTime();

/**
 * beacon::unsafe::Timeクラスを返します。
 * @return
 */
struct Type* GetTimeType();
#endif