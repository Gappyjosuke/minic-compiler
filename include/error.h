// error.h - Centralized error handling
#ifndef ERROR_H
#define ERROR_H

#include "lexer.h"


__attribute__((noreturn))
void parser_error(const char* message);

__attribute__((noreturn))
void parser_errorf(Token token, const char* fmt, ...);

// Report a syntax error and exit
void syntax_error(const char* msg);

// Report a runtime error and exit
void runtime_error(const char* msg);

// Like runtime_error, but with formatted input (like printf)
void runtime_errorf(const char* fmt, ...);

#endif // ERROR_H
