/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER
#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

void check_and_set_declarations(AST *node);
void check_undeclared();

#endif