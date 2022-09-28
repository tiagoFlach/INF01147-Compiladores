/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 */

#include <stdlib.h>
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
	if (tac->type = TAC_SYMBOL) return;
	fprintf(stderr, "TAC(");

	switch(tac->type)
	{
		case TAC_SYMBOL: fprintf(stderr, "TAC_SYMBOL"); break;
		case TAC_MOVE: fprintf(stderr, "TAC_MOVE"); break;
		case TAC_ADD: fprintf(stderr, "TAC_ADD"); break;
		case TAC_SUB: fprintf(stderr, "TAC_SUB"); break;
		case TAC_MUL: fprintf(stderr, "TAC_MUL"); break;
		case TAC_LSR: fprintf(stderr, "TAC_LSR"); break;
		case TAC_GTR: fprintf(stderr, "TAC_GTR"); break;
		case TAC_LSE: fprintf(stderr, "TAC_LSE"); break;
		case TAC_GTE: fprintf(stderr, "TAC_GTE"); break;
		case TAC_EQU: fprintf(stderr, "TAC_EQU"); break;
		case TAC_DIF: fprintf(stderr, "TAC_DIF"); break;
		case TAC_LABEL: fprintf(stderr, "TAC_LABEL"); break;
		case TAC_ENDFUN: fprintf(stderr, "TAC_ENDFUN"); break;
		case TAC_IFZ: fprintf(stderr, "TAC_IFZ"); break;
		case TAC_JUMP: fprintf(stderr, "TAC_JUMP"); break;
		case TAC_JFALSE: fprintf(stderr, "TAC_JFALSE"); break;
		case TAC_CALL: fprintf(stderr, "TAC_CALL"); break;
		case TAC_ARG: fprintf(stderr, "TAC_ARG"); break;
		case TAC_RET: fprintf(stderr, "TAC_RET"); break;
		case TAC_PRINT: fprintf(stderr, "TAC_PRINT"); break;
		case TAC_READ: fprintf(stderr, "TAC_READ"); break;
		case TAC_COPY: fprintf(stderr, "TAC_COPY"); break;
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
		return;
	else
	{
		tacPrintBackwards(tac->prev);
		tacPrint(tac);
	}
}

TAC* tacJoin(TAC* l1, TAC* l2)
{
	TAC *point;

	if (!l1) return l2;
	if (!l2) return l1;

	for (point = l2; point->prev != 0; point = point->prev);

	point->prev = l1;
	return l2;
}

// CODE GENERATE
TAC* makeIfThen(TAC* code0, TAC* code1);
TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2);
TAC* makeWhile(TAC* code0, TAC* code1);
TAC* makeBinaryOperation(int type, TAC* code0, TAC* code1);

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
		case AST_SYMBOL:
			result = tacCreate(TAC_SYMBOL, node->symbol,0,0); 
			break;
		case AST_ADD:
			result = makeBinaryOperation(TAC_ADD, code[0], code[1]);
			break;
		case AST_SUB:
			result = makeBinaryOperation(TAC_SUB, code[0], code[1]);
			break;
		case AST_DIV:
			result = makeBinaryOperation(TAC_DIV, code[0], code[1]);
			break;
		case AST_MUL:
			result = makeBinaryOperation(TAC_MUL, code[0], code[1]);
			break;
		case AST_LSR:
			result = makeBinaryOperation(TAC_LSR, code[0], code[1]);
			break;
		case AST_GTR:
			result = makeBinaryOperation(TAC_GTR, code[0], code[1]);
			break;
		case AST_LSE:
			result = makeBinaryOperation(TAC_LSE, code[0], code[1]);
			break;
		case AST_GTE:
			result = makeBinaryOperation(TAC_GTE, code[0], code[1]);
			break;
		case AST_EQU:
			result = makeBinaryOperation(TAC_EQU, code[0], code[1]);
			break;
		case AST_DIF:
			result = makeBinaryOperation(TAC_DIF, code[0], code[1]);
			break;
		case AST_ASSIGN:
			result = tacJoin(code[0], tacCreate(TAC_COPY, node->symbol, code[0] ? code[0]->res : 0,0));
			break;
		

		// case AST_AND: break;
		// case AST_OR: break;
		// case AST_NOT: break;
		// // case AST_ASSIGN: break;
		// case AST_DECVAR: break;
		// case AST_DECVEC: break;
		// case AST_DECFUN: break;
		// case AST_CMD: break;
		// case AST_LCMD: break;
		// case AST_LCMDT: break;
		// case AST_EXPN: break;
		// case AST_VAR: break;
		// case AST_VECTOR: break;
		// case AST_MSG: break;
		// case AST_MSGL: break;
		case AST_IF: 
			result = makeIfThen(code[0], code[1]);
			break;
		case AST_IF_ELSE: 
			result = makeIfThenElse(code[0], code[1], code[2]);
			break;
		case AST_WHILE: 
			result = makeWhile(code[0], code[1]);
			break;
		case AST_READ: break;
		// case AST_PRINT: break;
		case AST_RETURN: 
            result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0] ? code[0]->res : 0, 0, 0));
            break;
		// case AST_CALL: break;
		// case AST_CHAR: break;
		// case AST_FLOAT: break;
		// case AST_INT: break;
		// case AST_INTV: break;
		// case AST_EXPL: break;
		// case AST_ARGL: break;
		// case AST_DECL: break;
		// case AST_BLCK: break;
		// case AST_PROGRAM: break;

		default: 
			result = tacJoin(code[0], tacJoin(code[1], tacJoin(code[2], code[3])));
			break;
	}

	return result;
}


TAC* makeIfThen(TAC* code0, TAC* code1)
{
	TAC * jumptac = 0;
	TAC * labeltac = 0;

	HASH_NODE * newlabel = 0;
	newlabel = makeLabel();

	jumptac = tacCreate(TAC_JFALSE, newlabel,
						code0 ? code0->res : 0, 0);
	jumptac->prev = code0;
	labeltac = tacCreate(TAC_LABEL, newlabel, 0, 0);
	labeltac->prev = code1;

	return tacJoin(jumptac, labeltac);
}

TAC* makeIfThenElse(TAC* code0, TAC* code1, TAC* code2)
{
	TAC* jumpztac = 0;
	TAC* jumpzlabelTAC = 0;
	TAC* jumptac = 0;
	TAC* jumplabelTAC = 0;

	HASH_NODE* jumpzlabel = 0;
	jumpzlabel = makeLabel();

	HASH_NODE* jumplabel = 0;
	jumplabel = makeLabel();

	jumpztac = tacCreate(TAC_JUMPZ, jumpzlabel, code0?code0->res:0, 0);
	jumpzlabelTAC = tacCreate(TAC_LABEL, jumpzlabel, 0, 0);

	jumptac = tacCreate(TAC_JUMP, jumplabel, 0, 0);    
	jumplabelTAC = tacCreate(TAC_LABEL, jumplabel, 0, 0);

	return tacJoin(code0, 
		tacJoin(jumpztac, 
			tacJoin(code1, 
				tacJoin(jumptac,
					tacJoin(jumpzlabelTAC, 
						tacJoin(code2, jumplabelTAC))))));
}

TAC* makeWhile(TAC* code0, TAC* code1) {

}

TAC* makeBinaryOperation(int type, TAC* code0, TAC* code1) {
	return tacJoin(code0,
		tacJoin(code1,
			tacCreate(type, makeTemp(),
				code0 ? code0->res : 0, 
				code1 ? code1->res : 0)));
}