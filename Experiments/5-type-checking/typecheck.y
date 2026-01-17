%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yyerror(const char *s);
struct symtab {
    char name[20];
    char type[10];
} table[50];

int count = 0;

int lookup(char *name) {
    for (int i = 0; i < count; i++)
        if (strcmp(table[i].name, name) == 0)
            return i;
    return -1;
}

void insert(char *name, char *type) {
    if (lookup(name) == -1) {
        strcpy(table[count].name, name);
        strcpy(table[count].type, type);
        count++;
    } else {
        printf("Error: variable '%s' redeclared.\n", name);
    }
}

char* getType(char *t1, char *t2) {
    if (strcmp(t1, t2) == 0) return t1;
    if ((strcmp(t1, "float") == 0 && strcmp(t2, "int") == 0) ||
        (strcmp(t1, "int") == 0 && strcmp(t2, "float") == 0))
        return "float";
    return "error";
}

%}

%union {
    int ival;
    float fval;
    char *str;
}

%token <str> ID
%token <str> INT FLOAT
%token <ival> INT_NUM
%token <fval> FLOAT_NUM
%token ASSIGN SEMI OP

%type <str> expr type

%%

program : program stmt
        | stmt
        ;

stmt : type ID SEMI
        { insert($2, $1); }

     | ID ASSIGN expr SEMI
        {
           int pos = lookup($1);
           if (pos == -1)
               printf("Error: variable '%s' not declared.\n", $1);
           else {
               char *result = getType(table[pos].type, $3);
               if (strcmp(result, "error") == 0)
                   printf("Type Error: cannot assign %s to %s.\n", $3, table[pos].type);
               else
                   printf("Assignment valid: %s = %s\n", $1, $3);
           }
        }
     ;

type : INT   { $$ = "int"; }
     | FLOAT { $$ = "float"; }
     ;

expr : expr OP expr
        {
           $$ = getType($1, $3);
           if (strcmp($$, "error") == 0)
               printf("Type Error in expression.\n");
        }

     | ID
        {
           int pos = lookup($1);
           if (pos == -1) {
               printf("Error: variable '%s' undeclared.\n", $1);
               $$ = "error";
           } else
               $$ = table[pos].type;
        }

     | INT_NUM   { $$ = "int"; }
     | FLOAT_NUM { $$ = "float"; }
     ;

%%

int main() {
    printf("Enter declarations and expressions:\n");
    yyparse();
    return 0;
}

int yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
    return 0;
}
