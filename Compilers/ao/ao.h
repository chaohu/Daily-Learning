#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef AO_H
#define AO_H 1

extern FILE* yyin;
extern int yydebug;
extern int yyparse(void);
extern void yyerror(char const*);

#undef YYDEBUG
#define YYDEBUG 1

#undef YYLTYPE
#define YYLTYPE yyltype

typedef struct YYLTYPE {    //结点坐标信息结构
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} yyltype;

union T_value{      //结点值联合
	int i_value;
	float f_value;
	char c_value[20];
};

typedef struct STTree{
    int num;                //结点类型编号
	char content[17];       //结点名
	yyltype loc_info;       //结点坐标信息
	union T_value value;    //结点值
	int t_value;            //结点种类
	struct STTree *C_next;  //子结点
	struct STTree *B_next;  //兄弟结点
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
