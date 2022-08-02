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

#define MAX_SONS 4

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 3
#define AST_DIV 4
#define AST_MUL 5
#define AST_LSR 6
#define AST_GTR 7
#define AST_AND 8
#define AST_OR  9
#define AST_NOT 10
#define AST_LSE 11
#define AST_GTE 12
#define AST_EQU 13
#define AST_DIF 14
#define AST_LCD 15

typedef struct ast_node
{
    int type;
    HASH_NODE* symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST* node, int level);