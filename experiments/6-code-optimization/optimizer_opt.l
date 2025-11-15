%{
#include "optimizer_opt.tab.h"
#include <string.h>
#include <stdlib.h>

typedef struct Node Node;
%}

%%

[0-9]+                  { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*  { strcpy(yylval.id, yytext); return ID; }

"="     { return ASSIGN; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MUL; }
"/"     { return DIV; }
";"     { return SEMI; }

[ \t\n]+    ;  // Ignore whitespace
.           { return yytext[0]; }

%%

int yywrap() { 
    return 1; 
}