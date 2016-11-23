#include "ao.h"

int tabs = 0;
int tabc = 0;

int syntaxtree(STTree *sttree) {
	if(sttree != NULL) {
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->loc_info.first_line);break;
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

int o_tree_c(STTree *sttree) {
	tabs++;
	if(sttree != NULL) {
		tabc = tabs;
		while(tabc > 0) {
			printf("  ");
			tabc--;
		}
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->loc_info.first_line);break;
			case 1: printf("%s\n",sttree->content);break;
			case 2: printf("%s: %s\n",sttree->content,sttree->value.c_value);break;
			case 3: printf("%s: %d\n",sttree->content,sttree->value.i_value);break;
			case 4: printf("%s: %f\n",sttree->content,sttree->value.f_value);break;
			default: ;
		}
		o_tree_c(sttree->C_next);
		o_tree_b(sttree->B_next);
	}
	tabs--;
	return 1;
}

int o_tree_b(STTree *sttree) {
	if(sttree != NULL) {
		tabc = tabs;
		while(tabc > 0) {
			printf("  ");
			tabc--;
		}
		switch(sttree->t_value) {
			case 0: printf("%s (%d)\n",sttree->content,sttree->loc_info.first_line);break;
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

STTree * cretree_i(int num,char *content,yyltype loc_info,int t_value,int i_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
    temp->num = num;
	strcpy(temp->content,content);
	temp->loc_info = loc_info;
	temp->value.i_value = i_value;
	temp->t_value = t_value;
	temp->C_next = NULL;
	temp->B_next = NULL;
	return temp;
}

STTree * cretree_f(int num,char *content,yyltype loc_info,int t_value,float f_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
	temp->num = num;
    strcpy(temp->content,content);
	temp->loc_info = loc_info;
	temp->value.f_value = f_value;
	temp->t_value = t_value;
	temp->C_next = NULL;
	temp->B_next = NULL;
	return temp;
}

STTree * cretree_c(int num,char *content,yyltype loc_info,int t_value,char *c_value) {
	STTree * temp = (STTree *)malloc(sizeof(STTree));
	temp->num = num;
    strcpy(temp->content,content);
	temp->loc_info = loc_info;
	strcpy(temp->value.c_value,c_value);
	temp->t_value = t_value;
	temp->C_next = NULL;
	temp->B_next = NULL;
	return temp;
}

STTree * entree(int num,char *content,yyltype loc_info,int n, ...){
	int i = 0;
	STTree *temp[n];
	STTree *root = (STTree *)malloc(sizeof(STTree));
	root->num = num;
    strcpy(root->content,content);
	root->loc_info = loc_info;
	root->t_value = 0;
	root->C_next = NULL;
	root->B_next = NULL;
	va_list vap;
	va_start(vap, n);	
	while(i < n){
		temp[i] = va_arg(vap, STTree *);
		if(temp[i] == NULL) n--;
		// temp[i] = *((STTree **)((char *)(&n) + sizeof(int) + i * sizeof(STTree *)));
		else i++;
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
