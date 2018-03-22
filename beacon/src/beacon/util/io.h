#pragma once
#ifndef SIGNAL_UTIL_IO_H
#define SIGNAL_UTIL_IO_H
#include <stdio.h>
#include <stdbool.h>

/**
 * 新しいファイルを作成します.
 * @param filename
 * @return
 */
void io_new_file(const char* filename);

/**
 * 指定のファイルが既に存在するなら true.
 * @param filename
 * @return
 */
bool io_exists(const char* filename);

/**
 * ファイルが存在するかどうかを返します.
 * また、存在しなかった場合(fopenに失敗した場合)その原因を出力します。
 * @param filename
 * @return
 */
bool io_exists_s(const char* filename);

/**
 * 指定のファイルを削除します.
 * @param filename
 * @return
 */
bool io_delete(const char* filename);

/**
 * 指定のファイルを読み込んで返します.
 * @param filename
 * @return 呼び出し側で開放してください.
 */
char* io_read_text(const char* filename);

/**
 * 指定のファイルのテキストを上書きします.
 * @param filename
 * @param text
 * @return
 */
void io_write_text(const char* filename, const char* text);

/**
 * 実行時ディレクトリを基準として、
 * targetに表される位置を絶対パスに変換します.
 * @param target
 * @return 呼び出し側で開放してください.
 */
char* io_absolute_path(const char* target);
#endif // !SIGNAL_UTIL_IO_H