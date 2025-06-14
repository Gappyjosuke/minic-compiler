#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"
#include "../include/parser.h"

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

    TokenNode* tokens = tokenize(input);
    print_tokens(tokens);  // Optional: comment this if not needed

    parse_program(tokens); // Stubbed in parser.c

    free_tokens(tokens);
    free(input);

    return 0;
}
