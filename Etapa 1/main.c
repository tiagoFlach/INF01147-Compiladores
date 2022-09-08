/**
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1 - Etapa 1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 * Ainda sem grupo, providenciarei para a próxima etapa
 * 
 */

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
		exit(1);
	}

	while (isRunning())
	{
		token = yylex();

		if (isRunning() == 0)
			break;

		switch(token) 
		{
			case KW_CHAR:
			case KW_INT:
			case KW_FLOAT:
			case KW_IF:
			case KW_ELSE:
			case KW_WHILE:
			case KW_READ:
			case KW_PRINT:
			case KW_RETURN:
			case ASSIGNMENT:
			case OPERATOR_LE:
			case OPERATOR_GE:
			case OPERATOR_EQ:
			case OPERATOR_DIF:
			case TK_IDENTIFIER:
			case LIT_INTEGER:
			case LIT_FLOAT:
			case LIT_CHAR:
			case LIT_STRING:
				break;
			case TOKEN_ERROR: 
				printf("Unexpected token in line %d: %d . %c\n", getLineNumber(), token, yytext[0]);
				break;
			default: 
				printf("Especial character '%c' in line %d\n", yytext[0], getLineNumber()); 
				break;
		}
	}

	hashPrint();
	printf("File has %d lines\n", getLineNumber());

	// Print grouped by type
	for (int i = 280; i <= 286; ++i)
	{
		hashPrintByType(i);
	}

	return 0;
}