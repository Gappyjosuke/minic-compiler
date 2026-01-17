%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
%}
%%
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"for"           { return FOR; }
"return"        { return RETURN; }

[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT_CONST; }
[0-9]+          { yylval.fval = atoi(yytext); return INT_CONST; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return ID; }
"="             { return ASSIGN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACE; }
"}"             { return RBRACE; }
";"             { return SEMICOLON; }
","             { return COMMA; }
"=="            { return EQ; }
"!="            { return NE; }
">"             { return GT; }
"<"             { return LT; }
">="            { return GE; }
"<="            { return LE; }

[ \t\n]+        ;   // skip whitespace
.               { return yytext[0]; }
%%
int yywrap(void) { return 1; }
