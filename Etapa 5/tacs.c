#include "tacs.h"

TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2)
{
	TAC* newtac = 0;
	newtac = (TAC*) calloc(1, sizeof(TAC));
	newtac->type = type;
	newtac->res = res;
	newtac->op1 = op1;
	newtac->op2 = op2;
	newtac->prev = 0;
	newtac->next = 0;
	return newtac;
}

void tacPrint(TAC* tac)
{
	if (!tac) return;
	fprintf(stderr, "TAC(");

	switch(tac->type)
	{
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		default: fprintf(stderr, "TAC_UNKNOWN"); break;
	}

	fprintf(stderr, ",%s", (tac->res) ? tac->res->text : "");
	fprintf(stderr, ",%s", (tac->op1) ? tac->op1->text : "");
	fprintf(stderr, ",%s", (tac->op2) ? tac->op2->text : "");
	fprintf(stderr, ");\n");
}
void tacPrintBackwards(TAC* tac)
{
	if (!tac)
		return
	else
	{
		tacPrintBackwards(tac->prev);
		tacPrint(tac);
	}
}

TAC* generateCode(AST *node)
{
	int i;
	TAC *result = 0;
	TAC *code[MAX_SONS];

	if (!node) return 0;

	// Children
	for (i=0; i<MAX_SONS; ++i)
		code[i] = generateCode(node->son[i]);

	// This node
	switch(node->type)
	{

	}

	return result;
}