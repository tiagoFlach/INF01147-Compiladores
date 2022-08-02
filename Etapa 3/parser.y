
%{
/*
 * 
 * UFRGS - Compiladores B - Marcelo Johann - 2022/1
 * 
 * Tiago Lucas Flach <tlflach@inf.ufrgs.br>
 * Arthur Prochnow Baumgardt <apbaumgardt@inf.ufrgs.br>
 * 
 */
#include "hash.h"
#include "ast.h"

int yylex(void); 
int yyerror(const char* s);
int getLineNumber();
%}

%union
{
HASH_NODE *symbol;
AST* ast;
}

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

%token<symbol> TK_IDENTIFIER

%token<symbol> LIT_INTEGER 
%token<symbol> LIT_FLOAT 
%token<symbol> LIT_CHAR
%token<symbol> LIT_STRING 

%token TOKEN_ERROR 

%type<ast> expr
%type<symbol> lit
%type<ast> var

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
        | var ASSIGNMENT expr                   { astPrint($3,0); }
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

lcmd:   cmd lcmdt                               { $$ = astCreate(AST_LCD,0,$1,$2,0,0); }
        ;

/* List command tail */
lcmdt: ';' cmd lcmdt 
        |                                       { $$ = 0; }
        ;

var:    TK_IDENTIFIER                           { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0);  }
        | TK_IDENTIFIER '[' expr ']'            { $$ = astCreate(AST_SYMBOL,$1,$3,0,0,0); }
        ;

expr:   lit                                     { $$ = astCreate(AST_SYMBOL,$1,0,0,0,0); }
        | var                                   
        | expr '+' expr                         { $$ = astCreate(AST_ADD,0,$1,$3,0,0); }
        | expr '-' expr                         { $$ = astCreate(AST_SUB,0,$1,$3,0,0); }
        | expr '/' expr                         { $$ = astCreate(AST_DIV,0,$1,$3,0,0); }
        | expr '.' expr                         { $$ = astCreate(AST_MUL,0,$1,$3,0,0); }
        | expr '<' expr                         { $$ = astCreate(AST_LSR,0,$1,$3,0,0); }
        | expr '>' expr                         { $$ = astCreate(AST_GTR,0,$1,$3,0,0); }
        | expr '&' expr                         { $$ = astCreate(AST_AND,0,$1,$3,0,0); }
        | expr '|' expr                         { $$ = astCreate(AST_OR ,0,$1,$3,0,0); }
        | expr '~' expr                         { $$ = astCreate(AST_NOT,0,$1,$3,0,0); }
        | expr OPERATOR_LE expr                 { $$ = astCreate(AST_LSE,0,$1,$3,0,0); }
        | expr OPERATOR_GE expr                 { $$ = astCreate(AST_GTE,0,$1,$3,0,0); }
        | expr OPERATOR_EQ expr                 { $$ = astCreate(AST_EQU,0,$1,$3,0,0); }
        | expr OPERATOR_DIF expr                { $$ = astCreate(AST_DIF,0,$1,$3,0,0); }
        | '(' expr ')'                          { $$ = $2; }
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