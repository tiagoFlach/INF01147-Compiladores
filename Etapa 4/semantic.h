/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */

#pragma once
#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

void check_and_set_declarations(AST *node);
void check_undeclared();
void check_nature(AST *node);
void check_datatype(AST *node);
void check_function_arguments(AST *node);
void check_vector(AST *node);
void check_return(AST *node);
void check_index(AST *node);