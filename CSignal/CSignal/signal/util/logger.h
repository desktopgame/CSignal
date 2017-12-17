#pragma once
#ifndef SIGNAL_UTIL_LOGGER_H
#define SIGNAL_UTIL_LOGGER_H
#include <stdarg.h>

/**
 * ���O�̃��x����\����.
 */
typedef enum log_level {
	log_debug,
	log_info,
	log_warn,
	log_error,
	log_fatal,
} log_level;

/**
 * ���K�[�̏o�͐�ƂȂ�t�@�C�����I�[�v�����܂�.
 */
void sg_lopen();

/**
 * ���K�[�̏o�͐�ƂȂ�t�@�C�����N���[�Y���܂�.
 */
void sg_lclose();

/**
 * �w��̃t�H�[�}�b�g�w�肵�ƌx�����x���ŕ�����\�����܂�.
 * @param level
 * @param filename
 * @param lineno
 * @param source
 * @param ...
 */
void sg_log(log_level level, const char* filename, int lineno, const char* source, ...);

//�}�N���������ꍇ�� LOG_OVERRIDE ���`���Ċ����̂��̂𖳌��ɂ��܂��B
//(���ƈ�ʓI�Ȗ��O���g�p���Ă���̂ŗp�ӂ��Ă܂��B)
#if defined(LOG_OVERRIDE)
#if defined(DEBUG)
#undef DEBUG
#endif

#if defined(INFO)
#undef INFO
#endif

#if defined(WARN)
#undef WARN
#endif

#if defined(ERROR)
#undef ERROR
#endif

#if defined(FATAL)
#undef FATAL
#endif
#endif

//���O�o�͗p�}�N���𖳌��ɂ���ɂ�
//LOG_DISABLE���`���܂��B
#if !defined(LOG_DISABLE)
#if defined(__FILE__) && defined(__LINE__)

#define DEBUG(source) sg_log(log_debug, __FILE__, __LINE__, source)
#define INFO(source) sg_log(log_info, __FILE__, __LINE__, source)
#define WARN(source) sg_log(log_warn, __FILE__, __LINE__, source)
#define ERROR(source) sg_log(log_error, __FILE__, __LINE__, source)
#define FATAL(source) sg_log(log_fatal, __FILE__, __LINE__, source)

#else
#define DEBUG(source) sg_log(log_debug, "invalid", -1, source)
#define INFO(source) sg_log(log_info, "invalid", -1, source)
#define WARN(source) sg_log(log_warn, "invalid", -1, source)
#define ERROR(source) sg_log(log_error, "invalid", -1, source)
#define FATAL(source) sg_log(log_fatal, "invalid", -1, source)

#endif
#endif
#endif // !SIGNAL_UTIL_LOGGER_H
