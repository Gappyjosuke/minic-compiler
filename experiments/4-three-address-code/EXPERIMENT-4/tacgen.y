%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tempCount = 1, labelCount = 1;
char* newTemp();
char* newLabel();

void emit(const char *s);

int yylex(void);
int yyerror(const char *s);
%}

%union {
    char *str;
}

%token <str> ID NUM
%token IF ELSE
%token ASSIGN PLUS MINUS MUL DIV
%token EQ NE LT GT LE GE
%token LPAREN RPAREN SEMI
%type <str> expr stmt condition

%left PLUS MINUS
%left MUL DIV
%left EQ NE LT GT LE GE

%%
program:
    /* empty */
  | program stmt
  ;

stmt:
    ID ASSIGN expr SEMI
        {
            printf("%s = %s\n", $1, $3);
        }
  | IF LPAREN condition RPAREN stmt
        {
            char *L1 = newLabel(), *L2 = newLabel();
            printf("if %s goto %s\n", $3, L1);
            printf("goto %s\n", L2);
            printf("%s:\n", L1);
            // then-part already printed
            printf("%s:\n", L2);
        }
  | IF LPAREN condition RPAREN stmt ELSE stmt
        {
            char *L1 = newLabel(), *L2 = newLabel(), *L3 = newLabel();
            printf("if %s goto %s\n", $3, L1);
            printf("goto %s\n", L2);
            printf("%s:\n", L1);
            // then-part
            printf("%s:\n", L2);
            // else-part
            printf("%s:\n", L3);
        }
  ;

condition:
    expr LT expr    { $$ = newTemp(); printf("%s = %s < %s\n", $$, $1, $3); }
  | expr GT expr    { $$ = newTemp(); printf("%s = %s > %s\n", $$, $1, $3); }
  | expr LE expr    { $$ = newTemp(); printf("%s = %s <= %s\n", $$, $1, $3); }
  | expr GE expr    { $$ = newTemp(); printf("%s = %s >= %s\n", $$, $1, $3); }
  | expr EQ expr    { $$ = newTemp(); printf("%s = %s == %s\n", $$, $1, $3); }
  | expr NE expr    { $$ = newTemp(); printf("%s = %s != %s\n", $$, $1, $3); }
  ;

expr:
    expr PLUS expr  { $$ = newTemp(); printf("%s = %s + %s\n", $$, $1, $3); }
  | expr MINUS expr { $$ = newTemp(); printf("%s = %s - %s\n", $$, $1, $3); }
  | expr MUL expr   { $$ = newTemp(); printf("%s = %s * %s\n", $$, $1, $3); }
  | expr DIV expr   { $$ = newTemp(); printf("%s = %s / %s\n", $$, $1, $3); }
  | LPAREN expr RPAREN { $$ = $2; }
  | ID              { $$ = $1; }
  | NUM             { $$ = $1; }
  ;
%%
char* newTemp() {
    char *buf = malloc(8);
    sprintf(buf, "t%d", tempCount++);
    return buf;
}

char* newLabel() {
    char *buf = malloc(8);
    sprintf(buf, "L%d", labelCount++);
    return buf;
}

int yyerror(const char *s) {
    printf("Error: %s\n", s);
    return 0;
}

int main() {
    printf("Enter code (Ctrl+Z to stop):\n");
    yyparse();
    return 0;
}
