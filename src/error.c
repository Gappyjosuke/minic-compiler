// error.c - Implementation of error reporting
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/error.h"


void parser_error_at(Token token, const char* message) {
    fprintf(stderr, "Syntax Error: %s at line %d, column %d (got '%s')\n",
            message, token.line, token.column, token.lexeme);
    exit(EXIT_FAILURE);
}


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

void parser_error(const char* message) {
    fprintf(stderr, "[Parser Error] %s\n", message);
    exit(1);
}

void parser_errorf(Token token, const char* fmt, ...) {
    fprintf(stderr, "[Parser Error] Line %d, Column %d: ", token.line, token.column);
    
    va_list args;
    va_start(args, fmt);
    
    vfprintf(stderr, fmt, args);
    va_end(args);
    
    fprintf(stderr, "\n");
    exit(1);
}



void parser_error_free_str(Token token, char* str_to_free, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    if (str_to_free) free(str_to_free);
    parser_error_at(token, buffer);
}