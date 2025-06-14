#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

static TokenNode* add_token(TokenNode* tail, Token token) {
    TokenNode* new_node = (TokenNode*)malloc(sizeof(TokenNode));
    new_node->token = token;
    new_node->next = NULL;
    tail->next = new_node;
    return new_node;
}

TokenNode* tokenize(const char* input) {
    TokenNode* head = (TokenNode*)malloc(sizeof(TokenNode));
    TokenNode* tail = head;
    head->next = NULL;

    const char* p = input;

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

void print_tokens(TokenNode* head) {
    TokenNode* current = head;
    while (current) {
        printf("Token: %-12s Lexeme: %-10s Value: %d\n",
            (current->token.type == TOKEN_INT) ? "INT" :
            (current->token.type == TOKEN_IDENTIFIER) ? "IDENTIFIER" :
            (current->token.type == TOKEN_ASSIGN) ? "ASSIGN" :
            (current->token.type == TOKEN_NUMBER) ? "NUMBER" :
            (current->token.type == TOKEN_PLUS) ? "PLUS" :
            (current->token.type == TOKEN_PRINT) ? "PRINT" :
            (current->token.type == TOKEN_LPAREN) ? "LPAREN" :
            (current->token.type == TOKEN_RPAREN) ? "RPAREN" :
            (current->token.type == TOKEN_SEMICOLON) ? "SEMICOLON" : "EOF",
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
