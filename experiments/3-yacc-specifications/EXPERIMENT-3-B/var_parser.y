%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token IDENTIFIER INVALID

%%

start:
      IDENTIFIER { printf("Valid variable name.\n"); }
    | INVALID    { printf("Invalid variable name.\n"); }
    ;

%%

int main() {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}
