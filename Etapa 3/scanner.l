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
#include "y.tab.h"
#include "hash.h"

int running = 1;
int lineNumber = 1;

int isRunning(void)
{
	return running;
}

int getLineNumber(void)
{
	return lineNumber;
}

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

{DIGIT}+				{ hashInsert(yytext, LIT_INTEGER); return LIT_INTEGER; }
{DIGIT}","{DIGIT}		{ hashInsert(yytext, LIT_FLOAT); return LIT_FLOAT; }
\'.\'					{ hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
\"(\\.|[^\\"])*\"		{ hashInsert(yytext, LIT_STRING); return LIT_STRING; }

[a-zA-Z_]*				{ hashInsert(yytext, TK_IDENTIFIER); return TK_IDENTIFIER; }

[;()\[\]{}+-./<>&|~]	{ return yytext[0]; }

"##".*					{ }
"\\#"					{ BEGIN(COMMENT); }
"\n"					{ ++lineNumber; }	
[ \t\r]					{ }

.						{ return TOKEN_ERROR; }

<COMMENT>"\n"			{ ++lineNumber; }
<COMMENT>"#\\"			{ BEGIN(INITIAL); }
<COMMENT>.				{ }

%%


#include "y.tab.c"
#include "hash.c"
#include "main.c"

void initMe(void)
{
	hashInit();
}

int yywrap()
{
	running = 0;
	return 1;
}