/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 */

#ifndef TACS_HEADER
#define TACS_HEADER

#include "hash.h"
#include "ast.h"

enum tacSymbol {
	TAC_SYMBOL,
	TAC_MOVE,
	// Mathematics
	TAC_ADD,
	TAC_SUB,
	TAC_DIV,
	TAC_MUL,
	// Comparison
	TAC_LSR,
	TAC_GTR,
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




	// // Logic
	// AST_AND,
	// AST_OR,
	// AST_NOT,
	// // Operators
	// AST_LSE,
	// AST_GTE,
	// AST_EQU,
	// AST_DIF,
	// AST_ASSIGN,
	// // Commands
	// AST_DECVAR,
	// AST_DECVEC,
	// AST_DECFUN,
	// AST_CMD,
	// AST_LCMD,
	// AST_LCMDT,
	// AST_EXPN,
	// // Variables
	// AST_VAR,
	// AST_VECTOR,
	// // Message
	// AST_MSG,
	// AST_MSGL,
	// // Conditions
	// AST_IF,
	// AST_IF_ELSE,
	// AST_WHILE,
	// // Functions
	// AST_READ,
	// AST_PRINT,
	// AST_RETURN,
	// AST_CALL,
	// // Type
	// AST_CHAR,
	// AST_FLOAT,
	// AST_INT,
	// // Initialization
	// AST_INTV,
	// // Lists
	// AST_EXPL,
	// AST_ARGL,
	// AST_DECL,
	// AST_BLCK,
	// AST_PROGRAM
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