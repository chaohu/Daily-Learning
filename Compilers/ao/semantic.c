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
 * 名称：deal_extdeflist
 * 作者：ao
 * 功能：处理extdeflist
 */
int deal_extdeflist(STTree *t_sttree) {
    if(t_sttree->C_next != NULL) {
        deal_extdef(t_sttree->C_next);
        deal_extdeflist(t_sttree->C_next->B_next)
    }
    return 1;
}

/**
 * 名称：deal_extdef
 * 作者：ao
 * 功能：处理extdef
 */
int deal_extdef(STTree *t_sttree) {
    Type type1;
    if(t_sttree->C_next->B_next->num == 3) {    //ExtDecList
        addscope();
        type1 = deal_specifier(t_sttree->C_next);
        deal_extdeclist(type1,t_sttree->C_next->B_next);
    }
    else if(t_sttree->C_next->B_next->num == 24) {//SEMI
        deal_specifier(t_sttree->C_next);
    }
    else if(t_sttree->C_next->B_next->num == 9) {//FunDec
        type1 = deal_specifier(t_sttree->C_next);
        addscope();
        deal_fundec(t_sttree->C_next->B_next);
        deal_compst(t_sttree->C_next->B_next->B_next);
        delscope();
    }
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
        type = t_exit(4,t_sttree->C_next->B_next->value.c_value);
        if(type == NULL) {
            printf("error, no such symbol!@line:,column:");
            exit(0);
        }
    }
    else  {
        type = (Type)malloc(sizeof(Type_));
        type->kind = type->STRUCTURE;
        if(t_sttree->C_next->B_next->num == 6) {
            type->u.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next->B_next);
            pro_stru(t_sttree->C_next->B_next->C_next->value.c_value,type);
        }
        else {
            char name[4] = "@@@";
            type->u.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next);
            pro_stru(name,type);
        }
    }
    return type;
}

/**
 * 名称：deal_s_deflist
 * 作者：ao
 * 功能：处理结构中的deflist
 */
FieldList deal_s_deflist(STTree *t_sttree) {
    FieldList fieldlist = (FieldList)malloc(sizeof(FieldList_)); 
    if(t_sttree->C_next == NULL) return NULL;
    else {
        fieldlist = deal_def(t_sttree->C_next);
        fieldlist->tail = deal_s_deflist(t_sttree->C_next->B_next);
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
    FieldList fieldlist;
    fieldlist = deal_dec(type,t_sttree->C_next);
    if (t_sttree->C_next->B_next != NULL) fieldlist->tail = deal_declist(type,t_sttree->C_next->B_next->B_next);
    return fieldlist;
}

/**
 * 名称：deal_dec
 * 作者：ao
 * 功能：处理dec
 */
FieldList deal_dec(Type type,STTree *t_sttree) {
    FieldList fieldlist;
    if(t_sttree->C_next->B_next == NULL) {
        fieldlist = (FieldList)malloc(sizeof(FieldList_));
        fieldlist->tail = NULL;
        fieldlist->type = type;
        strcpy(fieldlist->name,t_sttree->C_next->value.c_value);
    }
    else {
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = type1->ARRAY;
        type1->u.array.size = t_sttree->C_next->B_next->B_next->value.i_value;
        type1->u.array.elem = type;
        fieldlist = deal_s_vardec(type1,t_sttree->C_next);
    }
    return fieldlist;
}

/**
 * 名称：deal_s_vardec
 * 作者：ao
 * 功能：处理结构体中的vardec
 */
FieldList deal_s_vardec(Type type,STTree *t_sttree) {
    FieldList fieldlist;
    if(t_sttree->C_next->num == 23) {   //ID
        fieldlist = (FieldList)malloc(sizeof(FieldList_));
        fieldlist->type = type;
        strcpy(fieldlist->name,t_sttree->C_next->value.c_value);
        fieldlist->tail = NULL;
    }
    else {      //数组
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = type1->ARRAY;
        type1->u.array.size = t_sttree->C_next->B_next->B_next->value.i_value;
        type1->u.array.elem = type;
        fieldlist = deal_s_vardec(type1,t_sttree->C_next);
    }
    return fieldlist;
}

/**
 * 名称：deal_extdeclist
 * 作者：ao
 * 功能：处理extdeclist
 */
int deal_extdeclist(Type type,STTree *t_sttree) {
    deal_vardec(0,type,t_sttree->C_next);
    if(t_sttree->C_next->B_next != NULL) deal_extdeclist(type,t_sttree->C_next->B_next->B_next);
    return 1;
}

/**
 * 名称：deal_vardec
 * 作者：ao
 * 功能：处理vardec
 * 说明：kind(0:ID,1:ARRAY)
 */
int deal_vardec(int kind,Type type,STTree *t_sttree) {
    if(t_sttree->C_next->num == 23) {
        if(kind) pro_vari(t_sttree->C_next->value.c_value,type);
        else pro_iden(t_sttree->C_next->value.c_value,type);
    }
    else {
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = type1->ARRAY;
        type1->u.array.elem = type;
        type1->u.array.size = t_sttree->C_next->B_next->B_next->value.i_value;
        deal_vardec(1,type,t_sttree->C_next);
    }
    return 1;
}

/**
 * 名称：deal_fundec
 * 作者：ao
 * 功能：处理fundec
 */
int deal_fundec(STTree *t_sttree) {

}

/**
 * 名称：deal_compst
 * 作者：ao
 * 功能：处理compst
 */
int deal_compst(STTree *t_sttree) {

}

/**
 * 名称：t_exit
 * 作者：ao
 * 功能：检查symbol是否存在，若存在返回symbol类型
 * 说明：kind(0:ID,1:FU,2:VA,3:ST)
 */
Type t_exit(int kind,char *c_value) {
    Type type = NULL;
    unsigned num = hash_pjw(c_value);
    TOKEN *t_token = token[num].next;
    while(t_token) {
        switch(kind) {
            case 0: if(strcmp(c_value,t_token->symbol.identity.name)) type = t_token->symbol.identity.type;break;
            case 1: if(strcmp(c_value,t_token->symbol.function.name)) type = t_token->symbol.function.retype;break;
            case 2: if(strcmp(c_value,t_token->symbol.variable.name)) type = t_token->symbol.variable.type;break;
            case 3: if(strcmp(c_value,t_token->symbol.structure.name)) type = t_token->symbol.structure.type;break;
        }
        t_token = t_token->next;
    }
    return type;
}
