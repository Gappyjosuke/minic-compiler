%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%union {
    float fval;
}

%token <fval> INT_CONST FLOAT_CONST
%token PLUS MINUS MUL DIV LPAREN RPAREN

%type <fval> expr

%left PLUS MINUS
%left MUL DIV

%%
program:
      expr { printf("Result: %f\n", $1); }
    ;

expr:
      expr PLUS expr     { $$ = $1 + $3; }
    | expr MINUS expr    { $$ = $1 - $3; }
    | expr MUL expr      { $$ = $1 * $3; }
    | expr DIV expr      { $$ = $1 / $3; }
    | LPAREN expr RPAREN { $$ = $2; }

    | INT_CONST        { $$ = $1; }
    | FLOAT_CONST      { $$ = $1; }
    ;

%%

int main() {
    printf("Enter arithmetic expression:\n");
    printf("-------------------------------------------------\n");
    printf("1. Type your arithmetic expression.\n");
    printf("2. Press Enter.\n");
    printf("3. Then press Ctrl+Z and again press Enter to show the result.\n");
    printf("-------------------------------------------------\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
    return 0;
}
