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
    if (!name || strlen(name) >= 64 ) {
        runtime_error("Invalid variable name");
        return;
    }

    printf("Setting variable %s to %d\n", name, value);
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
    strncpy(new_var->name, name, 63);
    new_var->name[63] = '\0';
    new_var->next = symbol_table;
    symbol_table = new_var;
}

int get_variable(const char* name) {
    if (!symbol_table) {
        runtime_errorf("Undefined variable '%s' (empty symbol table)", name);
        return 0;
    }

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
        printf("NULL expression in eval_expr!\n");
        runtime_error("eval_expr called with NULL expression node");   
        return 0;
    }
    printf("Evaluating expression type %d\n", expr->type);
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
            if (!expr->binary_op.left || !expr->binary_op.right) {
             runtime_error("Missing operand in binary operation");
             return 0;
            }
            printf("Evaluating binary op: %d\n", expr->binary_op.op);
            int left = eval_expr(expr->binary_op.left);
            int right = eval_expr(expr->binary_op.right);

            switch (expr->binary_op.op) {
                case TOKEN_PLUS: return left + right;
                case TOKEN_MINUS: return left - right;
                case TOKEN_STAR: return left * right;
                case TOKEN_EQ:    return left == right;
                case TOKEN_NEQ:    return left != right;
                case TOKEN_LT:    return left < right;
                case TOKEN_LE:    return left <= right;
                case TOKEN_GT:    return left > right;
                case TOKEN_GE:    return left >= right;
                case TOKEN_SLASH:
                    if (right == 0) {
                        runtime_error("Division by zero");
                    }
                    return left / right;
                default:
                    printf("Failing operator: %d\n", expr->binary_op.op);
                    runtime_errorf("Unsupported binary operator: %d", expr->binary_op.op);
            }
        }

        default:
        runtime_errorf("Unknown expression type: %d (%s)", expr->type, ast_type_to_str(expr->type));

    }
    return 0;
}


void interpret(ASTNode* node) {
    if (!node) {
        printf("Empty AST\n");
        return; 
    }
    printf("Starting interpretation...\n");
    while (node) {
        printf("Current node type: %d\n", node->type);
        switch (node->type) {
            case AST_VAR_DECL:
                printf("Processing declaration of %s\n", node->var_decl.name);
                set_variable(node->var_decl.name, eval_expr(node->var_decl.value));
                break;
            case AST_ASSIGN:
             set_variable(node->assign.name, eval_expr(node->assign.value));
            break;            
            case AST_PRINT:
                if (!node->print.expression) {
                    runtime_error("NULL expression in print");
                    break;
                }

                printf("%d\n", eval_expr(node->print.expression));
                break;
            default:
                runtime_errorf("Unknown statement type: %d (%s)", node->type, ast_type_to_str(node->type));
        }
        node = node->next;
    }
    printf("Interpretation completed successfully.\n");
}
