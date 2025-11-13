%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count = 0;
char symtab[100][100];

void insertSymbol(char *sym) {
    if (!strcmp(sym,"int") || !strcmp(sym,"float") || !strcmp(sym,"char") ||
        !strcmp(sym,"if") || !strcmp(sym,"else") || !strcmp(sym,"while") ||
        !strcmp(sym,"for") || !strcmp(sym,"do") || !strcmp(sym,"switch") ||
        !strcmp(sym,"case") || !strcmp(sym,"return") || !strcmp(sym,"main") ||
        !strcmp(sym,"printf") || !strcmp(sym,"scanf"))
        return;
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
"int"|"float"|"char"|"if"|"else"|"while"|"for"|"do"|"switch"|"case"|"return"|"main" { printf("Keyword: %-10s\n", yytext); }
"=="|"!="|"<="|">="|"<"|">" { printf("Relational Operator: %-5s\n", yytext); }
"="|"+"|"-"|"*"|"/" { printf("Operator: %-5s\n", yytext); }
"(" { printf("Special Symbol: ( \n"); }
")" { printf("Special Symbol: ) \n"); }
"{" { printf("Special Symbol: { \n"); }
"}" { printf("Special Symbol: } \n"); }
";" { printf("Special Symbol: ; \n"); }
"," { printf("Special Symbol: , \n"); }
[0-9]+\.[0-9]+ { printf("Float Number: %-10s\n", yytext); }
[0-9]+         { printf("Integer Number: %-10s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %-10s\n", yytext); insertSymbol(yytext); }
\"([^\"\n]|\\.)*\" { printf("String: %s\n", yytext); }
[ \t\n]+ { }
. { printf("Unknown token: %s\n", yytext); }
%%

int yywrap(void) { return 1; }

int main() {
    printf("Enter your C code (Ctrl+Z to end input):\n\n");
    yylex();
    printSymbolTable();
    return 0;
}
