/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3)
{
    AST* newNode;
    newNode = (AST*)calloc(1, sizeof(AST));
    newNode->type = type;
    newNode->symbol = symbol;
    newNode->son[0] = s0;
    newNode->son[1] = s1;
    newNode->son[2] = s2;
    newNode->son[3] = s3;
    return newNode;
}

void astPrint(AST* node, int level)
{
    if(!node) return;
    for(int i = 0; i < level; i++) fprintf(stderr, "::");
    fprintf(stderr, "AST(");
    switch(node->type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL");  break;
        case AST_ADD:    fprintf(stderr, "AST_ADD");     break;
        case AST_SUB:    fprintf(stderr, "AST_SUB");     break;
        default:         fprintf(stderr, "AST_UNKNOWN"); break;
    }
    if(node->symbol) fprintf(stderr, ",%s\n", node->symbol->text);
    else fprintf(stderr, ",0\n");

    for(int i = 0; i < MAX_SONS; i++) astPrint(node->son[i], level+1);
}