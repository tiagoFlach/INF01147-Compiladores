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
%token TK_EOF 0

%left '&' '|'
%left '<' '>' OPERATOR_EQ OPERATOR_DIF OPERATOR_LE OPERATOR_GE
%left '+' '-'
%left '.' '/'
%left '~'

%%

program:
	TK_EOF
	| dec_list
	;

dec:
	dec_var
	| function
	;

dec_list:
	dec dec_list
	|
	;

/* Variáveis */

dec_var:
	simple_var
	| vector
	;

simple_var:
	type TK_IDENTIFIER '(' literal ')' ';'
	;

vector:
	type TK_IDENTIFIER '[' LIT_INTEGER ']' ';'
	| type TK_IDENTIFIER '[' LIT_INTEGER ']' vector_value ';'
	;

vector_value:
	literal
	| literal vector_value
	;


/* Funções */

function:
	function_header function_body
	;

function_header:
	type TK_IDENTIFIER '(' param_list ')'
	;

function_body:
	cmd_block
	;

param:
	type TK_IDENTIFIER
	;

param_list:
	param param_list
	|
	;


/* Comandos */

cmd: 
	assignment
	| flow_cotrol
	| KW_READ TK_IDENTIFIER
	| KW_READ TK_IDENTIFIER '[' expr ']'
	| KW_PRINT print_list
	| KW_RETURN expr
	| '{' cmd_list '}'
	| TK_IDENTIFIER
	| cmd_block
	|
	;

cmd_list: 
	cmd ';' cmd_list
	| cmd
	|
	;

cmd_block:
	'{' cmd_list '}'
	| '{' '}'
	;

assignment:
	TK_IDENTIFIER ASSIGNMENT expr
	| TK_IDENTIFIER '[' expr ']' ASSIGNMENT expr
	;

expr: 
	TK_IDENTIFIER
	| TK_IDENTIFIER '[' expr ']'
	| TK_IDENTIFIER '(' parameter_list ')'
	| '(' expr ')'
	| literal
	| expr operator expr
	;


/* Controle de fluxo */

flow_cotrol:
	KW_IF '(' expr ')' cmd
	| KW_IF '(' expr ')' cmd KW_ELSE cmd
	| KW_WHILE '(' expr ')' cmd


/* Definições */

	
print_argument:
	LIT_STRING
	| expr
	;

print_list:
	print_argument print_list
	| print_argument
	;

parameter_list: expr parameter_list
    | expr
    ;

literal:
	LIT_INTEGER
	| LIT_FLOAT
	| LIT_CHAR
	;

type:
	KW_CHAR
	| KW_INT
	| KW_FLOAT
	;

operator: 
	OPERATOR_EQ
	| OPERATOR_LE
	| OPERATOR_GE
	| OPERATOR_DIF
	| '+'
	| '-'
	| '.'
	| '/'
	| '<'
	| '>'
	| '&'
	| '|'
	| '~'
	;

%%

int yyerror (char const *s)
{
	fprintf(stderr, "Error at line %d: %s\n", getLineNumber(), s);
	exit(3);
}