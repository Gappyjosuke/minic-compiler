#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/ast.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.mc>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);

    char* input = malloc(length + 1);
    fread(input, 1, length, file);
    input[length] = '\0';
    fclose(file);
    
    //Lexical Analysis
    TokenNode* tokens = tokenize(input);
    print_tokens(tokens);

    //Parsing -> AST
    ASTNode* ast = parse_program(tokens);

    //Print AST (just debug-print)
    printf("\nAST:\n"):
    print_ast(ast);

    //cleanup
    free_ast(ast);
    free_tokens(tokens);
    free(input);

    return 0;
}
