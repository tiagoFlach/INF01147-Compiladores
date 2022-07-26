
%{
        //Autor: Arthur Prochnow Baumgardt
        int yylex(void); 
        int yyerror(const char* s);
        int getLineNumber();
%}

%token KW_CHAR 
%token KW_INT  
%token KW_FLOAT

%token KW_IF    
%token KW_ELSE  
%token KW_WHILE 
%token KW_READ  
%token KW_PRINT 
%token KW_RETURN

%token ASSIGNMENT 
%token OPERATOR_LE
%token OPERATOR_GE
%token OPERATOR_EQ 
%token OPERATOR_DIF

%token TK_IDENTIFIER

%token LIT_INTEGER 
%token LIT_FLOAT 
%token LIT_CHAR
%token LIT_STRING 

%token TOKEN_ERROR 

%left '|' '&'
%left '+' '-'
%left '<' '>'
%left '~'
%left '.' '/'

%left OPERATOR_LE OPERATOR_GE
%left OPERATOR_EQ OPERATOR_DIF

%nonassoc IFX
%nonassoc KW_ELSE

%%

program: decl
        ;

decl:   dec decl
        |
        ;

dec:    lftop '(' lit ')' ';'
        | lftop '(' argl ')' blck
        | lftop '[' LIT_INTEGER ']' initv
        ;

/* Left operator */
lftop:  kw_t TK_IDENTIFIER
        ;

/* Type */
kw_t:   KW_CHAR     
        | KW_FLOAT
        | KW_INT
        ;

/* Literal */
lit:    LIT_CHAR
        | LIT_FLOAT
        | LIT_INTEGER
        ;

/* Init vector */
initv:  lit initv
        | ';'
        ;

/* Argument list */
argl:   lftop argl
        |
        ;

cmd:    blck 
        | var ASSIGNMENT expr
        | KW_WHILE '(' expr ')' cmd 
        | KW_IF '(' expr ')' cmd KW_ELSE cmd
        | KW_IF '(' expr ')' cmd %prec IFX
        | KW_READ var
        | KW_PRINT msgl
        | KW_RETURN expr
        |
        ;

/* Message list */
msgl:   msg msgl
        |
        ;

msg:    LIT_STRING
        | expr
        ;

blck:   '{' lcmd '}'
        ;

lcmd:   cmd lcmdt 
        ;

/* List command tail */
lcmdt: ';' cmd lcmdt 
        | 
        ;

var:    TK_IDENTIFIER
        | TK_IDENTIFIER '[' expr ']'
        ;

expr:   lit
        | var
        | expr '+' expr
        | expr '-' expr
        | expr '/' expr
        | expr '.' expr
        | expr '<' expr
        | expr '>' expr
        | expr '&' expr
        | expr '|' expr
        | expr '~' expr
        | expr OPERATOR_LE expr
        | expr OPERATOR_GE expr
        | expr OPERATOR_EQ expr
        | expr OPERATOR_DIF expr
        | '(' expr ')'
        | TK_IDENTIFIER '(' exprl ')'
        ;

exprl:  expr exprl
        |
        ;

%%

#include <stdio.h>
#include <stdlib.h>

extern char* yytext;

int yyerror(const char* s)
{
        fprintf(stderr, s);
        fprintf(stderr, " at line %d.\n", getLineNumber());
        fprintf(stderr, "Error here: %s\n", &yytext[0]);
        exit(3);
}