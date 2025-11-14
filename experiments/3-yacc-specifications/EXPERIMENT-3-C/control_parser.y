%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
int yyerror(const char *s);
%}

%token IF ELSE FOR WHILE DO SWITCH OTHER

%%

start:
      controls
    ;

controls:
      control
    | controls control
    ;

control:
      IF      { printf("Control Structure: IF\n"); }
    | ELSE    { printf("Control Structure: ELSE\n"); }
    | FOR     { printf("Control Structure: FOR\n"); }
    | WHILE   { printf("Control Structure: WHILE\n"); }
    | DO      { printf("Control Structure: DO\n"); }
    | SWITCH  { printf("Control Structure: SWITCH\n"); }
    | OTHER   { /* ignore non-control words */ }
    ;

%%

int main() {
    printf("Enter C code (press Ctrl+Z then Enter to finish):\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}
