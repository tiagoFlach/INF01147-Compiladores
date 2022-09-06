#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

enum tacSymbol {
	TAC_SYMBOL,
	TAC_MOVE,
	TAC_ADD,
	TAC_SUB,
	TAC_MUL,
	TAC_LABEL,
	TAC_ENDFUN,
	TAC_IFZ,
	TAC_JUMP,
	TAC_CALL,
	TAC_ARG,
	TAC_RET,
	TAC_PRINT,
	TAC_READ,
	TAC_COPY,
	TAC_JFALSE,
};

typedef struct tac_node
{
	int type;
	HASH_NODE * res;
	HASH_NODE * op1;
	HASH_NODE * op2;
	struct tac_node* prev;
	struct tac_node* next;
} TAC;


TAC* tacCreate(int type, HASH_NODE* res, HASH_NODE* op1, HASH_NODE* op2);
void tacPrint(TAC* tac);
void tacPrintBackwards(TAC* tac);
TAC* tacJoin(TAC* l1, TAC* l2);

TAC* generateCode(AST *node);

#endif