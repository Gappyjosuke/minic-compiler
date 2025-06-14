#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.minic>\n", argv[0]);
        return 1;
    }

    const char* filename = argv[1];
    TokenNode* tokens = tokenize_file(filename);

    // Optional: Print tokens
    for (TokenNode* t = tokens; t != NULL; t = t->next) {
        printf("Token: %-12s Lexeme: %-10s Value: %d\n",
               token_type_to_string(t->token.type),
               t->token.lexeme,
               t->token.value);
    }
    
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    //Parsing -> AST
    ASTNode* ast = parse_program(tokens);

    //Print AST (just debug-print)
    printf("\nAST:\n"):
    print_ast(ast);

    //cleanup
    free_ast(ast);
    free_tokens(tokens);

    return 0;
}
