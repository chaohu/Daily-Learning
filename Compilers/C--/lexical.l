%{
	#include "syntax.tab.h"
	#include "ao.h"
	
	int yycolumn = 1;
	#define YY_USER_ACTION									\
		yylloc.first_line = yylloc.last_line = yylineno; 	\
		yylloc.first_column = yycolumn; 					\
		yylloc.first_column = yycolumn + yyleng - 1; 		\
		yycolumn += yyleng;
%}

%option yylineno
%%
int	{
	yylval.type_sttree = cretree_c("TYPE",yylloc.first_line,3,"int");
	return TYPE;
	}
float {
	yylval.type_sttree = cretree_c("TYPE",yylloc.first_line,3,"float");
	return TYPE;
	}
struct {
	yylval.type_sttree = cretree_c("STRUCT",yylloc.first_line,1,"struct");
	return STRUCT;
	}
return {
	yylval.type_sttree = cretree_c("RETURN",yylloc.first_line,1,"return");
	return RETURN;
	}
if	{
	yylval.type_sttree = cretree_c("IF",yylloc.first_line,1,"if");
	return IF;
	}
else	{
	yylval.type_sttree = cretree_c("ELSE",yylloc.first_line,1,"else");
	return ELSE;
	}
while	{
	yylval.type_sttree = cretree_c("WHILE",yylloc.first_line,1,"while");
	return WHILE;
	}
([1-9][0-9]*)|0	{
	yylval.type_sttree = cretree_i("DINT",yylloc.first_line,3,atoi(yytext));
	return DINT;
	 }
0[1-7]*[0-7]*	{
	return OINT;
 	}
0x|0X[1-9|a-f|A-F][0-9|a-f|A-F]*	{
	return HINT;
	}
[0-9]+.[0-9]+ {
	yylval.type_sttree = cretree_f("FLOAT",yylloc.first_line,4,atof(yytext));
	return FLOAT;
	}
_?(_|[a-z]|[A-Z])* {
	yylval.type_sttree = cretree_c("ID",yylloc.first_line,2,yytext);
	return ID; }
";"	{
	yylval.type_sttree = cretree_c("SEMI",yylloc.first_line,1,yytext);
	return SEMI;
	}
","	{
	yylval.type_sttree = cretree_c("COMMA",yylloc.first_line,1,yytext);
	return COMMA;
	}
"="	{
	yylval.type_sttree = cretree_c("ASSIGNOP",yylloc.first_line,1,yytext);
	return ASSIGNOP;
	}
>|<|>=|<=|==|!=	{
	yylval.type_sttree = cretree_c("RELOP",yylloc.first_line,1,yytext);
	return RELOP;
	}
"+"	{
	yylval.type_sttree = cretree_c("PLUS",yylloc.first_line,1,yytext);
	return PLUS;
	}
"-"	{
	yylval.type_sttree = cretree_c("MINUS",yylloc.first_line,1,yytext);
	return MINUS;
	}
"*"	{
	yylval.type_sttree = cretree_c("STAR",yylloc.first_line,1,yytext);
	return STAR;
	}
"/"	{
	yylval.type_sttree = cretree_c("DIV",yylloc.first_line,1,yytext);
	return DIV;
	}
"&&" {
	yylval.type_sttree = cretree_c("AND",yylloc.first_line,1,yytext);
	return AND;
	}
"||" {
	yylval.type_sttree = cretree_c("OR",yylloc.first_line,1,yytext);
	return OR;
	}
"."	{
	yylval.type_sttree = cretree_c("DOT",yylloc.first_line,1,yytext);
	return DOT;
	}
"!"	{
	yylval.type_sttree = cretree_c("NOT",yylloc.first_line,1,yytext);
	return NOT;
	}
"("	{
	yylval.type_sttree = cretree_c("LP",yylloc.first_line,1,yytext);
	return LP;
	}
")"	{
	yylval.type_sttree = cretree_c("RP",yylloc.first_line,1,yytext);
	return RP;
	}
"["	{
	yylval.type_sttree = cretree_c("LB",yylloc.first_line,1,yytext);
	return LB;
	}
"]"	{
	yylval.type_sttree = cretree_c("RB",yylloc.first_line,1,yytext);
	return RB;
	}
"{"	{
	yylval.type_sttree = cretree_c("LC",yylloc.first_line,1,yytext);
	return LC;
	}
"}"	{
	yylval.type_sttree = cretree_c("RC",yylloc.first_line,1,yytext);
	return RC;
	}
"//"	{ 
	char c = input();
	while (c != '\n') c = input();
	}
[" "]+	{}
[\t]+	{}
[\n]	{ yycolumn = 1; }
~ { printf("Error type A at Line %d:error:\'%s\'.\n",yylineno,yytext); }
[0-9][a-z|A-Z]+[0-9|a-z|A-Z]*	{ printf("Error type A at Line %d: error:\'%s\'.\n",yylineno,yytext); }
. 	
%%	{ printf("Error type A at Line %d: error:\'%s\'.\n",yylineno,yytext); }
