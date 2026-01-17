%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

int yylex(void);
int yyerror(const char *s);
%}

%union {
    float fval;
    char *sval;
}

%token <fval> INT_CONST FLOAT_CONST
%token <sval> ID
%token IF ELSE WHILE FOR RETURN
%token ASSIGN PLUS MINUS MUL DIV LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA
%token EQ NE GT LT GE LE

%type <fval> expr statement
%left PLUS MINUS
 
%left MUL DIV

%%

program:
    /* empty */
  | program statement
  ;

statement:
      expr SEMICOLON                     { printf("Result: %f\n", $1); }
    | ID ASSIGN expr SEMICOLON           { set_var($1, $3); free($1); }
    | IF LPAREN expr RPAREN statement_block { if($3) ; } 
    | IF LPAREN expr RPAREN statement_block ELSE statement_block { if($3) ; else ; }
    | WHILE LPAREN expr RPAREN statement_block { while($3) ; }
    | FOR LPAREN statement expr SEMICOLON expr RPAREN statement_block { ; } 
    ;

statement_block:
      LBRACE program RBRACE
    | statement
    ;

expr:
      expr PLUS expr      { $$ = $1 + $3; }
    | expr MINUS expr     { $$ = $1 - $3; }
    | expr MUL expr       { $$ = $1 * $3; }
    | expr DIV expr       { $$ = $1 / $3; }
    | expr GT expr       { $$ = $1 > $3; }
    | expr LT expr       { $$ = $1 < $3; }
    | expr GE expr       { $$ = $1 >= $3; }
    | expr LE expr       { $$ = $1 <= $3; }
    | expr EQ expr       { $$ = $1 == $3; }
    | expr NE expr       { $$ = $1 != $3; }
    
    | LPAREN expr RPAREN  { $$ = $2; }
 
    | ID                  { $$ = get_var_value($1); free($1); }
    | INT_CONST           { $$ = $1; }
    | FLOAT_CONST         { $$ = $1; }
    ;
    

%%

int main(void) {
    printf("Instructions:\n");
    printf("-------------------------------------------------\n");
    printf("1. Create a file named 'input.c' in the same folder.\n");
    printf("2. Write your control instrucations code inside 'input.c'.\n");
    printf("3. Save the file.\n");
    printf("4. Run this program using the command:\n");
    printf("       control.exe < input.c\n");
    printf("5. The program will read from 'input.c' and display the result.\n");
    printf("-------------------------------------------------\n");

    return yyparse();
}

int yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
    return 0;
} 
