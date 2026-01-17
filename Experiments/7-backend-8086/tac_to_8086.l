%{
#include "tac_to_8086.tab.h"
#include <string.h>
#include <ctype.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { 
    strcpy(yylval.strval, yytext); 
    return ID; 
}

[0-9]+                  { 
    strcpy(yylval.strval, yytext); 
    return NUMBER; 
}

"+"|"-"|"*"|"/"         { 
    strcpy(yylval.strval, yytext); 
    return OPERATOR; 
}

"=="|"!="|"<"|">"|"<="|">=" { 
    strcpy(yylval.strval, yytext); 
    return RELOP; 
}

"="                     { 
    strcpy(yylval.strval, yytext); 
    return ASSIGNOP; 
}

\n                      { return NEWLINE; }
[ \t]+                  ; /* Skip whitespace */
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}