// parser.c: Parses tokens into AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast.h"

static TokenNode* current;

// Advance to next token
static ASTNode* advance() {
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
ASTNode* parse_statement();
ASTNode* parse_expression();
ASTNode* parse_term();

// Entry point
ASTNode* parse_program(TokenNode* tokens) {
    current = tokens;
    ASTNode* program = create_node(AST_PROGRAM);

    while (current != NULL && current->token.type != TOKEN_EOF) {
      ASTNode* stmt = parse_statement();
      if (stmt) {
        add_child(program, stmt);
      }
    }
    return program;
}

// statement → declaration | print_statement | assignment
ASTNode* parse_statement() {
    if (match(TOKEN_INT)) {
        if (current->token.type == TOKEN_IDENTIFIER) {
            ASTNode* decl = create_node(AST_VAR_DECL);
            decl->name = strdup(current->token.lexeme);
            advance();

            if (match(TOKEN_ASSIGN)) {
                ASTNode* expr = parse_expression();
                add_child(dec1, expr);

                if (!match(TOKEN_SEMICOLON)) {
                    fprintf(stderr, "Syntax Error: Expected ';'\n");
                    exit(1);
                }
            } else {
                fprintf(stderr, "Syntax Error: Expected '='\n");
                exit(1);
            }

            return dec1;
        } else {
            fprintf(stderr, "Syntax Error: Expected identifier after 'int'\n");
            exit(1);
        }
    }
    else if (current->token.type == TOKEN_IDENTIFIER ) {
        ASTNode* assign = create_node(AST_ASSIGN);
        assign->name = strdup(current->token.lexeme);
        advance();
        

        if (match(TOKEN_ASSIGN)) {
            ASTNode* expr = parse_expression();
            add_child(assign, expr);

            if (!match(TOKEN_SEMICOLON)) {
                fprintf(stderr, "Syntax Error: Expected ';'\n");
                exit(1);
            }

            return assign;
        } else {
            fprintf(stderr, "Syntax Error: Expected '=' after identifier '%s'\n", assign->name);
            exit(1);
        }
    } else if (match(TOKEN_PRINT)) {
        if (match(TOKEN_LPAREN)) {
            ASTNode* print = create_node(AST_PRINT);
            ASTNode* expr = parse_expression();
            add_child(print, expr);

            if (!match(TOKEN_RPAREN)) {
                fprintf(stderr, "Syntax Error: Expected ')'\n");
                exit(1);
            }
            if (!match(TOKEN_SEMICOLON)) {
                fprintf(stderr, "Syntax Error: Expected ';'\n");
                exit(1);
            }

            return print;
        } else {
            fprintf(stderr, "Syntax Error: Expected '('\n");
            exit(1);
        }
    } else {
        fprintf(stderr, "Syntax Error: Unknown statement at token '%s'\n", current->token.lexeme);
        exit(1);
    }

    return NULL;
}


ASTNode* parse_expression() {
    ASTNode* parse_term();
    while (current != NULL && current->token.type == TOKEN_PLUS) {
        advance();
        ASTNode* right = parse_term();
        op->op = strdup("+");
        add_child(op, left);
        add_child(op, right);
        left = op;
    }

    return left;
}


ASTNode* parse_term() {
    if(current->token.type == TOKEN_NUMBER ) {
        ASTNode* num = create_node(AST_LITERAL);
        num->value = current->token.value;
        advance();
        return num;
    } else if (current->token.type == TOKEN_IDENTIFIER) {
        ASTNode* id = create_node(AST_IDENTIFIER);
        id->name = strdup(current->token.lexeme);
        advance();
        return id;
    } else {
        fprintf(stderr, "Syntax Error: Expected number or identifier\n");
        exit(1);
    }
}
