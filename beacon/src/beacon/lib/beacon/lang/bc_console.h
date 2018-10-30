#pragma once
#ifndef BEACON_LIB_SIGNAL_LANG_SG_CONSOLE_H
#define BEACON_LIB_SIGNAL_LANG_SG_CONSOLE_H
struct Type;
/**
 * beacon::lang::Consoleクラスを初期化します.
 */
void InitBCConsole();

/**
 * beacon::lang::Console型を返します.
 * @return
 */
struct Type* GetBCConsoleType();
#endif // !SIGNAL_LIB_SIGNAL_LANG_SG_CONSOLE_H
