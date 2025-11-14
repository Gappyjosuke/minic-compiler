%{
#include "control_parser.tab.h"
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
"for"       { return FOR; }
"while"     { return WHILE; }
"do"        { return DO; }
"switch"    { return SWITCH; }

[ \t\n]+    { /* skip spaces */ }
.           { return OTHER; }
%%

int yywrap(void) { return 1; }
