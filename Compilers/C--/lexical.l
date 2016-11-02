%{
	#include "syntax.tab.h"
	
	int yycolumn = 1;
	#define YY_USER_ACTION									\
		yylloc.first_line = yylloc.last_line = yylineno; 	\
		yylloc.first_column = yycolumn; 					\
		yylloc.first_column = yycolumn + yyleng - 1; 		\
		yycolumn += yyleng;
%}

%option yylineno
%%
int	{ return TYPE; }
float { return TYPE; }
struct { return STRUCT; }
return { return RETURN; }
if	{ return IF; }
else	{ return ELSE; }
while	{ return WHILE; }
([1-9][0-9]*)|0	{
	yylval.type_int = atoi(yytext);
	return DINT;
	 }
0[1-7]*[0-7]*	{
	return OINT;
 	}
0x|0X[1-9|a-f|A-F][0-9|a-f|A-F]*	{
	return HINT;
	}
[0-9]+.[0-9]+ {
	yylval.type_float = atof(yytext);
	return FLOAT;
	}
_?(_|[a-z]|[A-Z])* { return ID; }
";"	{ return SEMI; }
","	{ return COMMA; }
"="	{ return ASSIGNOP; }
>|<|>=|<=|==|!=	{ return RELOP; }
"+"	{ return ADD; }
"-"	{ return SUB; }
"*"	{ return MUL; }
"/"	{ return DIV; }
"&&" { return AND; }
"||" { return OR; }
"."	{ return DOT; }
"!"	{ return NOT; }
"("	{ return LP; }
")"	{ return RP; }
"["	{ return LB; }
"]"	{ return RB; }
"{"	{ return LC; }
"}"	{ return RC; }
"//"	{ 
	char c = input();
	while (c != '\n') c = input();
	}
[" "]+	{}
[\t]+	{}
[\n]	{ yycolumn = 1; }
[0-9][a-z|A-Z]+[0-9|a-z|A-Z]*	{ printf("Error type A at Line %d: error:\'%s\'.\n",yylineno,yytext); }
. 	{ printf("error\n"); }
%%
