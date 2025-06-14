// include/ast.h
#ifndef AST_H
#define AST_H

#include "lexer.h"

typedef enum {
    AST_VAR_DECL,
    AST_ASSIGN,
    AST_PRINT,
    AST_BINARY_OP,
    AST_LITERAL,
    AST_VARIABLE,
    AST_UNARY_OP
} ASTNodeType;

const char* ast_type_to_str(ASTNodeType type);


typedef struct ASTNode {
    ASTNodeType type;

    union {
        struct {
            char* name;
            struct ASTNode* value;
        } var_decl;

        struct {
            char* name;
            struct ASTNode* value;
        } assign;

        struct {
            TokenType op;
            struct ASTNode* operand;
        } unary_op;
            
        struct {
            struct ASTNode* expression;
        } print;

        struct {
            TokenType op; // e.g. TOKEN_PLUS
            struct ASTNode* left;
            struct ASTNode* right;
        } binary_op;

        struct {
            int value;
        } literal;

        struct {
            char* name;
        } variable;
    };
    
    struct ASTNode* next; // For chaining statements
} ASTNode;

ASTNode* create_var_decl_node(const char* name, ASTNode* value);
ASTNode* create_assign_node(const char* name, ASTNode* value);
ASTNode* create_print_node(ASTNode* expr);
ASTNode* create_binary_op_node(TokenType op, ASTNode* left, ASTNode* right);
ASTNode* create_literal_node(int value);
ASTNode* create_variable_node(const char* name);
ASTNode* create_unary_op_node(TokenType op, ASTNode* operand);
void print_ast(ASTNode* root);
void free_ast(ASTNode* node);

#endif
