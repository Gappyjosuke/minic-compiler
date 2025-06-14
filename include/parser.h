#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"

ASTNode* parse_program(TokenNode* tokens);

#endif
