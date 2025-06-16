#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

int debug_lexer = 0;

// ---------------------- Token Type Name ----------------------

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_INT: return "int";
        case TOKEN_IDENTIFIER: return "identifier";
        case TOKEN_ASSIGN: return "=";
        case TOKEN_NUMBER: return "number";
        case TOKEN_PLUS: return "+";
        case TOKEN_MINUS: return "-";
        case TOKEN_STAR: return "*";
        case TOKEN_PRINT: return "print";
        case TOKEN_LPAREN: return "(";
        case TOKEN_RPAREN: return ")";
        case TOKEN_SEMICOLON: return ";";
        case TOKEN_LET: return "let";
        case TOKEN_SLASH: return "/";
        case TOKEN_LT: return "<";
        case TOKEN_LE: return "<=";
        case TOKEN_GT: return ">";
        case TOKEN_GE: return ">=";
        case TOKEN_EQ: return "==";
        case TOKEN_NEQ: return "!=";
        case TOKEN_EOF: return "EOF";
        default: return "UNKNOWN";
    }
}

// ---------------------- Internal Helper ----------------------

TokenNode* add_token(TokenNode* tail, Token token) {
    TokenNode* new_node = (TokenNode*)malloc(sizeof(TokenNode));
    new_node->token = token;
    new_node->next = NULL;
    tail->next = new_node;
    return new_node;
}

// ---------------------- Tokenize from Source Code ----------------------

TokenNode* tokenize(const char* input) {
    TokenNode* head = (TokenNode*)malloc(sizeof(TokenNode));
    TokenNode* tail = head;
    head->next = NULL;

    const char* p = input;
    int line = 1;
    int column = 1;

    if (debug_lexer) {
        printf("Raw input starts with: %.50s\n", p);
    }

    while (*p) {
        while (isspace(*p)) {
            if (*p == '\n') {
                line++;
                column = 1;
            } else {
                column++;
            }
            p++;
        }
        // End of file after whitespace
        if (*p == '\0') break;

        // Skip single-line comments
        if (*p == '/' && *(p + 1) == '/') {
            while (*p && *p != '\n') {
                p++; //skip till end of line
                column++;
            }
            continue; //try next loop
        }

        // Skip block comments (/* ... */)
        if (*p == '/' && *(p + 1) == '*') {
            p += 2; // Skip the '/*'
            column +=2;
            while (*p && !(*p == '*' && *(p + 1) == '/')) {
                if (*p == '\n') {
                    line++;
                    column = 1;
                } else {
                    column++;
                }
                p++;
            }
            if (*p == '*' && *(p + 1) == '/') {
                p += 2;
                column +=2;
            } else { 
                fprintf(stderr, "Unterminated block comment at line %d\n", line);
                exit(1);
            }
            continue;
        }
        
        // End of input
        if (*p == '\0') break;


        // Token template
        Token token;
        token.value = 0;
        token.line = line;
        token.column = column;


        //Numbers
        if (isdigit(*p)) {
            char num[32];
            int len = 0;
            while (isdigit(*p)){ 
                num[len++] = *p++;
                column++;
            }
            num[len] = '\0';
            token.type = TOKEN_NUMBER;
            strcpy(token.lexeme, num);
            token.value = atoi(num);
            
            tail = add_token(tail, token);
            continue;
        } 
        //Identifiers and Keywords
        else if (isalpha(*p)) {
            char id[64];
            int len = 0;
            while (isalnum(*p)){ 
                id[len++] = *p++;
                column++;
            }
            id[len] = '\0';

            if (strcmp(id, "int") == 0) token.type = TOKEN_INT;
            else if (strcmp(id, "print") == 0) token.type = TOKEN_PRINT;
            else if (strcmp(id, "let") == 0) token.type = TOKEN_LET;
            else token.type = TOKEN_IDENTIFIER;
            strcpy(token.lexeme, id);

            tail = add_token(tail, token);
            continue;
        } 
        //Symbol and operators
        if (*p == '=' && *(p + 1) == '=') {
            token.type = TOKEN_EQ;
            strcpy(token.lexeme, "==");
            p += 2;
            column += 2;
        } else if (*p == '!' && *(p + 1) == '=') {
            token.type = TOKEN_NEQ;
            strcpy(token.lexeme, "!=");
            p += 2;
            column += 2;
        } else if (*p == '<' && *(p + 1) == '=') {
            token.type = TOKEN_LE;
            strcpy(token.lexeme, "<=");
            p += 2;
            column += 2;
        } else if (*p == '>' && *(p + 1) == '=') {
            token.type = TOKEN_GE;
            strcpy(token.lexeme, ">=");
            p += 2;
            column += 2;
        } else if (*p == '<') {
            token.type = TOKEN_LT;
            strcpy(token.lexeme, "<");
            p++;
            column++;
        } else if (*p == '>') {
            token.type = TOKEN_GT;
            strcpy(token.lexeme, ">");
            p++;
            column++;
        } else {
            switch (*p) {
                case '=':
                    token.type = TOKEN_ASSIGN;
                    strcpy(token.lexeme, "=");
                    break;
                case '+':
                    token.type = TOKEN_PLUS;
                    strcpy(token.lexeme, "+");
                    break;
                case '-':
                    token.type = TOKEN_MINUS;
                    strcpy(token.lexeme, "-");
                    break;
                case '*':
                    token.type = TOKEN_STAR;
                    strcpy(token.lexeme, "*");
                    break;
                case '/':
                    token.type = TOKEN_SLASH;
                    strcpy(token.lexeme, "/");
                    break;
                case '(':
                    token.type = TOKEN_LPAREN;
                    strcpy(token.lexeme, "(");
                    break;
                case ')':
                    token.type = TOKEN_RPAREN;
                    strcpy(token.lexeme, ")");
                    break;
                case ';':
                    token.type = TOKEN_SEMICOLON;
                    strcpy(token.lexeme, ";");
                    break;
                default:
                    fprintf(stderr, "Unknown character '%c' at line %d, column %d\n", *p, line, column);
                    p++;
                    column++;
                    continue;
            }
            p++;
            column++;
        }

        tail = add_token(tail, token);
    }
    //Add EOF token
    Token eof_token;
    eof_token.type = TOKEN_EOF;
    strcpy(eof_token.lexeme, "EOF");
    eof_token.value = 0;
    eof_token.line = line;
    eof_token.column = column;
    add_token(tail, eof_token);    

    return head->next;
}

// ---------------------- Tokenize from File ----------------------

TokenNode* tokenize_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Could not open file: %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        exit(1);
    }

    fread(buffer, 1, size, file);
    buffer[size] = '\0';
    fclose(file);

    TokenNode* tokens = tokenize(buffer);
    free(buffer);
    return tokens;
}

// ---------------------- Print & Cleanup ----------------------

void print_tokens(TokenNode* head) {
    TokenNode* current = head;
    while (current) {
        printf("Token: %-12s Lexeme: %-10s Value: %d (Line: %d, Col: %d)\n",
            token_type_to_string(current->token.type),
            current->token.lexeme,
            current->token.value,
            current->token.line,
            current->token.column);
        current = current->next;
    }
}


void free_tokens(TokenNode* head) {
    TokenNode* current = head;
    while (current) {
        TokenNode* next = current->next;
        free(current);
        current = next;
    }
}
