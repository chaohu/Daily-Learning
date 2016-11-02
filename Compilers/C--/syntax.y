%locations

%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "lex.yy.c"
	int yyerror(char *);
%}
/* declared types */
%union {
	int type_int;
	float type_float;
	double type_double;
}

/* declared tokens */
%token TYPE
%token ID
%token <type_int> DINT OINT HINT
%token <type_float> FLOAT
%token SEMI COMMA ASSIGNOP RELOP
%token ADD SUB MUL DIV
%token AND OR DOT NOT
%token LP RP LB RB LC RC

/* declared binding */
%right ASSIGNOP
%left AND SUB
%left MUL DIV
%left LP RP

/* declared non-terminals */
%type <type_double> Exp Factor Term

%%
/* Tokens */
DINT
FLOAT
ID
SEMI
	: ;
	;
COMMA
	: ,
	;
ASSIGNOP
	: =
	;
RELOP
	: >
	| <
	| >=
	| <=
	| ==
	| !=
	;
PLUS
	: +
	;
MINUS
	: -
	;
STAR
	: *
	;
DIV
	: /
	;
AND
	: &&
	;
OR
	: ||
	;
DOT
	: .
	;
NOT
	: !
	;
TYPE
	: int
	| float
	;
LP
	: (
	;
RP
	: )
	;
LB
	: [
	;
RB
	: ]
	;
LC
	: {
	;
RC
	: }
	;
STRUCT
	: struct
	;
RETURN
	: return
	;
IF
	: if
	;
ELSE
	: else
	;
WHILE
	: while
	; 

/* High-level Definition */
Program 
	: ExtDefList
	;
ExtDefList 
	: ExtDef ExtDefList
	|
	;
ExtDef 
	: Specifier ExtDecList SEMI
	| Specifier SEMI
	| Specifier FunDec CompSt
	;
ExtDecList 
	: VarDec
	| VarDec COMMA ExtDecList
	;

/* Specifier */
Specifier 
	: TYPE
	| StructSpecifier
	;
StructSpecifier
	: STRUCT Tag
	;
OptTag
	: ID
	|
	;
Tag
	: ID
	;

/* Declarators */
VarDec
	: ID
	| VarDec LB INT RB
	;
FunDec
	: ID LP VarList RP
	| ID LP RP
	;
VarList
	: ParamDec COMMA VarList
	| ParamDec
	;
ParamDec
	: Specifier VarDec
	;

/* Statements */
CompSt
	: LC DefList StmtList Rc
	;
StmtList
	: Stmt StmtKist
	|
	;
Stmt
	: Exp SEMI
	| CompSt
	| RETURN Exp SEMI
	| IF LP Exp RP Stmt
	| IF IP Exp RP Stmt ELSE Stmt
	| WHILE LP Exp RP Stmt
	;

/* Local Definitions */
DefList
	: Def DefList
	|
	;
Def
	: Specifier DecList SEMI
	;
DecList
	: Dec
	| Dec COMMA DecList
	;
Dec
	: VarDec
	| VarDec ASSIGNOP Exp
	;

/* Expressions */
Exp
	: Exp ASSIGNOP Exp
	| Exp AND Exp
	| Exp OR Exp
	| Exp RELOP Exp
	| Exp PLUS Exp
	| Exp MINUS Exp
	| Exp STAR Exp
	| Exp DIV Exp
	| LP Exp RP
	| MINUS Exp
	| NOT Exp
	| ID LP Args RP
	| ID LP RP
	| Exp LB Exp RB
	| Exp DOT ID
	| ID
	| DINT
	| FLOAT
	;
Args
	: Exp COMMA Args
	| Exp
	;
%%
int yyerror(char *msg) {
	fprintf(stderr, "error: %s\n", msg);
}
