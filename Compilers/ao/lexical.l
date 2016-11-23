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
%x COMMENT

%option yylineno
%%
int	{
	yylval.type_sttree = cretree_c(36,"TYPE",yylloc,2,"int");
	return TYPE;
	}
float {
	yylval.type_sttree = cretree_c(36,"TYPE",yylloc,2,"float");
	return TYPE;
	}
struct {
	yylval.type_sttree = cretree_c(43,"STRUCT",yylloc,1,"struct");
	return STRUCT;
	}
return {
	yylval.type_sttree = cretree_c(44,"RETURN",yylloc,1,"return");
	return RETURN;
	}
if	{
	yylval.type_sttree = cretree_c(45,"IF",yylloc,1,"if");
	return IF;
	}
else	{
	yylval.type_sttree = cretree_c(46,"ELSE",yylloc,1,"else");
	return ELSE;
	}
while	{
	yylval.type_sttree = cretree_c(47,"WHILE",yylloc,1,"while");
	return WHILE;
	}
([1-9][0-9]*)|0	{
	yylval.type_sttree = cretree_i(21,"INT",yylloc,3,atoi(yytext));
	return INT;
	 }
0[1-7]*[0-7]*	{
	yylval.type_sttree = cretree_i(21,"INT",yylloc,3,(int)strtol(yytext,NULL,8));
	return INT;
 	}
(0x|0X)[1-9a-fA-F][0-9a-fA-F]*	{
	yylval.type_sttree = cretree_i(21,"INT",yylloc,3,(int)strtol(yytext,NULL,16));
	return INT;
	}
[0-9]+.[0-9]+ {
	yylval.type_sttree = cretree_f(22,"FLOAT",yylloc,4,atof(yytext));
	return FLOAT;
	}
_?(_|[a-z]|[A-Z])* {
	yylval.type_sttree = cretree_c(23,"ID",yylloc,2,yytext);
	return ID; }
";"	{
	yylval.type_sttree = cretree_c(24,"SEMI",yylloc,1,yytext);
	return SEMI;
	}
","	{
	yylval.type_sttree = cretree_c(25,"COMMA",yylloc,1,yytext);
	return COMMA;
	}
"="	{
	yylval.type_sttree = cretree_c(26,"ASSIGNOP",yylloc,1,yytext);
	return ASSIGNOP;
	}
>|<|>=|<=|==|!=	{
	yylval.type_sttree = cretree_c(27,"RELOP",yylloc,1,yytext);
	return RELOP;
	}
"+"	{
	yylval.type_sttree = cretree_c(28,"PLUS",yylloc,1,yytext);
	return PLUS;
	}
"-"	{
	yylval.type_sttree = cretree_c(29,"MINUS",yylloc,1,yytext);
	return MINUS;
	}
"*"	{
	yylval.type_sttree = cretree_c(30,"STAR",yylloc,1,yytext);
	return STAR;
	}
"/"	{
	yylval.type_sttree = cretree_c(31,"DIV",yylloc,1,yytext);
	return DIV;
	}
"&&" {
	yylval.type_sttree = cretree_c(32,"AND",yylloc,1,yytext);
	return AND;
	}
"||" {
	yylval.type_sttree = cretree_c(33,"OR",yylloc,1,yytext);
	return OR;
	}
"."	{
	yylval.type_sttree = cretree_c(34,"DOT",yylloc,1,yytext);
	return DOT;
	}
"!"	{
	yylval.type_sttree = cretree_c(35,"NOT",yylloc,1,yytext);
	return NOT;
	}
"("	{
	yylval.type_sttree = cretree_c(37,"LP",yylloc,1,yytext);
	return LP;
	}
")"	{
	yylval.type_sttree = cretree_c(38,"RP",yylloc,1,yytext);
	return RP;
	}
"["	{
	yylval.type_sttree = cretree_c(39,"LB",yylloc,1,yytext);
	return LB;
	}
"]"	{
	yylval.type_sttree = cretree_c(40,"RB",yylloc,1,yytext);
	return RB;
	}
"{"	{
	yylval.type_sttree = cretree_c(41,"LC",yylloc,1,yytext);
	return LC;
	}
"}"	{
	yylval.type_sttree = cretree_c(42,"RC",yylloc,1,yytext);
	return RC;
	}
"//"	{ 
	char c = input();
	while (c != '\n') c = input();
	}
"/*"	{ BEGIN COMMENT; /*切换到注释模式*/ }
<COMMENT>. |
<COMMENT>\n;
<COMMENT>"*/"	{ BEGIN INITIAL;	/*回到正常状态*/ }
[ \t]+	{}
[\n]	{ yycolumn = 1; }
~ { printf("Error type A at Line %d and Column %d: Mysterious character \"%s\".\n",yylloc.first_line,yylloc.first_column,yytext); }
[0-9][a-z|A-Z]+[0-9|a-z|A-Z]*	{ printf("Error type A at Line %d: error:\'%s\'.\n",yylineno,yytext); }
. 	{ printf("Error type A at Line %d and Column %d: error:\'%s\'.\n",yylloc.first_line,yylloc.first_column,yytext); }

%%
