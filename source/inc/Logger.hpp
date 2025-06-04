#pragma once
#include <iostream>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <ctime>

#define error(format, ...) \
	(logger::_error(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))
#define warning(format, ...) \
	(logger::_warning(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))
#define warn(format, ...) \
	(logger::_warning(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))
#define info(format, ...) \
	(logger::_info(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))
#define debug(format, ...) \
	(logger::_debug(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))
#define fatal(format, ...) \
	(logger::_fatal(__FILE__, __FUNCTION__, __LINE__, format __VA_OPT__(,) __VA_ARGS__))

typedef enum {
	Default = 39,
	Black   = 30,
	Red	 = 31,
	Green   = 32,
	Yellow  = 33,
	Blue	= 34,
	Purple  = 35,
	Cyan	= 36,
	White   = 37,

	BG_Default = 49,
	BG_Black   = 40,
	BG_Red	 = 41,
	BG_Green   = 42,
	BG_Yellow  = 43,
	BG_Blue	= 44,
	BG_Purple  = 45,
	BG_Cyan	= 46,
	BG_White   = 47,
} TermColor;

typedef enum {
	Clear,
	Bold,
	Underline,
	Reset,
	MoveHome,
	HideCursor,
	ShowCursor,
	Move,		 // Needs row and column
	SetColor,	 // Needs TermColor
} TermCmd;

namespace logger {
	void _error(const char* file, const char* func, const unsigned int line, const char* format, ...);
	void _warning(const char* file, const char* func, const unsigned int line, const char* format, ...);
	void _warn(const char* file, const char* func, const unsigned int line, const char* format, ...);
	void _info(const char* file, const char* func, const unsigned int line, const char* format, ...);
	void _debug(const char* file, const char* func, const unsigned int line, const char* format, ...);
	void _fatal(const char* file, const char* func, const unsigned int line, const char* format, ...);

	void set(const TermCmd cmd);
	void set(const TermCmd cmd, int row, int col);
	void set(const TermCmd cmd, const TermColor tc);
};
