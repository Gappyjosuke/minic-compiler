// parser.c: Parses tokens into AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static TokenNode* current;

// Advance to next token
static void advance() {
    if (current != NULL)
        current = current->next;
}

// Match current token type
static int match(TokenType type) {
    if (current != NULL && current->token.type == type) {
        advance();
        return 1;
    }
    return 0;
}

// Forward declarations
void parse_statement();
void parse_expression();
void parse_term();

// Entry point
void parse_program(TokenNode* tokens) {
    current = tokens;
    while (current != NULL && current->token.type != TOKEN_EOF) {
        parse_statement();
    }
}

// statement → declaration | print_statement | assignment
void parse_statement() {
    if (match(TOKEN_INT)) {
        if (current != NULL && current->token.type == TOKEN_IDENTIFIER) {
            printf("Parse: Variable declaration: %s\n", current->token.lexeme);
            advance();

            if (match(TOKEN_ASSIGN)) {
                parse_expression();

                if (!match(TOKEN_SEMICOLON)) {
                    fprintf(stderr, "Syntax Error: Expected ';'\n");
                    return;
                }
            } else {
                fprintf(stderr, "Syntax Error: Expected '='\n");
                return;
            }
        } else {
            fprintf(stderr, "Syntax Error: Expected identifier after 'int'\n");
            return;
        }
    }
    else if (current != NULL &&
             current->token.type == TOKEN_IDENTIFIER &&
             strcmp(current->token.lexeme, "printf") == 0) {

        advance(); // skip 'printf'

        if (match(TOKEN_LPAREN)) {
            parse_expression();

            if (!match(TOKEN_RPAREN)) {
                fprintf(stderr, "Syntax Error: Expected ')'\n");
                return;
            }

            if (!match(TOKEN_SEMICOLON)) {
                fprintf(stderr, "Syntax Error: Expected ';'\n");
                return;
            }

            printf("Parse: Print statement\n");
        } else {
            fprintf(stderr, "Syntax Error: Expected '('\n");
            return;
        }
    }
    else if (current != NULL && current->token.type == TOKEN_IDENTIFIER) {
        // assignment like: G = 5;
        char* name = current->token.lexeme;
        advance();

        if (match(TOKEN_ASSIGN)) {
            parse_expression();

            if (!match(TOKEN_SEMICOLON)) {
                fprintf(stderr, "Syntax Error: Expected ';'\n");
                return;
            }

            printf("Parse: Assignment to variable: %s\n", name);
        } else {
            fprintf(stderr, "Syntax Error: Expected '=' after identifier '%s'\n", name);
            return;
        }
    }
    else {
        fprintf(stderr, "Syntax Error: Unknown statement at token '%s'\n", current->token.lexeme);
        advance(); // skip to recover
    }
}


// expression → term ( '+' term )*
void parse_expression() {
    parse_term();
    while (current != NULL && current->token.type == TOKEN_PLUS) {
        advance();
        parse_term();
    }
}

// term → NUMBER | IDENTIFIER
void parse_term() {
    if (current != NULL &&
        (current->token.type == TOKEN_NUMBER || current->token.type == TOKEN_IDENTIFIER)) {
        advance();
    } else {
        fprintf(stderr, "Syntax Error: Expected number or identifier, got '%s'\n",
                current ? current->token.lexeme : "EOF");
        if (current) advance();
    }
}
