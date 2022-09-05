#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

enum tacSymbol {
	TAC_SYMBOL,
	TAC_ADD,
	TAC_SUB,
}

typedef struct tac_node
{
	int type;
	HASH_NODE * res;
	HASH_NODE * op1;
	HASH_NODE * op2;
	struct tac_node* prev;
	struct tac_node* next;
} TAC


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);

TAC* generateCode(AST *node);

#endif