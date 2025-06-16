// parser.c: Parses tokens into AST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "parser.h"
#include "ast.h"
#include "error.h"
#include "lexer.h"

static TokenNode* current;



static ASTNode* parse_expression(); // entry
static ASTNode* parse_equality();   // ==, !=
static ASTNode* parse_relational(); // <, >, <=, >=
static ASTNode* parse_addition();   // +, -
static ASTNode* parse_term();       // *, /
static ASTNode* parse_unary();      // -x
static ASTNode* parse_primary();    // literals, identifiers, ()
static ASTNode* parse_statement();  // statement parser
static ASTNode* parse_factor();     // wraps parse_unary


// Advance to next token
static void advance() {
    if (current == NULL || current->next == NULL) {
        current = NULL;  // Set to NULL instead of error
        return;
    }
    if (!current) return;
    current = current->next;
}


bool match(TokenType type) {
    if (!current) return false;
    if (current->token.type == type) {
        advance();
        return true;
    }
    return false;
}



// Entry point
ASTNode* parse_program(TokenNode* tokens) {
    current = tokens;
    ASTNode* head = NULL;
    ASTNode* tail = NULL;

    while (current != NULL && current->token.type != TOKEN_EOF) {
        ASTNode* stmt = parse_statement();
        if (stmt == NULL) break;  // Stop if statement parsing fails

        if (head == NULL) {
            head = tail = stmt;
        } else {
            tail->next = stmt;
            tail = stmt;
        }
        
        // Add explicit check after each statement
        if (current == NULL || current->token.type == TOKEN_EOF) {
            break;
        }
    }
    return head;
}

// statement → declaration 

// ---- Expression parsing ----

static ASTNode* parse_expression() {
    return parse_equality();
}

static ASTNode* parse_equality() {
    ASTNode* node = parse_relational();

    while (current->token.type == TOKEN_EQ || current->token.type == TOKEN_NEQ) {
        TokenType op = current->token.type;
        advance();  // consume == or !=

        ASTNode* right = parse_relational();

        // Replace with:
        
        node = create_binary_op_node(op, node, right);
        
    }

    return node;
}


static ASTNode* parse_relational() {
    ASTNode* left = parse_addition();

    while (current->token.type == TOKEN_LT || current->token.type == TOKEN_LE ||
           current->token.type == TOKEN_GT || current->token.type == TOKEN_GE) {
        TokenType op = current->token.type;
        advance();  // consume <, <=, >, >=

        ASTNode* right = parse_addition();

        left = create_binary_op_node(op, left, right);
    }

    return left;
}
 
static ASTNode* parse_addition() {
    ASTNode* left = parse_term();
    while (current->token.type == TOKEN_PLUS || current->token.type == TOKEN_MINUS) {
        TokenType op = current->token.type;
        advance(); // consume + or -
        ASTNode* right = parse_term();
        left = create_binary_op_node(op, left, right);
    }
    return left;
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
    if(current == NULL){
        parser_error("unexpected end of input in primary expression");
    }
    
    if (!current) {
        fprintf(stderr, "Unexpected end of input\n");
        exit(1);
    }
    
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
            parser_errorf(current->token, "Expected ')' after expression, but got '%s'", token_type_to_string(current->token.type));
        }
        return expr;
    }

    parser_errorf(current->token, "Unexpected token '%s' in expression", current->token.lexeme);
    return NULL;
}

ASTNode* parse_statement() {
    if (current == NULL || current->token.type == TOKEN_EOF) {
        return NULL;  // Gracefully handle EOF
    }
    if (current->token.type == TOKEN_INT || current->token.type == TOKEN_LET) {
        advance();
        if (!current || current->token.type != TOKEN_IDENTIFIER) {
            parser_errorf(current->token, "Expected identifier after 'let'", token_type_to_string(current->token.type));
            return NULL;
        }
        char* name = strdup(current->token.lexeme);
        advance();

        if (!match(TOKEN_ASSIGN)) {
            parser_error_free_str(current->token, name, "Expected '=' after identifier");
            return NULL;  
        }

        ASTNode* value = parse_expression();

        if (!match(TOKEN_SEMICOLON)) {
            free(name);
            parser_errorf(current->token, "Expected ';' after declaration, but got '%s'", token_type_to_string(current->token.type));
            return NULL;
        }

        return create_var_decl_node(name, value);
        
    }
    

    if (current->token.type == TOKEN_IDENTIFIER) {
        char* name = strdup(current->token.lexeme);
        advance();

        if (!match(TOKEN_ASSIGN)) {
            parser_error_free_str(current->token, name, "Expected '=' after identifier");
            return NULL;
        }
        advance();

        ASTNode* value = parse_expression();

        if (!match(TOKEN_SEMICOLON)) {
            free(name);
            parser_errorf(current->token, "Expected ';' after assignment, but got '%s'", token_type_to_string(current->token.type));
            return NULL;
        }

        return create_assign_node(name, value);
    }

    if (match(TOKEN_PRINT)) {
        if (!match(TOKEN_LPAREN)) {
            parser_errorf(current->token, "Expected '(' after 'print', but got '%s'", token_type_to_string(current->token.type));
        }

        if (current == NULL){
            parser_error("Unexpected EOF after print");
        }

        ASTNode* expr = parse_expression();

        if (!match(TOKEN_RPAREN)) {
            parser_errorf(current->token, "Expected ')' after print expression, but got '%s'", token_type_to_string(current->token.type));

        }
        

        if (!match(TOKEN_SEMICOLON)) {
            parser_errorf(current->token, "Expected ';' after print statement, but got '%s'", token_type_to_string(current->token.type));

        }
        

        return create_print_node(expr);
    }

    parser_errorf(current->token, "Unknown statement at token '%s'", current->token.lexeme);
    return NULL;
}



static ASTNode* parse_factor() {
    return parse_unary();  // Might be unary or primary (like a number or (expr))
}
