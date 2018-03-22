﻿#include "logger.h"
#include <stdio.h>
#include <time.h>
//#include <conio.h>
#include "text.h"
#include "io.h"
#include "mem.h"

#if defined(_WIN32)
#include <Windows.h>
#endif

//proto
static void sg_log_impl(log_level level, const char* filename, int lineno, const char * source, va_list ap);
static char* sg_unique_name();
static void sg_print_loglevel(log_level level);
static void sg_fprint_loglevel(FILE* fp, log_level level);
static void sg_pretty_paint_start(log_level level);
static void sg_pretty_paint_stop();
static bool sg_is_error(log_level level);

static FILE* logger_fp = NULL;
static bool logger_enabled = true;
static int logger_hour = 0;
static int logger_min = 0;
static int logger_sec = 0;

#if defined(_WIN32)
static WORD savedInstance;
//https://stackoverflow.com/questions/9203362/c-color-text-in-terminal-applications-in-windows
//http://vivi.dyndns.org/tech/cpp/setColor.html
#define COL_BLACK 0x00
#define COL_DARK_BLUE 0x01
#define COL_DARK_GREEN 0x02
#define COL_DARK_CYAN 0x03
#define COL_DARK_RED 0x04
#define COL_DARK_VIOLET0x05
#define COL_DARK_YELLOW 0x06
#define COL_GRAY 0x07
#define COL_LIGHT_GRAY 0x08
#define COL_BLUE 0x09
#define COL_GREEN 0x0a
#define COL_CYAN 0x0b
#define COL_RED 0x0c
#define COL_VIOLET 0x0d
#define COL_YELLOW 0x0e
#define COL_WHITE 0x0f
#define COL_INTENSITY 0x08	// 高輝度マスク
#define COL_RED_MASK 0x04	// 赤色ビット
#define COL_GREEN_MASK 0x02	// 緑色ビット
#define COL_BLUE_MASK 0x01	//  青色ビット
#endif

void logger_open() {
	if (logger_fp != NULL) {
		return;
	}
	char* name = sg_unique_name();
	if (name == NULL) {
		logger_fp = NULL;
		return;
	}
	if (!io_exists(name)) {
		io_new_file(name);
	}
#if defined(_MSC_VER)
	FILE* fp;
	errno_t e = fopen_s(&fp, name, "a");
	if (e) {
		mem_free(name, __FILE__,__LINE__);
		//MEM_FREE(name);
		return;
	}
	mem_free(name, __FILE__, __LINE__);
	//MEM_FREE(name);
	logger_fp = fp;
#else
	FILE* fp = fopen(name, "a");
	mem_free(name, __FILE__, __LINE__);
	logger_fp = fp;
#endif
	fprintf(logger_fp, "%d:%d:%d", logger_hour, logger_min, logger_sec);
	fputs("\n", logger_fp);
}

void logger_close() {
	if (logger_fp == NULL) {
		return;
	}
	fputs("\n", logger_fp);

	fflush(logger_fp);
	fclose(logger_fp);
	logger_fp = NULL;
}

void logger_set_enabled(bool b) {
	logger_enabled = b;
}

bool logger_is_enabled() {
	return logger_enabled;
}

//http://www.serendip.ws/archives/4635
void logger_log(log_level level, const char* filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(level, filename, lineno, source, ap);
	}
	va_end(ap);
}

//FIXME:コピペ
void logger_debug(const char * filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(log_debug, filename, lineno, source, ap);
	}
	va_end(ap);
}

void logger_info(const char * filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(log_info, filename, lineno, source, ap);
	}
	va_end(ap);
}

void logger_warn(const char * filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(log_warn, filename, lineno, source, ap);
	}
	va_end(ap);
}

void logger_error(const char * filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(log_error, filename, lineno, source, ap);
	}
	va_end(ap);
}

void logger_fatal(const char * filename, int lineno, const char * source, ...) {
	va_list ap;
	va_start(ap, source);
	if (logger_enabled) {
		sg_log_impl(log_fatal, filename, lineno, source, ap);
	}
	va_end(ap);
}

void logger_test(bool cond) {
	if (cond) {
		int x = 0;
	}
}

//private
static void sg_log_impl(log_level level, const char* filename, int lineno, const char * source, va_list ap) {
#define LEN 256
//	va_list ap;
//	va_start(ap, source);
	//ソース文字列をフォーマットする
	char buff[LEN];
	int res = text_vsprintf(buff, LEN, source, ap);
	//フォーマット失敗
	if (res == -1) {
		text_printf("internal error: %s %d %s", filename, lineno, source);
		//現在開いているファイルがあるなら書き出す
		if (logger_fp != NULL) {
			//rewind(logger_fp);
			fprintf(logger_fp, "internal error: %s %s %d", source, filename, lineno);
			fputs("\n", logger_fp);
			fflush(logger_fp);
		}
		//フォーマット成功
	} else {
		sg_pretty_paint_start(level);
		sg_print_loglevel(level);
		text_printf(buff);
		text_printf(" [");
		text_printf("%s %d", filename, lineno);
		text_printf("]");
		sg_pretty_paint_stop();
		//現在開いているファイルがあるなら書き出す
		if (logger_fp != NULL) {
			//rewind(logger_fp);
			sg_fprint_loglevel(logger_fp, level);
			fprintf(logger_fp, buff);
			fprintf(logger_fp, " [");
			fprintf(logger_fp, "%s %d", filename, lineno);
			fprintf(logger_fp, "]");
			fputs("\n", logger_fp);
			fflush(logger_fp);
		}
	}
//	va_end(ap);
	text_putline();
#undef LEN
}

static char* sg_unique_name() {
	//http://www.c-tipsref.com/tips/time/time.html
#if defined(_MSC_VER)
	errno = 0;
	//現在の時刻を取得
	time_t timer = time(NULL);
	struct tm local;
	errno_t e = localtime_s(&local, &timer);
	//取得出来なかった場合はNULL
	//=ログファイルは作成できない
	if (e) {
		return NULL;
	}
	char buff[200];
	errno_t e2 = text_sprintf(
		buff, 
		200, 
		"log(%d-%d-%d).txt",
		local.tm_year + 1900,
		local.tm_mon + 1,
		local.tm_mday
	);
	if (e2) {
		//return NULL;
	}
	//ここでファイル作成時の時間を記録しておく
	//後で書き込むので
	logger_hour = local.tm_hour;
	logger_min = local.tm_min;
	logger_sec = local.tm_sec;

	char* name = text_strdup(buff);
	return name;
#else
	return NULL;
#endif
}

static void sg_print_loglevel(log_level level) {
	switch (level) {
		case log_debug:
			text_printf("debug: ");
			break;
		case log_info:
			text_printf("info: ");
			break;
		case log_warn:
			text_printf("warn: ");
			break;
		case log_error:
			text_printf("error: ");
			break;
		case log_fatal:
			text_printf("fatal: ");
			break;
		default:
			break;
	}
}

static void sg_fprint_loglevel(FILE* fp, log_level level) {
	switch (level) {
		case log_debug:
			fprintf(fp, "debug: ");
			break;
		case log_info:
			fprintf(fp, "info: ");
			break;
		case log_warn:
			fprintf(fp, "warn: ");
			break;
		case log_error:
			fprintf(fp, "error: ");
			break;
		case log_fatal:
			fprintf(fp, "fatal: ");
			break;
		default:
			break;
	}
}

static void sg_pretty_paint_start(log_level level) {
#if defined(_WIN32)
	HANDLE h;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	//現在の設定をバックアップ
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &csbi);
	savedInstance = csbi.wAttributes;
	//色を付ける
	switch (level) {
		case log_debug:
			SetConsoleTextAttribute(h, COL_WHITE);
			break;
		case log_info:
			SetConsoleTextAttribute(h, COL_GRAY);
			break;
		case log_warn:
			SetConsoleTextAttribute(h, COL_YELLOW);
			break;
		case log_error:
			SetConsoleTextAttribute(h, COL_RED);
			break;
		case log_fatal:
			SetConsoleTextAttribute(h, COL_RED);
			//SetConsoleTextAttribute(h, COMMON_LVB_UNDERSCORE);
			break;
		default:
			break;
	}
#else
	//
	//no operation
	//
#endif // defined(_WIN32)
}

static void sg_pretty_paint_stop() {
#if defined(_WIN32)
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, savedInstance);
#else
	//
	//no operation
	//
#endif
}

static bool sg_is_error(log_level level) {
	return level == log_warn ||
		level == log_error ||
		level == log_fatal;
}