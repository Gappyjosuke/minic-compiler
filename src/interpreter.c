#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/ast.h"
#include "../include/lexer.h"


typedef struct Variable {
    char name[64];
    int value;
    struct Variable* next;
} Variable;

static Variable* symbol_table = NULL;

void set_variable(const char* name, int value) {
    Variable* v = symbol_table;
    while (v) {
        if (strcmp(v->name, name) == 0) {
            v->value = value;
            return;
        }
        v = v->next;
    }
    Variable* new_var = malloc(sizeof(Variable));
    strcpy(new_var->name, name);
    new_var->value = value;
    new_var->next = symbol_table;
    symbol_table = new_var;
}

int get_variable(const char* name) {
    Variable* v = symbol_table;
    while (v) {
        if (strcmp(v->name, name) == 0)
            return v->value;
        v = v->next;
    }
    fprintf(stderr, "Runtime Error: Undefined variable '%s'\n", name);
    exit(1);
}
int eval_expr(ASTNode* expr) {
    if (!expr) {
        fprintf(stderr, "eval_expr called with NULL!\n");
        exit(1);
    }
    
    if (expr == NULL) {
     fprintf(stderr, "Runtime Error: NULL expression node\n");
     exit(1);
    }

    if (expr->type < 0 || expr->type > AST_VARIABLE) {
        fprintf(stderr, "[SANITY] Invalid expr->type: %d (%s)\n", expr->type, ast_type_to_str(expr->type));
    }

    switch (expr->type) {
        case AST_LITERAL:
            return expr->literal.value;

        case AST_VARIABLE:
            return get_variable(expr->variable.name);

        case AST_UNARY_OP: {
            int val = eval_expr(expr->unary_op.operand);
            return (expr->unary_op.op == TOKEN_MINUS) ? -val : val;
        }

        case AST_BINARY_OP: {
            int left = eval_expr(expr->binary_op.left);
            int right = eval_expr(expr->binary_op.right);

            switch (expr->binary_op.op) {
                case TOKEN_PLUS: return left + right;
                case TOKEN_MINUS: return left - right;
                case TOKEN_STAR: return left * right;
                case TOKEN_SLASH:
                    if (right == 0) {
                        fprintf(stderr, "Division by zero\n");
                        exit(1);
                    }
                    return left / right;
                default:
                    fprintf(stderr, "Unsupported binary operator: %d\n", expr->binary_op.op);
                    exit(1);
            }
        }

        default:
            fprintf(stderr, "Unknown expression type: %d (%s) (maybe uninitialized or parser bug)\n",
                expr->type, ast_type_to_str(expr->type));
            fprintf(stderr, "[DEBUG] Raw node pointer: %p\n", (void*)expr);
            exit(1);
    }
}



void interpret(ASTNode* node) {
    while (node) {
        switch (node->type) {
            case AST_VAR_DECL:
                set_variable(node->var_decl.name, eval_expr(node->var_decl.value));
                break;
            case AST_PRINT:
                printf("%d\n", eval_expr(node->print.expression));
                break;
            default:
                fprintf(stderr, "Unknown statement type\n");
                exit(1);
        }
        node = node->next;
    }
}
