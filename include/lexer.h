#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_INT,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_PRINT,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SEMICOLON,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
    int value;
} Token;

typedef struct TokenNode {
    Token token;
    struct TokenNode* next;
} TokenNode;

TokenNode* tokenize(const char* input);
void print_tokens(TokenNode* head);
void free_tokens(TokenNode* head);

#endif
