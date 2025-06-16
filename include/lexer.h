#ifndef LEXER_H
#define LEXER_H

extern int debug_lexer;

typedef enum {
    // Basic tokens (0-10)
    TOKEN_INT = 0,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,       // =
    TOKEN_NUMBER,
    TOKEN_PLUS,         // +
    TOKEN_MINUS,        // -
    TOKEN_STAR,         // *
    TOKEN_PRINT,
    TOKEN_LPAREN,       // (
    TOKEN_RPAREN,       // )
    TOKEN_SEMICOLON,    // ;
    
    // Keywords (11-15)
    TOKEN_LET,
    
    // Operators (16-25)
    TOKEN_SLASH = 16,   // /
    TOKEN_LT,           // <
    TOKEN_LE,           // <=
    TOKEN_GT,           // >
    TOKEN_GE,           // >=
    TOKEN_EQ = 21,           // ==
    TOKEN_NEQ =22,          // !=

    // End marker
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[64];
    int value;
    int line;
    int column;
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
