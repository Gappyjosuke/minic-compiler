#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/interpreter.h"
#include "../include/ast.h"
#include "../include/lexer.h"
#include "../include/error.h"


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
    if (!new_var) {
        runtime_error("Out of memory when allocating new variable");
    }
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
    runtime_errorf("Undefined variable '%s'", name);
    return 0;
}

int eval_expr(ASTNode* expr) {
    if (!expr) {
        runtime_error("eval_expr called with NULL expression node");   
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
                        runtime_error("Division by zero");
                    }
                    return left / right;
                default:
                    runtime_errorf("Unsupported binary operator: %d", expr->binary_op.op);
            }
        }

        default:
        runtime_errorf("Unknown expression type: %d (%s)", expr->type, ast_type_to_str(expr->type));

    }
    return 0;
}



void interpret(ASTNode* node) {
    while (node) {
        switch (node->type) {
            case AST_VAR_DECL:
                set_variable(node->var_decl.name, eval_expr(node->var_decl.value));
                break;
            case AST_ASSIGN:
             set_variable(node->assign.name, eval_expr(node->assign.value));
            break;            
            case AST_PRINT:
                printf("%d\n", eval_expr(node->print.expression));
                break;
            default:
                runtime_errorf("Unknown statement type: %d (%s)", node->type, ast_type_to_str(node->type));
        }
        node = node->next;
    }
}
