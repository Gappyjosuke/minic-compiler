#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

// ---------------------- Token Type Name ----------------------

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_INT: return "TOKEN_INT";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";
        case TOKEN_ASSIGN: return "TOKEN_ASSIGN";
        case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";
        case TOKEN_PRINT: return "TOKEN_PRINT";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_LET: return "TOKEN_LET";
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
    printf("Raw input starts with: %.50s\n", p);

    while (*p) {
        while (isspace(*p)) p++;

        Token token;
        token.value = 0;

        if (isdigit(*p)) {
            char num[32];
            int len = 0;
            while (isdigit(*p)) num[len++] = *p++;
            num[len] = '\0';
            token.type = TOKEN_NUMBER;
            strcpy(token.lexeme, num);
            token.value = atoi(num);
        } else if (isalpha(*p)) {
            char id[64];
            int len = 0;
            while (isalnum(*p)) id[len++] = *p++;
            id[len] = '\0';
            if (strcmp(id, "int") == 0) token.type = TOKEN_INT;
            else if (strcmp(id, "print") == 0) token.type = TOKEN_PRINT;
            else if (strcmp(id, "let") == 0) token.type = TOKEN_LET;
            else token.type = TOKEN_IDENTIFIER;
            strcpy(token.lexeme, id);
        } else {
            switch (*p) {
                case '=': token.type = TOKEN_ASSIGN; token.lexeme[0] = '='; token.lexeme[1] = '\0'; p++; break;
                case '+': token.type = TOKEN_PLUS; token.lexeme[0] = '+'; token.lexeme[1] = '\0'; p++; break;
                case '(': token.type = TOKEN_LPAREN; token.lexeme[0] = '('; token.lexeme[1] = '\0'; p++; break;
                case ')': token.type = TOKEN_RPAREN; token.lexeme[0] = ')'; token.lexeme[1] = '\0'; p++; break;
                case ';': token.type = TOKEN_SEMICOLON; token.lexeme[0] = ';'; token.lexeme[1] = '\0'; p++; break;
                default: p++; continue;
            }
        }

        tail = add_token(tail, token);
    }

    Token eof_token = { TOKEN_EOF, "EOF", 0 };
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
        printf("Token: %-12s Lexeme: %-10s Value: %d\n",
            token_type_to_string(current->token.type),
            current->token.lexeme,
            current->token.value);
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
