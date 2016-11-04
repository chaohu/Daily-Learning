#include "ao.h"

int tabs = 0;
int tabc = 0;

int syntaxtree(STTree *sttree) {
	if(sttree != NULL) {
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->lineno);break;
			case 1: printf("%s\n",sttree->content);break;
			case 2: printf("%s: %s\n",sttree->content,sttree->value.c_value);break;
			case 3: printf("%s: %d\n",sttree->content,sttree->value.i_value);break;
			case 4: printf("%s: %f\n",sttree->content,sttree->value.f_value);break;
			default: ;
		}
		o_tree_c(sttree->C_next);
		o_tree_b(sttree->B_next);
		return 1;
	}
	else return 0;
}

int o_tree_c(STTree *sttree) {
	if(sttree != NULL) {
		tabs++;
		tabc = tabs;
		while(tabc) {
			printf("\t");
			tabc--;
		}
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->lineno);break;
			case 1: printf("%s\n",sttree->content);break;
			case 2: printf("%s: %s\n",sttree->content,sttree->value.c_value);break;
			case 3: printf("%s: %d\n",sttree->content,sttree->value.i_value);break;
			case 4: printf("%s: %f\n",sttree->content,sttree->value.f_value);break;
			default: ;
		}
		o_tree_c(sttree->C_next);
		o_tree_b(sttree->B_next);
	}
	return 1;
}

int o_tree_b(STTree *sttree) {
	if(sttree != NULL) {
		tabs--;
		tabc = tabs;
		while(tabc) {
			printf("\t");
			tabc--;
		}
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->lineno);break;
			case 1: printf("%s\n",sttree->content);break;
			case 2: printf("%s: %s\n",sttree->content,sttree->value.c_value);break;
			case 3: printf("%s: %d\n",sttree->content,sttree->value.i_value);break;
			case 4: printf("%s: %f\n",sttree->content,sttree->value.f_value);break;
			default: ;
		}
		o_tree_c(sttree->C_next);
		o_tree_b(sttree->B_next);
	}
	return 1;
}

STTree * cretree_i(char *content,int lineno,int t_value,int i_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
	strcpy(temp->content,content);
	temp->lineno = lineno;
	temp->value.i_value = i_value;
	temp->t_value = t_value;
	temp->C_next = NULL;
	return temp;
}

STTree * cretree_f(char *content,int lineno,int t_value,float f_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
	strcpy(temp->content,content);
	temp->lineno = lineno;
	temp->value.f_value = f_value;
	temp->t_value = t_value;
	temp->C_next = NULL;
	return temp;
}

STTree * cretree_c(char *content,int lineno,int t_value,char *c_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
	strcpy(temp->content,content);
	temp->lineno = lineno;
	strcpy(temp->value.c_value,c_value);
	temp->t_value = t_value;
	temp->C_next = NULL;
	return temp;
}

STTree * entree(char *content,int lineno,int n, ...){
	int i = 0;
	STTree *temp[n];
	STTree *root = (STTree *)malloc(sizeof(STTree));
	strcpy(root->content,content);
	root->lineno = lineno;
	root->C_next = NULL;
	root->B_next = NULL;
	va_list vap;
	va_start(vap, n);	
	while(i < n){
		temp[i] = va_arg(vap, STTree *);
		// temp[i] = *((STTree **)((char *)(&n) + sizeof(int) + i * sizeof(STTree *)));
		i++;
	}
	va_end(vap);
	i = 0;
	while(i < n){
		if(i) {
			temp[i-1]->B_next = temp[i];
		}
		else {
			root->C_next = temp[i];
		}
		i++;
	}
	return root;
}
