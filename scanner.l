%{
/**
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1 - Etapa 1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * 
 * Ainda sem grupo, providenciarei para a próxima etapa
 * 
 */
#include "tokens.h"
#include "hash.h"

int running = 1;
int lineNumber = 1;
%}

%x COMMENT
DIGIT	[0-9]
CHAR	[a-zA-Z]

%%

char					{ return KW_CHAR; }
int						{ return KW_INT; }
float					{ return KW_FLOAT; }

if 						{ return KW_IF; }
else					{ return KW_ELSE; }
while					{ return KW_WHILE; }
read					{ return KW_READ; }
print					{ return KW_PRINT; }
return					{ return KW_RETURN; }

"<-"					{ return ASSIGNMENT; }
"<="					{ return OPERATOR_LE; }
">="					{ return OPERATOR_GE; }
"=="					{ return OPERATOR_EQ; }
"!="					{ return OPERATOR_DIF; }

[a-zA-Z_]*				{ return TK_IDENTIFIER; }

{DIGIT}+				{ return LIT_INTEGER; }
{DIGIT}","{DIGIT}		{ return LIT_FLOAT; }
"'".{1}"'"				{ return LIT_CHAR; }
\".\"					{ return LIT_STRING; }

[;()\[\]{}+-./<>&|~]	{ return yytext[0]; }

"\n"					{ ++lineNumber; }	
"##".*					{ }
"\\#"					{ BEGIN(COMMENT); }

.						{ return TOKEN_ERROR; }

<COMMENT>"#\\"			{ BEGIN(INITIAL); }
<COMMENT>"\n"			{ ++lineNumber; }
<COMMENT>.				{ }

%%

#include "hash.c"
#include "main.c"

void initMe(void)
{
	hashInit();
}

int isRunning(void)
{
	return running;
}

int getLineNumber(void)
{
	return lineNumber;
}

int yywrap()
{
	running = 0;
	return 1;
}