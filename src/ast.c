// ast.c: AST construction and helpers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

ASTNode* create_var_decl_node(const char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VAR_DECL;
    node->var_decl.name = strdup(name);
    node->var_decl.value = value;
    node->next = NULL;
    return node;
}

ASTNode* create_assign_node(const char* name, ASTNode* value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_ASSIGN;
    node->assign.name = strdup(name);
    node->assign.value = value;
    node->next = NULL;
    return node;
}

ASTNode* create_print_node(ASTNode* expr) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_PRINT;
    node->print.expression = expr;
    node->next = NULL;
    return node;
}

ASTNode* create_binary_op_node(TokenType op, ASTNode* left, ASTNode* right) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_BINARY_OP;
    node->binary_op.op = op;
    node->binary_op.left = left;
    node->binary_op.right = right;
    node->next = NULL;
    return node;
}

ASTNode* create_literal_node(int value) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_LITERAL;
    node->literal.value = value;
    node->next = NULL;
    return node;
}

ASTNode* create_variable_node(const char* name) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_VARIABLE;
    node->variable.name = strdup(name);
    node->next = NULL;
    return node;
}

void print_ast(ASTNode* node) {
    while (node) {
        switch (node->type) {
            case AST_VAR_DECL:
                printf("AST: VarDecl %s = ...\n", node->var_decl.name);
                break;
            case AST_ASSIGN:
                printf("AST: Assign %s = ...\n", node->assign.name);
                break;
            case AST_PRINT:
                printf("AST: Print (...)\n");
                break;
            case AST_BINARY_OP:
                printf("AST: BinaryOp +\n");
                break;
            case AST_LITERAL:
                printf("AST: Literal %d\n", node->literal.value);
                break;
            case AST_VARIABLE:
                printf("AST: Variable %s\n", node->variable.name);
                break;
        }
        node = node->next;
    }
}

void free_ast(ASTNode* node) {
    if (!node) return;
    free_ast(node->next);
    switch (node->type) {
        case AST_VAR_DECL:
            free(node->var_decl.name);
            free_ast(node->var_decl.value);
            break;
        case AST_ASSIGN:
            free(node->assign.name);
            free_ast(node->assign.value);
            break;
        case AST_PRINT:
            free_ast(node->print.expression);
            break;
        case AST_BINARY_OP:
            free_ast(node->binary_op.left);
            free_ast(node->binary_op.right);
            break;
        case AST_VARIABLE:
            free(node->variable.name);
            break;
        default:
            break;
    }
    free(node);
}
