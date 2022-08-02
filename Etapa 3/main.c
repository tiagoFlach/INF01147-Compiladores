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

	yyparse();

	hashPrint();
	printf("File has %d lines\n", getLineNumber());

	// Print grouped by type
	// for (int i = 272; i < 277; ++i)
	// {
	// 	hashPrintByType(i);
	// }

	exit(0);
}