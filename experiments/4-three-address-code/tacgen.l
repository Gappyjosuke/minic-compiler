%{
#include "tacgen.tab.h"
#include <stdlib.h>
#include <string.h>
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
[0-9]+      { yylval.str = strdup(yytext); return NUM; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return ID; }
"=="        { return EQ; }
"!="        { return NE; }
">="        { return GE; }
"<="        { return LE; }
">"         { return GT; }
"<"         { return LT; }
"="         { return ASSIGN; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MUL; }
"/"         { return DIV; }
"("         { return LPAREN; }
")"         { return RPAREN; }
";"         { return SEMI; }
[ \t\n]+    ;  // ignore whitespace
.           ;
%%

int yywrap(void) { return 1; }
