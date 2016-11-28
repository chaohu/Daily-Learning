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
%token <type_sttree> INT
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
		$$ = entree(0,"Program",@1,1,$1);
        _sttree = $$;
		syntaxtree($$);
        semantic($$);
		}
	;
ExtDefList 
	: ExtDef ExtDefList	{ $$ = entree(1,"ExtDefList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
ExtDef 
	: Specifier ExtDecList SEMI	{ $$ = entree(2,"ExtDef",@1,3,$1,$2,$3); }
	| Specifier SEMI	{ $$ = entree(2,"ExtDef",@1,2,$1,$2); }
	| Specifier FunDec CompSt	{ $$ = entree(2,"ExtDef",@1,3,$1,$2,$3); }
	| error FunDec CompSt { }
	;
ExtDecList 
	: VarDec	{ $$ = entree(3,"ExtDecList",@1,1,$1); }
	| VarDec COMMA ExtDecList	{ $$ = entree(3,"ExtDecList",@1,3,$1,$2,$3); }
	;

/* Specifier */
Specifier 
	: TYPE	{ $$ = entree(4,"Specifier",@1,1,$1); }
	| StructSpecifier	{ $$ = entree(4,"Specifier",@1,1,$1); }
	;
StructSpecifier
	: STRUCT OptTag LC DefList RC	{ $$ = entree(5,"StructSpecifier",@1,4,$1,$2,$3,$4); }
	| STRUCT Tag	{ $$ = entree(5,"StructSpecifier",@1,2,$1,$2); }
	;
OptTag
	: ID	{ $$ = entree(6,"OptTag",@1,1,$1); }
	|	{ $$ = NULL; }
	;
Tag
	: ID	{ $$ = entree(7,"Tag",@1,1,$1); }
	;

/* Declarators */
VarDec
	: ID	{ $$ = entree(8,"VarDec",@1,1,$1); }
	| VarDec LB INT RB	{ $$ = entree(8,"VarDec",@1,4,$1,$2,$3,$4); }
	;
FunDec
	: ID LP VarList RP	{ $$ = entree(9,"FunDec",@1,4,$1,$2,$3,$4); }
	| ID LP RP	{ $$ = entree(9,"FunDec",@1,3,$1,$2,$3); }
	;
VarList
	: ParamDec COMMA VarList	{ $$ = entree(10,"VarList",@1,3,$1,$2,$3); }
	| ParamDec	{ $$ = entree(10,"VarList",@1,1,$1); }
	;
ParamDec
	: Specifier VarDec	{ $$ = entree(11,"ParamDec",@1,2,$1,$2); }
	;

/* Statements */
CompSt
	: LC DefList StmtList RC	{ $$ = entree(12,"CompSt",@1,4,$1,$2,$3,$4); }
	//| error DefList StmtList RC { }
	;
StmtList
	: Stmt StmtList	{ $$ = entree(13,"StmtList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
Stmt
	: Exp SEMI	{ $$ = entree(14,"Stmt",@1,2,$1,$2); }
	| CompSt	{ $$ = entree(14,"Stmt",@1,1,$1); }
	| RETURN Exp SEMI	{ $$ = entree(14,"Stmt",@1,3,$1,$2,$3); }
	| IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE { $$ = entree(14,"Stmt",@1,5,$1,$2,$3,$4,$5); }
	| IF LP Exp RP Stmt ELSE Stmt	{ $$ = entree(14,"Stmt",@1,7,$1,$2,$3,$4,$5,$6,$7); }
	| WHILE LP Exp RP Stmt	{ $$ = entree(14,"Stmt",@1,5,$1,$2,$3,$4,$5); }
	| error SEMI { }
	;

/* Local Definitions */
DefList
	: Def DefList	{ $$ = entree(15,"DefList",@1,2,$1,$2); }
	|	{ $$ = NULL; }
	;
Def
	: Specifier DecList SEMI { $$ = entree(16,"Def",@1,3,$1,$2,$3); }
	;
DecList
	: Dec	{ $$ = entree(17,"DecList",@1,1,$1); }
	| Dec COMMA DecList	{ $$ = entree(17,"DecList",@1,3,$1,$2,$3); }
	;
Dec
	: VarDec	{ $$ = entree(18,"Dec",@1,1,$1); }
	| VarDec ASSIGNOP Exp	{ $$ = entree(18,"Dec",@1,3,$1,$2,$3); }

	;

/* Expressions */
Exp
	: Exp ASSIGNOP Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp AND Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp OR Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp RELOP Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp PLUS Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp MINUS Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp STAR Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp DIV Exp	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| LP Exp RP	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| MINUS Exp	{ $$ = entree(19,"Exp",@1,2,$1,$2); }
	| NOT Exp	{ $$ = entree(19,"Exp",@1,2,$1,$2); }
	| ID LP Args RP	{ $$ = entree(19,"Exp",@1,4,$1,$2,$3,$4); }
	| ID LP RP	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| Exp LB Exp RB	{ $$ = entree(19,"Exp",@1,4,$1,$2,$3,$4); }
	| Exp DOT ID	{ $$ = entree(19,"Exp",@1,3,$1,$2,$3); }
	| ID	{ $$ = entree(19,"Exp",@1,1,$1); }
	| INT	{ $$ = entree(19,"Exp",@1,1,$1); }
	| FLOAT	{ $$ = entree(19,"Exp",@1,1,$1); }
	| error RP { }
	;
Args
	: Exp COMMA Args	{ $$ = entree(20,"Args",@1,3,$1,$2,$3); }
	| Exp	{ $$ = entree(20,"Args",@1,1,$1); }
	;
%%
void yyerror(char const*msg) {
	fprintf(stderr, "Error type B at Line %d and Column %d: \"%s\"\n", yylloc.first_line, yylloc.first_column, msg);
}
