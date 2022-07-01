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
			case TOKEN_ERROR:
				printf("Unexpected token %d: %c\n", token, yytext[0]);
				break;
			default:
				hashInsert(yytext, token);
				break;
		}
	}

	hashPrint();
	printf("File has %d lines", getLineNumber());

	return 0;
}