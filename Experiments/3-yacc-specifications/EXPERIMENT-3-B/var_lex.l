%{
#include "var_parser.tab.h"
#include <string.h>
%}

%%
[a-zA-Z_][a-zA-Z0-9_]*   { return IDENTIFIER; }
[ \t\n]+                 { /* ignore spaces */ }
.                        { return INVALID; }
%%

int yywrap(void) { return 1; }
