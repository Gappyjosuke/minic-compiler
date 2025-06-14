// parser.c: Parses tokens into AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast.h"

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
static ASTNode* parse_statement();
static ASTNode* parse_expression();
static ASTNode* parse_term();

// Entry point
ASTNode* parse_program(TokenNode* tokens) {
    current = tokens;
    ASTNode* head = NULL;
    ASTNode* tail = NULL;

    while (current != NULL && current->token.type != TOKEN_EOF) {
        ASTNode* stmt = parse_statement();

        if (head == NULL) {
            head = tail = stmt;
        } else {
            tail->next = stmt;
            tail = stmt;
        }
    }
    return head;
}

// statement → declaration | print_statement | assignment
ASTNode* parse_statement() {
    if (match(TOKEN_INT) || match(TOKEN_LET)) {
        if (current->token.type == TOKEN_IDENTIFIER) {
            char* name = strdup(current->token.lexeme);
            advance();

            if (!match(TOKEN_ASSIGN)) {
                fprintf(stderr, "Syntax Error: Expected '=' after identifier\n");
                exit(1);
            }

            ASTNode* value = parse_expression();

            if (!match(TOKEN_SEMICOLON)) {
                fprintf(stderr, "Syntax Error: Expected ';'\n");
                exit(1);
            }

            return create_var_decl_node(name, value);
        } else {
            fprintf(stderr, "Syntax Error: Expected identifier after 'int'\n");
            exit(1);
        }
    }
    

    if (current->token.type == TOKEN_IDENTIFIER) {
        char* name = strdup(current->token.lexeme);
        advance();

        if (!match(TOKEN_ASSIGN)) {
            fprintf(stderr, "Syntax Error: Expected '=' after identifier '%s'\n", name);
            exit(1);
        }

        ASTNode* value = parse_expression();

        if (!match(TOKEN_SEMICOLON)) {
            fprintf(stderr, "Syntax Error: Expected ';'\n");
            exit(1);
        }

        return create_assign_node(name, value);
    }

    if (match(TOKEN_PRINT)) {
        if (!match(TOKEN_LPAREN)) {
            fprintf(stderr, "Syntax Error: Expected '('\n");
            exit(1);
        }

        ASTNode* expr = parse_expression();

        if (!match(TOKEN_RPAREN)) {
            fprintf(stderr, "Syntax Error: Expected ')'\n");
            exit(1);
        }

        if (!match(TOKEN_SEMICOLON)) {
            fprintf(stderr, "Syntax Error: Expected ';'\n");
            exit(1);
        }

        return create_print_node(expr);
    }

    fprintf(stderr, "Syntax Error: Unknown statement at token '%s'\n", current->token.lexeme);
    exit(1);
}


static ASTNode* parse_expression() {
    ASTNode* left = parse_term();
    while (current->token.type == TOKEN_PLUS) {
        TokenType op = current->token.type;
        advance();
        ASTNode* right = parse_term();
        left = create_binary_op_node(op,left,right);
    }

    return left;
}


static ASTNode* parse_term() {
    if(current->token.type == TOKEN_NUMBER ) {
        int val = current->token.value;
        advance();
        return create_literal_node(val);
    }
    if (current->token.type == TOKEN_IDENTIFIER) {
        char* name = strdup(current->token.lexeme);
        advance();
        return create_variable_node(name);
    } 
    fprintf(stderr, "Syntax Error: Expected number or identifier\n");
    exit(1);
}

