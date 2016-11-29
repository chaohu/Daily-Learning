#include "ao.h"
#include "sbtree.h"

int semantic(STTree *t_sttree) { 
    if(t_sttree->C_next) deal_extdeflist(t_sttree->C_next);
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
        if(t_sttree->C_next->B_next) deal_extdeflist(t_sttree->C_next->B_next);
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
        deal_fundec(type1,t_sttree->C_next->B_next);
        deal_compst(t_sttree->C_next->B_next->B_next);
        delscope();
    }
    return  1;
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
        type->kind = BASIC;
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
            printf("error, no such symbol!@line:%d,column:%d",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            exit(0);
        }
    }
    else  {
        addscope();
        type = (Type)malloc(sizeof(Type_));
        type->kind = STRUCTURE;
        if(t_sttree->C_next->B_next->num == 6) {
            type->u.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next->B_next);
            pro_stru(t_sttree->C_next->B_next->C_next->value.c_value,type,t_sttree->C_next->B_next->loc_info);
        }
        else {
            type->u.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next);
            strcpy(hide_name,"$$");
            pro_stru(hide_name,type,t_sttree->C_next->loc_info);
        }
        delscope();
    }
    return type;
}

/**
 * 名称：deal_s_deflist
 * 作者：ao
 * 功能：处理结构体中的deflist
 */
FieldList deal_s_deflist(STTree *t_sttree) {
    FieldList fieldlist = (FieldList)malloc(sizeof(FieldList_)); 
    fieldlist = deal_s_def(t_sttree->C_next);
    if(t_sttree->C_next->B_next) fieldlist->tail = deal_s_deflist(t_sttree->C_next->B_next);
    else fieldlist->tail = NULL;
    return fieldlist;
}



/**
 * 名称：deal_s_def
 * 作者：ao
 * 功能：处理结构体中的def
 */
FieldList deal_s_def(STTree *t_sttree) {
    Type type = deal_specifier(t_sttree->C_next);
    return deal_s_declist(type,t_sttree->C_next->B_next);
}

/**
 * 名称：deal_s_declist
 * 作者：ao
 * 功能：处理结构体中的declist
 */
FieldList deal_s_declist(Type type,STTree *t_sttree) {
    FieldList fieldlist;
    fieldlist = deal_s_dec(type,t_sttree->C_next);
    if (t_sttree->C_next->B_next != NULL) fieldlist->tail = deal_s_declist(type,t_sttree->C_next->B_next->B_next);
    return fieldlist;
}

/**
 * 名称：deal_s_dec
 * 作者：ao
 * 功能：处理结构体中的dec
 */
FieldList deal_s_dec(Type type,STTree *t_sttree) {
    FieldList fieldlist;
    if(t_sttree->C_next->B_next == NULL) {
        fieldlist = (FieldList)malloc(sizeof(FieldList_));
        fieldlist->tail = NULL;
        fieldlist->type = type;
        fieldlist->name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->value.c_value)+1));
        strcpy(fieldlist->name,t_sttree->C_next->value.c_value);
    }
    else {
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = ARRAY;
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
        fieldlist->name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->value.c_value)+1));
        strcpy(fieldlist->name,t_sttree->C_next->value.c_value);
        fieldlist->tail = NULL;
    }
    else {      //数组
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = ARRAY;
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
ParaList deal_vardec(int kind,Type type,STTree *t_sttree) {
    ParaList paralist = (ParaList)malloc(sizeof(ParaList_));
    if(t_sttree->C_next->num == 23) {
        if(kind) pro_vari(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        else pro_iden(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        paralist->name = (char *)malloc(sizeof(char) * strlen(t_sttree->C_next->value.c_value));
        strcpy(paralist->name,t_sttree->C_next->value.c_value);
        paralist->type = type;
        paralist->next = NULL;
    }
    else if(t_sttree->C_next->num == 8) {
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = ARRAY;
        type1->u.array.elem = type;
        type1->u.array.size = t_sttree->C_next->B_next->B_next->value.i_value;
        deal_vardec(1,type1,t_sttree->C_next);
    }
    return paralist;
}

/**
 * 名称：deal_fundec
 * 作者：ao
 * 功能：处理fundec
 */
int deal_fundec(Type retype,STTree *t_sttree) {
    if(t_sttree->C_next->B_next->B_next->num == 10) {
        int paranum = 0;
        ParaList paralist = deal_varlist(&paranum,t_sttree->C_next->B_next->B_next);
        pro_func(t_sttree->C_next->value.c_value,retype,paranum,paralist,t_sttree->C_next->loc_info);
    }
    else pro_func(t_sttree->C_next->value.c_value,retype,0,NULL,t_sttree->C_next->loc_info);
    return 1;
}

/**
 * 名称：deal_varlist
 * 作者：ao
 * 功能：处理varlist
 * 说明：参数按左到右顺序存入链表
 */
ParaList deal_varlist(int *paranum,STTree *t_sttree) {
    (*paranum)++;
    ParaList paralist = deal_paramdec(t_sttree->C_next);
    if(t_sttree->C_next->B_next == NULL) {
        paralist->next = NULL;
    }
    else {
        paralist->next = deal_varlist(paranum,t_sttree->C_next->B_next->B_next);
    }
    return paralist;
}

/**
 * 名称：deal_paramdec
 * 作者：ao
 * 功能：处理paramdec
 */
ParaList deal_paramdec(STTree *t_sttree) {
    Type type = deal_specifier(t_sttree->C_next);
    ParaList paralist = deal_vardec(0,type,t_sttree->C_next->B_next);
    return paralist;
}

/**
 * 名称：deal_compst
 * 作者：ao
 * 功能：处理compst
 */
int deal_compst(STTree *t_sttree) {
    deal_c_deflist(t_sttree->C_next->B_next);
    deal_stmtlist(t_sttree->C_next->B_next->B_next);
    return 1;
}

/**
 * 名称：deal_c_deflist
 * 作者：ao
 * 功能：处理函数体中的deflist
 */
int deal_c_deflist(STTree *t_sttree) {
    deal_c_def(t_sttree->C_next);
    if(t_sttree->C_next->B_next) deal_c_deflist(t_sttree->C_next->B_next);
    return 1;
}

/**
 * 名称：deal_c_def
 * 作者：ao
 * 功能：处理函数体中的def
 */
int deal_c_def(STTree *t_sttree) {
    Type type = deal_specifier(t_sttree->C_next);
    deal_c_declist(type,t_sttree->C_next->B_next);
    return 1;
}

/**
 * 名称：deal_c_declist
 * 作者：ao
 * 功能：处理函数体中的declist
 */
int deal_c_declist(Type type,STTree *t_sttree) {
    deal_c_dec(type,t_sttree->C_next);
    if(t_sttree->C_next->B_next) deal_c_declist(type,t_sttree->C_next->B_next->B_next);
    return 1;
}

/**
 * 名称：deal_c_dec
 * 作者：ao
 * 功能：处理函数体中的dec
 */
int deal_c_dec(Type type,STTree *t_sttree) {
    if(t_sttree->C_next->B_next) {
        //TODO：类型检查
    }
    else deal_c_vardec(0,type,t_sttree->C_next);
    return 1;
}

/**
 * 名称：deal_c_vardec
 * 作者：ao
 * 功能：处理函数体中的vardec
 * 说明：kind(0:ID,1:ARRAY)
 */
int deal_c_vardec(int kind,Type type,STTree *t_sttree) {
    if(t_sttree->C_next->num == 23) {
        if(kind) pro_vari(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        else pro_iden(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
    }
    else {
        Type type1 = (Type)malloc(sizeof(Type_));
        type1->kind = ARRAY;
        type1->u.array.size = t_sttree->C_next->B_next->B_next->value.i_value;
        type1->u.array.elem = type;
        deal_c_vardec(1,type1,t_sttree->C_next);
    }
    return 1;
}

/**
 * 名称：deal_stmtlist
 * 作者：ao
 * 功能：处理stmtlist
 */
int deal_stmtlist(STTree *t_sttree) {
    deal_stmt(t_sttree->C_next);
    if(t_sttree->C_next->B_next) deal_stmtlist(t_sttree->C_next->B_next);
    return 1;
}

/**
 * 名称：deal_stmt
 * 作者：ao
 * 功能：处理stmt
 */
int deal_stmt(STTree *t_sttree) {
    if(t_sttree->C_next->num == 19) deal_exp(t_sttree->C_next);
    else if(t_sttree->C_next->num == 12) deal_compst(t_sttree->C_next);
    else if(t_sttree->C_next->num == 44) deal_exp(t_sttree->C_next->B_next);
    else if(t_sttree->C_next->num == 45) {
        deal_exp(t_sttree->C_next->B_next->B_next);
        addscope();
        deal_stmt(t_sttree->C_next->B_next->B_next->B_next->B_next);
        delscope();
        if(t_sttree->C_next->B_next->B_next->B_next->B_next->B_next) {
            addscope();
            deal_stmt(t_sttree->C_next->B_next->B_next->B_next->B_next->B_next->B_next);
            delscope();
        }
    }
    else if(t_sttree->C_next->num == 47) {
        deal_exp(t_sttree->C_next->B_next->B_next);
        addscope();
        deal_stmt(t_sttree->C_next->B_next->B_next->B_next->B_next);
        delscope();
    }
    return 1;
}

/**
 * 名称：deal_exp
 * 作者：ao
 * 功能：处理exp
 */
Type deal_exp(STTree *t_sttree) {
    Type type1,type2;
    if(t_sttree->C_next->num == 19) {
        if(t_sttree->C_next->B_next->num == 26) {
            type1 = deal_exp(t_sttree->C_next);
            type2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(match(type1,type2)) return type1;
            else {
                printf("类型不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else if(t_sttree->C_next->B_next->num == 32 || t_sttree->C_next->B_next->num == 33) {
            type1 = deal_exp(t_sttree->C_next);
            type2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(type1->kind == 0 && type2->kind == 0 && type1->u.basic == 0 && type2->u.basic == 0) {
                return type1;
            }
            else {
                printf("两者类型必需均为int型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else if(t_sttree->C_next->B_next->num == 27) {
            type1 = deal_exp(t_sttree->C_next);
            type2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(type1->kind == 0 && type2->kind == 0) {
                if(type1->u.basic) return type1;
                else return type2;
            }
            else {
                printf("两者类型必须均为int或float@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else if(t_sttree->C_next->B_next->num == 28 || t_sttree->C_next->B_next->num == 29 || t_sttree->C_next->B_next->num == 30 || t_sttree->C_next->B_next->num == 31) {
            type1 = deal_exp(t_sttree->C_next);
            type2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(type1->kind == 0 && type2->kind == 0) {
                if(type1->u.basic) return type1;
                else return type2;
            }
            else {
                printf("两者类型必须均为int或float@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else if(t_sttree->C_next->B_next->num == 39) {
            type1 = deal_exp(t_sttree->C_next);
            type2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(type1->kind == 1) {
                if(type2->kind == 0 && type2->u.basic == 0) {
                    while(type1->kind != 0) {
                        type1 = type1->u.array.elem;
                    }
                    return type1;
                }
                else {
                    printf("需为int@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
                    exit(1);
                }
            }
            else {
                printf("变量不是数组类型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else if(t_sttree->C_next->B_next->num == 34) {
            type1 = deal_exp(t_sttree->C_next);
            if(type1->kind == 2){
                while(type1->u.structure != NULL) {
                    if(strcmp(type1->u.structure->name,t_sttree->C_next->B_next->B_next->value.c_value)) {
                        return type1->u.structure->type;
                    }
                    else type1->u.structure = type1->u.structure->tail;
                }
                printf("该结构体没有此成员@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
                exit(1);
            }
            else {
                printf("变量需为结构体类型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
    }
    else if(t_sttree->C_next->num == 37) {
        return deal_exp(t_sttree->C_next->B_next);
    }
    else if(t_sttree->C_next->num == 29) {
        type1 = deal_exp(t_sttree->C_next->B_next);
        if(type1->kind == 0) {
            return type1;
        }
        else {
            printf("变量需为int或float型@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            exit(1);
        }
    }
    else if(t_sttree->C_next->num == 35) {
        type1 = deal_exp(t_sttree->C_next->B_next);
        if(type1->kind == 0 && type1->u.basic == 0) return type1;
        else {
            printf("变量需为int型@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            exit(1);
        }
    }
    else if(t_sttree->C_next->num == 23) {
        if(t_sttree->C_next->B_next) {
            ParaType paratype;
            if(t_sttree->C_next->B_next->B_next->num == 20) {
                type1 = t_exit(1,t_sttree->C_next->value.c_value);
                if(type1) {
                    paratype = para_fun(t_sttree->C_next->value.c_value);
                    if(deal_args(paratype.paralist,t_sttree->C_next->B_next->B_next)) return type1;
                    else {
                        printf("函数参数不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                        exit(1);
                    }
                }
                else {
                    printf("此函数未声明@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                    exit(1);
                }

            }
            else {
                type1 = t_exit(1,t_sttree->C_next->value.c_value);
                if(type1) {
                    paratype = 

            }
        }
        else {

        }
    }
    else if(t_sttree->C_next->num == 21) {

    }
    else if(t_sttree->C_next->num == 22) {

    }
}

/**
 * 名称：deal_args
 * 作者：ao
 * 功能：处理args
 */
int deal_args(ParaList paralist,STTree *t_sttree) {

}

/**
 * 名称：match
 * 作者：ao
 * 功能：判断两个ID的类型是否匹配
 */
int match(Type type1,Type type2) {

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
        if(t_token->kind == kind) {
            switch(kind) {
                case 0: if(strcmp(c_value,t_token->symbol.identity.name)) type = t_token->symbol.identity.type;break;
                case 1: if(strcmp(c_value,t_token->symbol.function.name)) type = t_token->symbol.function.retype;break;
                case 2: if(strcmp(c_value,t_token->symbol.variable.name)) type = t_token->symbol.variable.type;break;
                case 3: if(strcmp(c_value,t_token->symbol.structure.name)) type = t_token->symbol.structure.type;break;
            }
        }
        t_token = t_token->next;
    }
    return type;
}

/**
 * 名称：para_fun
 * 作者：ao
 * 功能：返回函数的参数ParaType
 */
ParaType para_fun(char *c_value) {
    ParaType paratype;
    paratype.paranum = 0;
    paratype.paralist = NULL;
    unsigned num = hash_pjw(c_value);
    TOKEN *t_token = token[num].next;
    while(t_token) {
        if(t_token->kind == 1) {
            if(strcmp(c_value,t_token->symbol.function.name)) {
                paratype = t_token->symbol.function.paratype;break; 
            }
        t_token = t_token->next;
        }
    }
    return paratype;
}
