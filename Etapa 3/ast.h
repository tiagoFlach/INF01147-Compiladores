/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */
#pragma once

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2

typedef struct ast_node
{
    int type;
    HASH_NODE* symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST* node);