#include "ao.h"
#include "sbtree.h"

int semantic(STTree *t_sttree) { 
    if(t_sttree != NULL) {
        if(t_sttree->num == 4) {
            if(t_sttree->C_next->num == 36) {
                Type type;
                type = cre_type_b(t_sttree->C_next);
                if(t_sttree->B_next->num == 9) {
                    //pro_func(t_sttree->B_next->C_next->value.c_value,type,type);
                }
                else if(t_sttree->B_next->num == 3) {
                }
                t_sttree = t_sttree->C_next;
            }
            else if(t_sttree->C_next->num == 5) {
                t_sttree = t_sttree->C_next;
                if(t_sttree->B_next->num == 6||t_sttree->B_next->num == 41) {
                    Type type;
                    if(t_sttree->B_next->num == 6) {
                        type = cre_type_s(t_sttree->B_next->B_next);
                        pro_stru(t_sttree->B_next->C_next->value.c_value,type);
                        t_sttree = t_sttree->B_next->B_next->B_next->B_next;
                    }
                    else {
                        type = cre_type_s(t_sttree->B_next);
                        pro_stru(hide_name,type);
                        t_sttree = t_sttree->B_next->B_next->B_next;
                    }
                }
            }
        }
        else if(t_sttree->num == 41) addscope();
        else if(t_sttree->num == 42) delscope();
        s_tree_c(t_sttree->C_next);
        s_tree_b(t_sttree->B_next);
    }
    return 1;
}

int s_tree_c(STTree *t_sttree) {
    if(t_sttree != NULL) {
        if(t_sttree->num == 2) {
        }
    }
    return 1;
}

int s_tree_b(STTree *t_sttree) {
    if(t_sttree != NULL) {
        if(t_sttree->num ==2) {
        }
    }
    return 1;
}

/**
 * 名称：deal_specifier
 * 作者：ao
 * 功能：处理specifier
 */
Type deal_specifier(STTree *t_sttree) {
    Type type = NULL;
    if(t_sttree->C_next->num == 36) {
        type = (Type)malloc(sizeof(Type_));
        type->kind = type->BASIC;
        if(strcmp(t_sttree->C_next->value.c_value,"int")) type->u.basic = 0;
        else type->u.basic = 1;
    }
    else if(t_sttree->C_next->num == 5) {
        type = deal_structspecifier(t_sttree->C_next);
    }
    return type;
}

/**
 * 名称：deal_structspecifier
 * 作者：ao
 * 功能：处理structspecifier
 */
Type deal_structspecifier(STTree *t_sttree) {
    Type type = NULL;
    if(t_sttree->C_next->B_next->num == 7) {
        type = t_exit(t_sttree->C_next->B_next->value.c_value);
        if(type == NULL) {
            printf("error, no such symbol!@line:,column:");
            exit(0);
        }
    }
    else  {
        type = (Type)malloc(sizeof(Type_));
        type->kind = type->STRUCTURE;
        if(t_sttree->C_next->B_next->num == 6) {
            type->u.structure = s_deal_deflist(t_sttree->C_next->B_next->B_next->B_next);
            pro_stru(t_sttree->C_next->B_next->C_next->value.c_value,type);
        }
        else {
            char name[4] = "@@@";
            type->u.structure = s_deal_deflist(t_sttree->C_next->B_next->B_next);
            pro_stru(name,type);
        }
    }
    return type;
}

/**
 * 名称：s_deal_deflist
 * 作者：ao
 * 功能：处理结构中的deflist
 */
FieldList s_deal_deflist(STTree *t_sttree) {
    FieldList fieldlist = (FieldList)malloc(sizeof(FieldList_)); 
    if(t_sttree->C_next == NULL) return NULL;
    else {
        fieldlist = deal_def(t_sttree->C_next);
        fieldlist->tail = s_deal_deflist(t_sttree->C_next->B_next);
        return fieldlist;
    }
}

/**
 * 名称：c_deal_deflist
 * 作者：ao
 * 功能：处理函数体中的deflist
 */
int c_deal_deflist(STTree *t_sttree) {

}

/**
 * 名称：deal_def
 * 作者：ao
 * 功能：处理def
 */
FieldList deal_def(STTree *t_sttree) {
    Type type = deal_specifier(t_sttree->C_next);
    return deal_declist(type,t_sttree->C_next->B_next);
}

/**
 * 名称：deal_declist
 * 作者：ao
 * 功能：处理declist
 */
FieldList deal_declist(Type type,STTree *t_sttree) {
    FieldList fieldlist = (FieldList)malloc(sizeof(FieldList_));
    fieldlist->type = type;
    fieldlist->tail = NULL;
    fieldlist->name = deal_dec(t_sttree->C_next);
    if (t_sttree->C_next->B_next != NULL) fieldlist->tail = deal_declist(type,t_sttree->C_next->B_next->B_next);
    return fieldlist;
}

/**
 * 名称：deal_dec
 * 作者：ao
 * 功能：处理dec
 */
char *deal_dec(STTree *t_sttree) {
    
}

/**
 * 名称：t_exit
 * 作者：ao
 * 功能：检查symbol是否存在，若存在返回symbol类型
 */
Type t_exit(char *c_value) {
    unsigned num = hash_pjw(c_value);

    while(token[num]) {

}
