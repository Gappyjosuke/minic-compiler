// parser.c: Parses tokens into AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ast.h"
#include "error.h"

static TokenNode* current;

// ---- Expression Parsing with Precedence ----

static ASTNode* parse_expression(); // entry
static ASTNode* parse_term();       // + -
static ASTNode* parse_unary();      // -x
static ASTNode* parse_primary();    // numbers, variables, (expr)

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
        if (!current || current->token.type != TOKEN_IDENTIFIER) {
            parser_error("Expected identifier after 'let'");
        }
            char* name = strdup(current->token.lexeme);
            advance();

            if (!match(TOKEN_ASSIGN)) {
                parser_error("Expected '=' after identifier");
            }

            ASTNode* value = parse_expression();

            if (!match(TOKEN_SEMICOLON)) {
                parser_error("Expected ';'");
            }

            return create_var_decl_node(name, value);
        
    }
    

    if (current->token.type == TOKEN_IDENTIFIER) {
        char* name = strdup(current->token.lexeme);
        advance();

        if (!match(TOKEN_ASSIGN)) {
            parser_errorf("Expected '=' after identifier '%s'", name);
        }

        ASTNode* value = parse_expression();

        if (!match(TOKEN_SEMICOLON)) {
            parser_error("Expected ';'");
        }

        return create_assign_node(name, value);
    }

    if (match(TOKEN_PRINT)) {
        if (!match(TOKEN_LPAREN)) {
            parser_error("Expected '('");
        }

        ASTNode* expr = parse_expression();

        if (!match(TOKEN_RPAREN)) {
            parser_error("Expected ')'");

        }

        if (!match(TOKEN_SEMICOLON)) {
            parser_error("Expected ';'");

        }

        return create_print_node(expr);
    }

    parser_errorf("Unknown statement at token '%s'", current->token.lexeme);

}



static ASTNode* parse_expression() {
    ASTNode* left = parse_term();
    while (current->token.type == TOKEN_PLUS || current->token.type == TOKEN_MINUS) {
        TokenType op = current->token.type;
        advance();
        ASTNode* right = parse_term();
        left = create_binary_op_node(op,left,right);
    }

    return left;
}

static ASTNode* parse_factor() {
    return parse_unary();  // Might be unary or primary (like a number or (expr))
}



static ASTNode* parse_term() {
    ASTNode* left = parse_factor();
    while (current->token.type == TOKEN_STAR || current->token.type == TOKEN_SLASH) {
        TokenType op = current->token.type;
        advance();
        ASTNode* right = parse_factor();
        left = create_binary_op_node(op, left, right);
    }
    return left;
}



// parse_unary → handles unary minus: -x
static ASTNode* parse_unary() {
    if (current->token.type == TOKEN_MINUS || current->token.type == TOKEN_PLUS) {
        TokenType op = current->token.type;
        advance();
        ASTNode* operand = parse_unary(); // recursive for chains like --x
        return create_unary_op_node(op, operand);
    }
   return parse_primary();
}

// parse_primary → numbers, identifiers, (expr)
static ASTNode* parse_primary() {
    if (current->token.type == TOKEN_NUMBER) {
        int val = current->token.value;
        advance();
        return create_literal_node(val);
    }
    if (current->token.type == TOKEN_IDENTIFIER) {
        char* name = strdup(current->token.lexeme);
        advance();
        return create_variable_node(name);
    }
    if (match(TOKEN_LPAREN)) {
        ASTNode* expr = parse_expression();
        if (!match(TOKEN_RPAREN)) {
            fprintf(stderr, "Syntax Error: Expected ')'\n");
            exit(1);
        }
        return expr;
    }

    fprintf(stderr, "Syntax Error: Unexpected token '%s'\n", current->token.lexeme);
    exit(1);
}

