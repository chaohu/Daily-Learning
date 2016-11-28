#ifndef AO_H
#define AO_H 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern FILE* yyin;
extern int yydebug;
extern int yyparse(void);
extern void yyerror(char const*);

#undef YYDEBUG
#define YYDEBUG 1

#undef YYLTYPE
#define YYLTYPE yyltype

typedef struct YYLTYPE {
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} yyltype;

union T_value{
	int i_value;
	float f_value;
	char c_value[20];
};

typedef struct STTree{
    int num;
	char content[17];
	yyltype loc_info;
	union T_value value;
	int t_value;
	struct STTree *C_next;
	struct STTree *B_next;
}STTree;

STTree *_sttree;

int syntaxtree(STTree *);
int o_tree_c(STTree *);
int o_tree_b(STTree *);
int semantic(STTree *t_sttree);
STTree *cretree_i(int num,char *content,yyltype loc_info,int t_value,int i_value);
STTree *cretree_f(int num,char *content,yyltype loc_info,int t_value,float f_value);
STTree *cretree_c(int num,char *content,yyltype loc_info,int t_value,char *c_value);
STTree *entree(int num,char *content,yyltype loc_info,int n,...);

#endif
