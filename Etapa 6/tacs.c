/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 */

#include <stdlib.h>
#include <string.h>
#include "tacs.h"

char * tacType[AST_ARGL+1] = {
	"TAC_SYMBOL",
	"TAC_LABEL",
	"TAC_IFZ",
	"TAC_JUMP",
	"TAC_JUMPZ",
	"TAC_JFALSE",
	"TAC_CALL",
	"TAC_VECTOR",
	"TAC_ARG",
	"TAC_EXPN",
	"TAC_READ",
	"TAC_PRINT",
	"TAC_RETURN",
	"TAC_COPY",
	"TAC_BEGINFUN",
	"TAC_ENDFUN",
	"TAC_ADD",
	"TAC_SUB",
	"TAC_DIV",
	"TAC_MUL",
	"TAC_AND",
	"TAC_OR",
	"TAC_NOT",
	"TAC_LSE",
	"TAC_GTE",
	"TAC_EQU",
	"TAC_DIF",
	"TAC_LSR",
	"TAC_GTR",
	"TAC_VAR",
	"TAC_DECVEC",
	"AST_INTV",
	"TAC_DECVAR",
	"TAC_MSGL",
	"AST_EXPL",
	"AST_ARGL",
};

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
	if ((tac->type == TAC_SYMBOL) || (tac->type == TAC_VAR) || 
		(tac->type == TAC_EXPN) || (tac->type == TAC_VECTOR)) return;
	fprintf(stderr, "TAC(");

	if(tac->type <= AST_ARGL) fprintf(stderr, "%s", tacType[tac->type]);
 	else fprintf(stderr, "TAC_UNKNOWN");

	fprintf(stderr, ", %s", (tac->res) ? tac->res->text : "");
	if (tac->op1) fprintf(stderr, ", %s", tac->op1->text);
	if (tac->op2) fprintf(stderr, ", %s", tac->op2->text);
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
TAC* makeUnaryOperation(int type, TAC* code0, int temp);
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
			result = tacCreate(TAC_SYMBOL, node->symbol, 0, 0); 
			break;
		case AST_ADD://foi
			result = makeBinaryOperation(TAC_ADD, code[0], code[1]);
			break;
		case AST_SUB://foi
			result = makeBinaryOperation(TAC_SUB, code[0], code[1]);
			break;
		case AST_DIV://foi
			result = makeBinaryOperation(TAC_DIV, code[0], code[1]);
			break;
		case AST_MUL://foi
			result = makeBinaryOperation(TAC_MUL, code[0], code[1]);
			break;
		case AST_LSR://foi
			result = makeBinaryOperation(TAC_LSR, code[0], code[1]);
			break;
		case AST_GTR://foi
			result = makeBinaryOperation(TAC_GTR, code[0], code[1]);
			break;
		case AST_LSE://foi
			result = makeBinaryOperation(TAC_LSE, code[0], code[1]);
			break;
		case AST_GTE://foi
			result = makeBinaryOperation(TAC_GTE, code[0], code[1]);
			break;
		case AST_EQU://foi
			result = makeBinaryOperation(TAC_EQU, code[0], code[1]);
			break;
		case AST_DIF://foi
			result = makeBinaryOperation(TAC_DIF, code[0], code[1]);
			break;
		case AST_AND:
			result = makeBinaryOperation(TAC_AND, code[0], code[1]);
			break;
		case AST_OR:
			result = makeBinaryOperation(TAC_OR, code[0], code[1]);
			break;
		case AST_NOT:
			result = makeUnaryOperation(TAC_NOT, code[0], 1);
			break;
		case AST_ASSIGN://foi
			result = tacJoin(code[0], tacJoin(code[1], 
							tacCreate(TAC_COPY, code[0]->res, code[1] ? code[1]->res : 0, 
										code[0]->op1? code[0]->op1 : code[1]->op1? code[1]->op1 : 0)));
			break;
		case AST_DECVAR://foi
			result = tacJoin(code[1], tacCreate(TAC_DECVAR, node->symbol, code[1] ? code[1]->res : 0, 0));
			break;
		case AST_INTV: //foi
			result = tacJoin(tacCreate(TAC_INTV, code[0]->res, 0, 0), code[1]);
			break;
		case AST_DECVEC://foi
			result = tacJoin(tacCreate(TAC_DECVEC, node->symbol, code[1] ? code[1]->res : 0, 0), tacJoin(code[1], code[2]));
			break;
		case AST_ARGL:// tem que vir depois?
			result = tacJoin(code[1], tacCreate(TAC_ARGL, node->symbol, 0, 0));
			break;
		case AST_DECFUN://foi
			result = tacJoin(code[1], 
				tacJoin(
					tacJoin(
						tacCreate(TAC_BEGINFUN, node->symbol, 0, 0),
						code[2]
					), 
					tacCreate(TAC_ENDFUN, node->symbol, 0, 0)
				)
			);
            break;
		case AST_VAR: //foi
			result = tacCreate(TAC_VAR, node->symbol, 0, 0); 
			break;
		case AST_VECTOR: //foi
			result = tacCreate(TAC_VECTOR, node->symbol, code[0]->res, 0);
			break;
		case AST_EXPN:
			result = makeUnaryOperation(TAC_EXPN, code[0], 0);
			break;
		case AST_READ: 
			result = tacCreate(TAC_READ, code[0]->res, 0, 0);
			break;
		case AST_EXPL:
			result = tacJoin(code[1], tacCreate(TAC_EXPL, code[0]->res, 0, 0));
			break;
		case AST_CALL: 
			result = tacJoin(code[1], tacJoin(code[0], tacCreate(TAC_CALL, node->symbol, code[0] ? code[0]->res : 0, 0)));
			break;
		case AST_MSGL:
			result = tacJoin(code[1], tacJoin(code[0], tacCreate(TAC_MSGL, code[0]->res, 0, 0)));
			break;
		case AST_PRINT:
			result = tacJoin(code[0], tacCreate(TAC_PRINT, 0, 0, 0));
			break;
		case AST_RETURN: 
            result = tacJoin(code[0], tacCreate(TAC_RETURN, code[0] ? code[0]->res : 0, 0, 0));
            break;
		case AST_IF: //foi
			result = makeIfThen(code[0], code[1]);
			break;
		case AST_IF_ELSE: //foi
			result = makeIfThenElse(code[0], code[1], code[2]);
			break;
		case AST_WHILE: //foi
			result = makeWhile(code[0], code[1]);
			break;
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

	jumptac = tacCreate(TAC_JFALSE, newlabel, code0 ? code0->res : 0, 0);
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

	jumpztac = tacCreate(TAC_JUMPZ, jumpzlabel, code0 ? code0->res : 0, 0);
	jumpzlabelTAC = tacCreate(TAC_LABEL, jumpzlabel, 0, 0);

	jumptac = tacCreate(TAC_JUMP, jumplabel, 0, 0);
	jumplabelTAC = tacCreate(TAC_LABEL, jumplabel, 0, 0);

	return tacJoin(code0, 
		tacJoin(jumpztac, 
			tacJoin(jumpzlabelTAC, 
				tacJoin(code1,
					tacJoin(jumptac, 
						tacJoin(jumplabelTAC, code2))))));
}// mudei a ordem aqui pro que eu acho que ta correto

TAC* makeWhile(TAC* code0, TAC* code1)
{
	TAC* whileTAC = 0;
	TAC* whilelabelTAC = 0;
	TAC* jumptac = 0;
	TAC* jumplabelTAC = 0;

	HASH_NODE* whilelabel = 0;
	whilelabel = makeLabel();

	HASH_NODE* jumplabel = 0;
	jumplabel = makeLabel();

	whileTAC = tacCreate(TAC_JUMPZ, whilelabel, code0 ? code0->res:0, 0);
	whilelabelTAC = tacCreate(TAC_LABEL, whilelabel, 0, 0);

	jumptac = tacCreate(TAC_JUMP, jumplabel, 0, 0);    
	jumplabelTAC = tacCreate(TAC_LABEL, jumplabel, 0, 0);

	return tacJoin(jumplabelTAC,
		tacJoin(code0,
			tacJoin(whileTAC,
				tacJoin(code1,
					tacJoin(jumptac, whilelabelTAC)))));
					// qual eh dessa ordem? ta certo?
}

TAC* makeUnaryOperation(int type, TAC* code0, int temp) {
	return tacJoin(code0, 
		tacCreate(type, 
					temp? makeTemp() : 
					code0? code0->res : 0, 
					(temp && code0) ? code0->res : 0, 0));
}

TAC* makeBinaryOperation(int type, TAC* code0, TAC* code1) {
	return tacJoin(code0,
		tacJoin(code1,
			tacCreate(type, makeTemp(),
				code0 ? code0->res : 0, 
				code1 ? code1->res : 0)));
}

// ASM GENERATE
TAC* tacReverse(TAC *tac)
{
	TAC *t = tac;
	for (t = tac; t->prev; t = t->prev)
		t->prev->next = t;	
		
	return t;
}

void asmComparisonOperation(FILE *fout, TAC *tac, char *mnemonic);

void generateAsm(TAC *first)
{
	TAC *tac;
	FILE *fout;
	fout = fopen("output.s", "w");

	// Init
	fprintf(fout, "## FIXED HEADER\n"
	".section	.rodata\n"
	"	.printInt: .string	\"%%d\"\n"
	"	.printStr: .string	\"%%s\"\n\n");

	// Each Tac
	for (tac = first; tac; tac = tac->next)
	{
		switch (tac->type)
		{
			case TAC_ADD:
				fprintf(fout, "## ADD\n"
					"	movl	%s(%%rip), %%edx\n"
					"	movl	%s(%%rip), %%eax\n"
					"	addl	%%edx, %%eax\n"
					"	movl	%%eax, %s(%%rip)\n\n", 
					tac->op1->text, tac->op2->text, tac->res->text);
				break;
			case TAC_SUB:
				fprintf(fout, "## SUB\n"
					"	movl	%s(%%rip), %%eax\n"
					"	movl	%s(%%rip), %%edx\n"
					"	subl	%%edx, %%eax\n"
					"	movl	%%eax, %s(%%rip)\n\n", 
					tac->op1->text, tac->op2->text, tac->res->text);
				break;
			case TAC_DIV:
				fprintf(fout, "## DIV\n"
					"	movl	%s(%%rip), %%eax\n"
					"	movl	%s(%%rip), %%ecx\n"
					"	cltd\n"
					"	idivl	%%ecx\n"
					"	movl	%%eax, %s(%%rip)\n\n", 
					tac->op1->text, tac->op2->text, tac->res->text);
				break;
			case TAC_MUL:
				fprintf(fout, "## MUL\n"
					"	movl	%s(%%rip), %%edx\n"
					"	movl	%s(%%rip), %%eax\n"
					"	imull	%%edx, %%eax\n"
					"	movl	%%eax, %s(%%rip)\n\n", 
					tac->op1->text, tac->op2->text, tac->res->text);
				break;
			case TAC_EQU:
				fprintf(fout, "	# EQU\n");
				asmComparisonOperation(fout, tac, "je");
				break;

			case TAC_DIF:
				fprintf(fout, "	# DIF\n");
				asmComparisonOperation(fout, tac, "jne");
				break;

			case TAC_GTE:
				fprintf(fout, "	# GTE\n");
				asmComparisonOperation(fout, tac, "jge");
				break;

			case TAC_LSE:
				fprintf(fout, "# LSE\n");
				asmComparisonOperation(fout, tac, "jle");
				break;

			case TAC_GTR:
				fprintf(fout, "	# GTR\n");
				asmComparisonOperation(fout, tac, "jg");
				break;

			case TAC_LSR:
				fprintf(fout, "	# LSR\n");
				asmComparisonOperation(fout, tac, "jl");
				break;
			// case TAC_AND:
			// 	fprintf(fout, " ", );
			// case TAC_OR:
			// 	fprintf(fout, " ", );
			// case TAC_NOT:
			// 	fprintf(fout, " ", );
			case TAC_LABEL:
				fprintf(fout, ".%s:\n", tac->res->text);
				break; 
			case TAC_JUMP:
				fprintf(fout, "	# Jump\n"
					"	jmp	.%s\n", tac->res->text);
				break;
			case TAC_JUMPZ:
			case TAC_JFALSE:
				fprintf(fout, "	# Pulo condicional\n"
					"	movl	%s(%%rip), %%eax\n"
					"	cmpl	$0, %%eax\n"
					"	je	.%s\n", tac->op1->text, tac->res->text);
				break;
			case TAC_DECVEC:
				break;
			case TAC_BEGINFUN: 
				fprintf(fout, "## BEGIN FUNCTION\n"
					".text\n"
					".globl	%s\n"
					".type	%s, @function\n"
					"%s:\n"
					"	pushq	%%rbp\n"
					"	movq	%%rsp, %%rbp\n\n", tac->res->text, tac->res->text, tac->res->text);
				break;
			case TAC_ENDFUN: 
				fprintf(fout, "## END FUNCTION\n"
					"	movl	$0, %%eax\n"
					"	popq	%%rbp\n"
					"	ret\n\n");
				break;
			case TAC_COPY: 
				char res[256], op1[256];
				memset(res, 0, 256); memset(op1, 0, 256);
				if(tac->res->type == HASH_VEC && strcmp(tac->op2->text, "0")){
					int indx = strtoll(tac->op2->text, NULL, 10) * 4;
					char sindx[10];
					sprintf(sindx, "%d", indx);
					strcpy(res, sindx);
					strcat(res, "+");
					strcat(res, tac->res->text);
					strcat(op1, tac->op1->text);
				} else if (tac->op1->type == HASH_VEC && strcmp(tac->op2->text, "0")) {
					int indx = strtoll(tac->op2->text, NULL, 10) * 4;
					char sindx[10];
					sprintf(sindx, "%d", indx);
					strcpy(op1, sindx);
					strcat(op1, "+");
					strcat(op1, tac->op1->text);
					strcat(res, tac->res->text);
				} else {
					strcpy(res, tac->res->text);
					strcat(op1, tac->op1->text);
				}
				if((tac->op1->type != HASH_LIT_I) && (tac->op1->type != HASH_LIT_C) && 
					(tac->op1->type != HASH_LIT_F) && (tac->op1->type != HASH_LIT_S))
				{
					fprintf(fout, "## ASSIGN VAR\n"
						"	movl	%s(%%rip), %%eax\n"
						"	movl	%%eax, %s(%%rip)\n\n", op1, res);
				} else {
					fprintf(fout, "## ASSIGN LIT\n"
						"	movl	$%s, %s(%%rip)\n\n", op1, res);	
				}
				break;
			case TAC_MSGL: 
				fprintf(fout, "## PRINT ARGUMENTS\n"
					"	movl	%s(%%rip), %%eax\n"
					"	movl	%%eax, %%esi\n\n", tac->res->text);
				break;
			case TAC_PRINT: 
				fprintf(fout, "## PRINT\n"
					"	leaq	.printInt(%%rip), %%rax\n" // change it to work with strings too
					"	movq	%%rax, %%rdi\n"
					"	movl	$0, %%eax\n"
					"	call	printf@PLT\n\n");
				break;
			default:
				break;
		}
	}

	// Hash Table
	printAsm(fout);
	fclose(fout);
}

void asmComparisonOperation(FILE *fout, TAC *tac, char *mnemonic) {
	// Copia os operandos para %eax e %ebx

	// Se for literal, precisa ser modo imediato
	// Caso não seja literal, acessa em relação ao %rip
	if(tac->op1->type == HASH_LIT_I) {
		fprintf(fout, "	movl	$%s, %%eax\n", tac->op1->text);
	}
	else {
		fprintf(fout, "	movl	%s(%%rip), %%eax\n", tac->op1->text);
	}

	if(tac->op2->type == HASH_LIT_I) {
		fprintf(fout, "	movl $%s, %%ebx\n", tac->op2->text);
	}
	else {
		fprintf(fout, "	movl %s(%%rip), %%ebx\n", tac->op2->text);
	}

	// Faz a comparação
	fprintf(fout, "	cmpl %%ebx, %%eax\n");

	// Cria os labels para efetuar os pulos
	HASH_NODE *label1 = makeLabel();
	HASH_NODE *label2 = makeLabel();

	// Cria a lógica dos operadore de comparação (baseado nas flags setadas pelo operador 'cmp' já feito)
	fprintf(fout, "	%s .%s\n\n"
		"	movl $0, %%eax\n"
		"	movl %%eax, %s(%%rip)\n"
		"	jmp .%s\n\n"
		".%s:\n"
		"	movl $1, %%eax\n"
		"	movl %%eax, %s(%%rip)\n\n"
		".%s:\n", mnemonic, label1->text, tac->res->text, label2->text, label1->text, tac->res->text,	label2->text);
}