// ast.c: AST construction and helpers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

const char* ast_type_to_str(ASTNodeType type) {
    switch (type) {
        case AST_VAR_DECL: return "VAR_DECL";
        case AST_ASSIGN: return "ASSIGN";
        case AST_PRINT: return "PRINT";
        case AST_BINARY_OP: return "BINARY_OP";
        case AST_UNARY_OP: return "UNARY_OP";
        case AST_LITERAL: return "LITERAL";
        case AST_VARIABLE: return "VARIABLE";
        default: return "UNKNOWN";
    }
}

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
    printf("[DEBUG] Created binary op node, type = %d, op = %d\n", node->type, op);
    return node;
}

ASTNode* create_unary_op_node(TokenType op, ASTNode* operand) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_UNARY_OP;
    node->unary_op.op = op;
    node->unary_op.operand = operand;
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
                print_ast(node->var_decl.value);
                break;
            case AST_ASSIGN:
                printf("AST: Assign %s = ...\n", node->assign.name);
                print_ast(node->assign.value);
                break;
            case AST_PRINT:
                printf("AST: Print ");
                print_ast(node->print.expression);
                break;
            case AST_BINARY_OP:
                printf("BinaryOp(%s)\n",
                 node->binary_op.op == TOKEN_PLUS ? "+" :
                 node->binary_op.op == TOKEN_MINUS ? "-" :
                 node->binary_op.op == TOKEN_STAR ? "*" :
                 node->binary_op.op == TOKEN_SLASH ? "/" : "?");
                printf("  Left: ");
                print_ast(node->binary_op.left);
                printf("  Right: ");
                print_ast(node->binary_op.right);
                break;
            case AST_LITERAL:
                printf("AST: Literal %d\n", node->literal.value);
                break;
            case AST_VARIABLE:
                printf("AST: Variable %s\n", node->variable.name);
                break;
            case AST_UNARY_OP:
                printf("UnaryOp(%s)\n", node->unary_op.op == TOKEN_MINUS ? "-" : "+");
                print_ast(node->unary_op.operand);
                break;
            default:
            printf("Unknown AST Node Type: %d (%s)\n", node->type, ast_type_to_str(node->type));
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
