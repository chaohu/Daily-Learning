%locations
%error-verbose

%{
	#include "ao.h"
	#include "lex.yy.c"
%}
/* declared types */
%union {
	STTree *type_sttree;
	int type_int;
	float type_float;
	double type_double;
}

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

/* declared tokens */
%token <type_sttree> TYPE STRUCT IF ELSE WHILE RETURN
%token <type_sttree> ID
%token <type_sttree> DINT OINT HINT
%token <type_sttree> FLOAT
%token <type_sttree> SEMI COMMA ASSIGNOP RELOP
%token <type_sttree> PLUS MINUS STAR DIV
%token <type_sttree> AND OR DOT NOT
%token <type_sttree> LP RP LB RB LC RC

/* declared production */
%type<type_sttree> Program ExtDefList ExtDef
%type<type_sttree> Specifier ExtDecList FunDec
%type<type_sttree> CompSt VarDec StructSpecifier
%type<type_sttree> OptTag DefList Tag
%type<type_sttree> VarList ParamDec StmtList
%type<type_sttree> Stmt Exp Def
%type<type_sttree> Dec Args DecList

/* declared binding */
%right ASSIGNOP
%left PLUS MINUS STAR DIV
%left AND OR
%left RELOP
%left LP RP LB RB DOT
%right NOT




%%
/* High-level Definition */
Program	 
	: ExtDefList	{
		$$ = entree("Program",@1,1,$1);
		syntaxtree($$);
		}
	;
ExtDefList 
	: ExtDef ExtDefList	{ $$ = entree("ExtDefList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
ExtDef 
	: Specifier ExtDecList SEMI	{ $$ = entree("ExtDef",@1,3,$1,$2,$3); }
	| Specifier SEMI	{ $$ = entree("ExtDef",@1,2,$1,$2); }
	| Specifier FunDec CompSt	{ $$ = entree("ExtDef",@1,3,$1,$2,$3); }
	| error FunDec CompSt { }
	;
ExtDecList 
	: VarDec	{ $$ = entree("ExtDecList",@1,1,$1); }
	| VarDec COMMA ExtDecList	{ $$ = entree("ExtDecList",@1,3,$1,$2,$3); }
	| error SEMI { }
	;

/* Specifier */
Specifier 
	: TYPE	{ $$ = entree("Specifier",@1,1,$1); }
	| StructSpecifier	{ $$ = entree("Specifier",@1,1,$1); }
	;
StructSpecifier
	: STRUCT OptTag LC DefList RC	{ $$ = entree("StructSpecifier",@1,4,$1,$2,$3,$4); }
	| STRUCT Tag	{ $$ = entree("StructSpecifier",@1,2,$1,$2); }
	;
OptTag
	: ID	{ $$ = entree("OptTag",@1,1,$1); }
	|	{ $$ = NULL; }
	;
Tag
	: ID	{ $$ = entree("Tag",@1,1,$1); }
	;

/* Declarators */
VarDec
	: ID	{ $$ = entree("VarDec",@1,1,$1); }
	| VarDec LB DINT RB	{ $$ = entree("VarDec",@1,4,$1,$2,$3,$4); }
	;
FunDec
	: ID LP VarList RP	{ $$ = entree("FunDec",@1,4,$1,$2,$3,$4); }
	| ID LP RP	{ $$ = entree("FunDec",@1,3,$1,$2,$3); }
	;
VarList
	: ParamDec COMMA VarList	{ $$ = entree("VarList",@1,3,$1,$2,$3); }
	| ParamDec	{ $$ = entree("VarList",@1,1,$1); }
	;
ParamDec
	: Specifier VarDec	{ $$ = entree("ParamDec",@1,2,$1,$2); }
	;

/* Statements */
CompSt
	: LC DefList StmtList RC	{ $$ = entree("CompSt",@1,4,$1,$2,$3,$4); }
	| error DefList StmtList RC { }
	;
StmtList
	: Stmt StmtList	{ $$ = entree("StmtList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
Stmt
	: Exp SEMI	{ $$ = entree("Stmt",@1,2,$1,$2); }
	| CompSt	{ $$ = entree("Stmt",@1,1,$1); }
	| RETURN Exp SEMI	{ $$ = entree("Stmt",@1,3,$1,$2,$3); }
	| IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE { $$ = entree("Stmt",@1,5,$1,$2,$3,$4,$5); }
	| IF LP Exp RP Stmt ELSE Stmt	{ $$ = entree("Stmt",@1,7,$1,$2,$3,$4,$5,$6,$7); }
	| WHILE LP Exp RP Stmt	{ $$ = entree("Stmt",@1,5,$1,$2,$3,$4,$5); }
	| error SEMI { }
	;

/* Local Definitions */
DefList
	: Def DefList	{ $$ = entree("DefList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
Def
	: Specifier DecList SEMI { $$ = entree("Def",@1,3,$1,$2,$3); }
	;
DecList
	: Dec	{ $$ = entree("DecList",@1,1,$1); }
	| Dec COMMA DecList	{ $$ = entree("DecList",@1,3,$1,$2,$3); }
	;
Dec
	: VarDec	{ $$ = entree("Dec",@1,1,$1); }
	| VarDec ASSIGNOP Exp	{ $$ = entree("Dec",@1,3,$1,$2,$3); }

	;

/* Expressions */
Exp
	: Exp ASSIGNOP Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp AND Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp OR Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp RELOP Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp PLUS Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp MINUS Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp STAR Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp DIV Exp	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| LP Exp RP	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| MINUS Exp	{ $$ = entree("Exp",@1,2,$1,$2); }
	| NOT Exp	{ $$ = entree("Exp",@1,2,$1,$2); }
	| ID LP Args RP	{ $$ = entree("Exp",@1,4,$1,$2,$3,$4); }
	| ID LP RP	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| Exp LB Exp RB	{ $$ = entree("Exp",@1,4,$1,$2,$3,$4); }
	| Exp DOT ID	{ $$ = entree("Exp",@1,3,$1,$2,$3); }
	| ID	{ $$ = entree("Exp",@1,1,$1); }
	| DINT	{ $$ = entree("Exp",@1,1,$1); }
	| FLOAT	{ $$ = entree("Exp",@1,1,$1); }
	| error RP { }
	;
Args
	: Exp COMMA Args	{ $$ = entree("Args",@1,3,$1,$2,$3); }
	| Exp	{ $$ = entree("Args",@1,1,$1); }
	;
%%
void yyerror(char const*msg) {
	fprintf(stderr, "Error type B at Line %d and Column %d: \"%s\"\n", yylloc.first_line, yylloc.first_column, msg);
}
