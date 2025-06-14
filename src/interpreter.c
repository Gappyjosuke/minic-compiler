#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/ast.h"

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
    switch (expr->type) {
        case AST_NUMBER_LITERAL:
            return expr->number.value;
        case AST_IDENTIFIER:
            return get_variable(expr->identifier.name);
        case AST_BINARY_EXPR: {
            int left = eval_expr(expr->binary.left);
            int right = eval_expr(expr->binary.right);
            if (strcmp(expr->binary.op, "+") == 0)
                return left + right;
            fprintf(stderr, "Unsupported operator: %s\n", expr->binary.op);
            exit(1);
        }
        default:
            fprintf(stderr, "Unknown expression type\n");
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
