/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */

#include "semantic.h"

int SemanticErrors = 0;

void check_and_set_declarations(AST *node)
{
	int i;

	if (node == 0)
		return;

	switch (node->type)
	{
		case AST_DECVAR:
			if (node->symbol)
			{
				if (node->symbol->type != HASH_IDT)
				{
					fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			node->symbol->type = HASH_VAR;
			}
			break;
		case AST_DECVEC:
			if (node->symbol)
			{
				if (node->symbol->type != HASH_IDT)
				{
					fprintf(stderr, "Semantic ERROR: vector %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			node->symbol->type = HASH_VEC;}
			break;
		case AST_DECFUN:
			if (node->symbol)
			{
				if (node->symbol->type != HASH_IDT)
				{
					fprintf(stderr, "Semantic ERROR: function %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			node->symbol->type = HASH_FUN;}
			break;
	}

	for (i=0; i<MAX_SONS; ++i)
		check_and_set_declarations(node->son[i]);
}
void check_undeclared();