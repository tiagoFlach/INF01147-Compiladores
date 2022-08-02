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
#include "lex.yy.h"

extern int yyparse();
extern int hashPrint();

void initMe(void);
int isRunning(void);
int getLineNumber(void);

extern FILE *yyin;
FILE *out;
// extern AST *ASTroot;

int main(int argc, char** argv)
{
	int token = 0;

	initMe();

	// Falta do arquivo de entrada
	if (argc < 2)
	{
		printf("Call: ./etapa1 input.txt\n");
		exit(1);
	}

	// Falha ao abrir o arquivo
	if ((yyin = fopen(argv[1], "r")) == 0)
	{
		printf("Cannot open file %s... \n", argv[1]);
		exit(2);
	}

	// Falha ao abrir o arquivo
	if ((out = fopen(argv[1], "r")) == 0)
	{
		printf("Cannot open file %s... \n", argv[1]);
		exit(2);
	}

	yyparse();

	// hashPrint();
	// astDecompile(ASTroot, out);
	// astDecompile(ASTroot, out);

	printf("File has %d lines\n", getLineNumber());

	exit(0);
}