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
extern FILE *out;

AST* astCreate(int type, HASH_NODE* symbol, AST* s0, AST* s1, AST* s2, AST* s3)
{
    AST* newNode;
    newNode = (AST*) calloc(1, sizeof(AST));
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
    for(int i = 0; i < level; i++) fprintf(stderr, "..");
    fprintf(stderr, "AST(");
    switch(node->type)
    {
        case AST_SYMBOL: fprintf(stderr, "AST_SYMBOL");  break;
        case AST_ADD:    fprintf(stderr, "AST_ADD");     break;
        case AST_SUB:    fprintf(stderr, "AST_SUB");     break;
		case AST_DIV:    fprintf(stderr, "AST_DIV");     break;
		case AST_MUL:    fprintf(stderr, "AST_MUL");     break;
		case AST_LSR:    fprintf(stderr, "AST_LSR");     break;
		case AST_GTR:    fprintf(stderr, "AST_GTR");     break;
		case AST_AND:    fprintf(stderr, "AST_AND");     break;
		case AST_OR:     fprintf(stderr, "AST_OR");      break;
		case AST_NOT:    fprintf(stderr, "AST_NOT");     break;
		case AST_LSE:    fprintf(stderr, "AST_LSE");     break;
        case AST_GTE:    fprintf(stderr, "AST_GTE");     break;
		case AST_EQU:    fprintf(stderr, "AST_EQU");     break;
		case AST_DIF:    fprintf(stderr, "AST_DIF");     break;
		case AST_READ:   fprintf(stderr, "AST_READ");    break;
		case AST_PRINT:  fprintf(stderr, "AST_PRINT");   break;
		case AST_RETURN: fprintf(stderr, "AST_RETURN");  break;
		case AST_ASSIGN: fprintf(stderr, "AST_ASSIGN");  break;
		case AST_IF:     fprintf(stderr, "AST_IF");      break;
		case AST_IF_ELSE:fprintf(stderr, "AST_IF_ELSE"); break;
		case AST_WHILE:  fprintf(stderr, "AST_WHILE");   break;
		case AST_VAR:    fprintf(stderr, "AST_VAR");     break;
		case AST_VECTOR: fprintf(stderr, "AST_VECTOR");  break;
		case AST_MSG:    fprintf(stderr, "AST_MSG");     break;
		case AST_MSGL:   fprintf(stderr, "AST_MSGL");    break;
		case AST_CMD:    fprintf(stderr, "AST_CMD");     break;
		case AST_LCMD:   fprintf(stderr, "AST_LCMD");    break;
		case AST_LCMDT:  fprintf(stderr, "AST_LCMDT");   break;

		default:         fprintf(stderr, "AST_UNKNOWN"); break;
	}

	if(node->symbol) fprintf(stderr, ",%s\n", node->symbol->text);
	else fprintf(stderr, ",0\n");

	for(int i = 0; i < MAX_SONS; i++) astPrint(node->son[i], level+1);
}

void astDecompile(AST *node)
{
    if (!node) return;
    
	switch (node->type)
    {
		case AST_LCMD:
			astDecompile(node->son[0]);
			fprintf(out,";\n ");
			astDecompile(node->son[1]);
			break;
		case AST_SYMBOL:
			fprintf(out,"%s",node->symbol->text);
			break;
		case AST_NOT:
			fprintf(out, "~");
			astDecompile(node->son[0]);
			break;
		case AST_ADD:
			astDecompile(node->son[0]);
			fprintf(out, "+");
			astDecompile(node->son[1]);
			break;
		case AST_SUB:
			astDecompile(node->son[0]);
			fprintf(out, "-");
			astDecompile(node->son[1]);
			break;
		case AST_MUL:
			astDecompile(node->son[0]);
			fprintf(out, ".");
			astDecompile(node->son[1]);
			break;
		case AST_DIV:
			astDecompile(node->son[0]);
			fprintf(out, "/");
			astDecompile(node->son[1]);
			break;
		case AST_AND:
			astDecompile(node->son[0]);
			fprintf(out, "&");
			astDecompile(node->son[1]);
			break;
		case AST_OR:
			astDecompile(node->son[0]);
			fprintf(out, "|");
			astDecompile(node->son[1]);
			break;
		case AST_LSR:
			astDecompile(node->son[0]);
			fprintf(out, "<");
			astDecompile(node->son[1]);
			break;
		case AST_GTR:
			astDecompile(node->son[0]);
			fprintf(out, ">");
			astDecompile(node->son[1]);
			break;
		case AST_LSE:
			astDecompile(node->son[0]);
			fprintf(out, "<=");
			astDecompile(node->son[1]);
			break;
		case AST_GTE:
			astDecompile(node->son[0]);
			fprintf(out, ">=");
			astDecompile(node->son[1]);
			break;
		case AST_EQU:
			astDecompile(node->son[0]);
			fprintf(out, "==");
			astDecompile(node->son[1]);
			break;
		case AST_DIF:
			astDecompile(node->son[0]);
			fprintf(out, "!=");
			astDecompile(node->son[1]);
			break;
		case AST_CHAR:
			fprintf(out, "char");
			break;
		case AST_INT:
			fprintf(out, "int");
			break;
		case AST_FLOAT:
			fprintf(out, "float");
			break;
		case AST_IF:
			fprintf(out,"if(");
			astDecompile(node->son[0]);
			fprintf(out,")  \n");
			astDecompile(node->son[1]);
			fprintf(out," ");
			break;
		case AST_IF_ELSE:
			fprintf(out,"if(");
			astDecompile(node->son[0]);
			fprintf(out,")  ");
			astDecompile(node->son[1]);
			fprintf(out," ");
			fprintf(out,"else\n");
			astDecompile(node->son[2]);
			break;
		case AST_PRINT:
			fprintf(out,"print ");
			astDecompile(node->son[0]);
			break;
		case AST_READ:
			fprintf(out,"read ");
			break;
		case AST_RETURN:
			fprintf(out,"return ");
			astDecompile(node->son[0]);
			break;
    }  
}