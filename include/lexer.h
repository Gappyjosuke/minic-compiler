#ifndef LEXER_H
#define LEXER_H


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
    TOKEN_LET,
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

const char* token_type_to_string(TokenType type); 

TokenNode* tokenize(const char* source_code);
TokenNode* tokenize_file(const char* filename);
void free_tokens(TokenNode* head);
void free_tokens(TokenNode* head);

#endif
