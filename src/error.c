// error.c - Implementation of error reporting
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/error.h"

void syntax_error(const char* msg) {
    fprintf(stderr, "[Syntax Error] %s\n", msg);
    exit(1);
}

void runtime_error(const char* msg) {
    fprintf(stderr, "[Runtime Error] %s\n", msg);
    exit(1);
}

void runtime_errorf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[Runtime Error] ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
