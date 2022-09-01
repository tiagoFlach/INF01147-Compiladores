/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 */

#pragma once
#include "hash.h"
#include "ast.h"

extern int SemanticErrors;

int get_semantic_errors();
int get_datatype(int ast_const);

int is_number(AST *node);

void check_and_set_declarations(AST *node);
void check_undeclared();
void check_operands(AST *node);
void check_vec_index(AST *node);
void check_vec(AST *node, int vsize, int current, int dtype);
void check_return(AST *node, int ret);
void check_function_arguments(AST *node);
void check_nature(AST *node);
void check_datatype(AST *node);

void check_semantic(AST *node);