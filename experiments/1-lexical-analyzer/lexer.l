%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count = 0;
char symtab[100][100];

void insertSymbol(char *sym) {
    for (int i = 0; i < count; i++)
        if (!strcmp(symtab[i], sym)) return;
    strcpy(symtab[count++], sym);
}

void printSymbolTable() {
    printf("\nSymbol Table:\n");
    for (int i = 0; i < count; i++)
        printf("%s\n", symtab[i]);
}
%}
%%
"int"|"float"|"char"    { printf("Keyword: %s\n", yytext); }
"="|"+"|"-"|"*"|"/"     { printf("Operator: %s\n", yytext); }
[0-9]+\.[0-9]+          { printf("Float Number: %s\n", yytext); }
[0-9]+                  { printf("Integer Number: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*  { printf("Identifier: %s\n", yytext); insertSymbol(yytext); }
[ \t\n]+                { /* skip whitespace */ }
.                       { printf("Unknown token: %s\n", yytext); }
%%
int yywrap(void) { return 1; }

int main() {
    printf("Enter your C code (Ctrl+Z to end input):\n\n");
    yylex();
    printSymbolTable();
    return 0;
}
