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

// AST
// ----------
#define AST_SYMBOL 	1
// Mathematics
#define AST_ADD 	2
#define AST_SUB 	3
#define AST_DIV 	4
#define AST_MUL 	5
// Comparison
#define AST_LSR 	6
#define AST_GTR 	7
// Logic
#define AST_AND 	8
#define AST_OR  	9
#define AST_NOT 	10
// Operators
#define AST_LSE 	11
#define AST_GTE 	12
#define AST_EQU 	13
#define AST_DIF 	14
// Commands
#define AST_CMD 	15
#define AST_LCMD 	16
#define AST_LCMDT 	17
// Variables
#define AST_VAR 	18
#define AST_VECTOR 	19
// Message
#define AST_MSG		20
#define AST_MSGL	21
// Conditions
#define AST_IF		22
#define AST_IF_ELSE	23
#define AST_WHILE	24
// Functions
#define AST_READ	25
#define AST_PRINT	26
#define AST_RETURN	27
// Type
#define AST_CHAR	28
#define AST_FLOAT	29
#define AST_INT		30

#define AST_ASSIGN	31

#define AST_DECL	18
#define AST_BLCK	18
#define AST_PROGRAM 18

typedef struct ast_node
{
    int type;
    HASH_NODE* symbol;
    struct ast_node *son[MAX_SONS];
} AST;

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3);
void astPrint(AST* node, int level);
void astDecompile(AST *node);
