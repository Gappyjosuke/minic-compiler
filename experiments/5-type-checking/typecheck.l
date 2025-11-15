%{
#include "typecheck.tab.h"
#include <string.h>
%}

%%
"int"      { return INT; }
"float"    { return FLOAT; }
[0-9]+"."[0-9]+   { yylval.fval = atof(yytext); return FLOAT_NUM; }
[0-9]+            { yylval.ival = atoi(yytext); return INT_NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return ID; }
"="        { return ASSIGN; }
";"        { return SEMI; }
[+\-*/]    { return OP; }
[ \t\n]+   { /* skip whitespace */ }
.          { /* ignore invalid characters */ }
%%
int yywrap() { return 1; }
