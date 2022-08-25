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
		case AST_VAR:
			if (node->symbol)
			{
				if (node->symbol->type != SYMBOL_IDENTIFIER)
				{
					fprintf(stderr, "Semantic ERROR: variable %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			} else {

			}
			node->symbol->type = SYMBOL_VARIABLE;
			break;
		case AST_VECTOR:
			if (node->symbol)
			{
				if (node->symbol->type != SYMBOL_IDENTIFIER)
				{
					fprintf(stderr, "Semantic ERROR: vector %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			} else {

			}
			node->symbol->type = SYMBOL_VECTOR;
			break;
		case ART_DEC:
			if (node->symbol)
			{
				if (node->symbol->type != SYMBOL_IDENTIFIER)
				{
					fprintf(stderr, "Semantic ERROR: function %s already declared\n", node->symbol->text);
					++SemanticErrors;
				}
			} else {

			}
			node->symbol->type = SYMBOL_FUNCTION;
			break;
	}

	for (i=0; i<MAX_SONS; ++i)
		check_and_set_declarations(node->son[i]);
}
void check_undeclared();