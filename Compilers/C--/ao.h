#ifndef AO_H
#define AO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

union T_value{
	int i_value;
	float f_value;
	char c_value[20];
};

typedef struct STTree{
	char content[9];
	int lineno;
	union T_value value;
	int t_value;
	struct STTree *C_next;
	struct STTree *B_next;
}STTree;

int syntaxtree(STTree *);
int o_tree_c(STTree *);
int o_tree_b(STTree *);
STTree *cretree_i(char *content,int lineno,int t_value,int i_value);
STTree *cretree_f(char *content,int lineno,int t_value,float f_value);
STTree *cretree_c(char *content,int lineno,int t_value,char *c_value);
STTree *entree(char *content,int lineno,int n,...);

#endif
