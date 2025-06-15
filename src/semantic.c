#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "ast.h"
#include "error.h"

typedef struct Symbol {
    char* name;
    struct Symbol* next;
} Symbol;

static Symbol* symbol_table = NULL;

static int is_declared(const char* name) {
    for (Symbol* s = symbol_table; s != NULL; s = s->next) {
        if (strcmp(s->name, name) == 0) return 1;
    }
    return 0;
}

static void declare(const char* name) {
    Symbol* new_sym = malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->next = symbol_table;
    symbol_table = new_sym;
}

static void check_node(ASTNode* node) {
    while (node != NULL) {
        switch (node->type) {
            case AST_VAR_DECL:
                if (is_declared(node->var_decl.name)) {
                    fprintf(stderr, "[Semantic Error] Variable '%s' already declared\n", node->var_decl.name);
                    exit(1);
                }
                declare(node->var_decl.name);
                check_node(node->var_decl.value);
                break;

            case AST_ASSIGN:
                if (!is_declared(node->assign.name)) {
                    fprintf(stderr, "[Semantic Error] Variable '%s' used before declaration\n", node->assign.name);
                    exit(1);
                }
                check_node(node->assign.value);
                break;

            case AST_PRINT:
                check_node(node->print.expression);
                break;

            case AST_BINARY_OP:
                check_node(node->binary_op.left);
                check_node(node->binary_op.right);
                break;

            case AST_UNARY_OP:
                check_node(node->unary_op.operand);
                break;

            case AST_VARIABLE:
                if (!is_declared(node->variable.name)) {
                    fprintf(stderr, "[Semantic Error] Variable '%s' used before declaration\n", node->variable.name);
                    exit(1);
                }
                break;

            default:
                break;
        }
        node = node->next;
    }
}

void perform_semantic_analysis(ASTNode* root) {
    check_node(root);
}
