%{
#include "arith_parser.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+\.[0-9]+  { yylval.fval = atof(yytext); return FLOAT_CONST; }
[0-9]+          { yylval.fval = atoi(yytext); return INT_CONST; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return MUL; }
"/"             { return DIV; }
[ \t\n]+        { /* skip whitespace */ }
.               { return yytext[0]; }
%%

int yywrap(void) { return 1; }
