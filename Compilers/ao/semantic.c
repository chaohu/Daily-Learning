#include "ao.h"
#include "sbtree.h"

int hide_num = 0;   //隐藏变量名

int semantic(STTree *t_sttree) { 
    if(t_sttree->C_next) {
        addscope();
        deal_extdeflist(t_sttree->C_next);
        delscope();
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
        type1 = deal_specifier(t_sttree->C_next);
        deal_extdeclist(type1,t_sttree->C_next->B_next);
    }
    else if(t_sttree->C_next->B_next->num == 24) {//SEMI
        deal_specifier(t_sttree->C_next);
    }
    else if(t_sttree->C_next->B_next->num == 9) {//FunDec
        addscope();
        type1 = deal_specifier(t_sttree->C_next);
        deal_fundec(type1,t_sttree->C_next->B_next);
        deal_compst(type1,t_sttree->C_next->B_next->B_next);
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
        if(!strcmp(t_sttree->C_next->value.c_value,"int")) type->u.basic = 0;
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
        type = looksymbol(1,0,t_sttree->C_next->B_next->C_next->value.c_value);
        if(type == NULL) {
            printf("Error, 此结构类型未定义!@line:%d,column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            exit(0);
        }
    }
    else  {
        addscope();
        type = (Type)malloc(sizeof(Type_));
        type->kind= STRUCTURE;
        if(t_sttree->C_next->B_next->C_next) {
            if(looksymbol(1,0,t_sttree->C_next->B_next->C_next->value.c_value) == NULL) {
                type->u.structfield.name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->B_next->C_next->value.c_value) + 1));
                strcpy(type->u.structfield.name,t_sttree->C_next->B_next->C_next->value.c_value);
                type->u.structfield.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next->B_next);
                delscope();
                pro_stru(0,t_sttree->C_next->B_next->C_next->value.c_value,type,t_sttree->C_next->B_next->loc_info);
            }
            else {
                printf("此结构类型已存在@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
                exit(1);
            }
        }
        else {
            sprintf(hide_name,"%d",hide_num);
            hide_num++;
            strcpy(type->u.structfield.name,hide_name);
            type->u.structfield.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next);
            delscope();
            pro_stru(0,hide_name,type,t_sttree->C_next->loc_info);
        }
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
    if(t_sttree->C_next->B_next == NULL) {
        return deal_s_vardec(0,type,t_sttree->C_next);
    }
    else {
        printf("错误：不能结构体中初始化@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
        exit(1);
    }
}

/**
 * 名称：deal_s_vardec
 * 作者：ao
 * 功能：处理结构体中的vardec
 * 说明：kind(0:ID,1:ARRAY)
 */
FieldList deal_s_vardec(int kind,Type type,STTree *t_sttree) {
    FieldList fieldlist;
    if(t_sttree->C_next->num == 23) {   //ID
        if(kind) {
            type->u.array.name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->value.c_value) + 1));
            strcpy(type->u.array.name,t_sttree->C_next->value.c_value);
            pro_vari(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        }
        else pro_iden(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
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
        type1->u.array.name = NULL;
        fieldlist = deal_s_vardec(1,type1,t_sttree->C_next);
    }
    return fieldlist;
}

/**
 * 名称：deal_extdeclist
 * 作者：ao
 * 功能：处理extdeclist
 */
int deal_extdeclist(Type type,STTree *t_sttree) {
    deal_c_vardec(0,type,t_sttree->C_next);
    if(t_sttree->C_next->B_next != NULL) deal_extdeclist(type,t_sttree->C_next->B_next->B_next);
    return 1;
}

/**
 * 名称：deal_c_vardec
 * 作者：ao
 * 功能：处理函数体中的vardec
 * 说明：kind(0:ID,1:ARRAY)
 */
ParaList deal_c_vardec(int kind,Type type,STTree *t_sttree) {
    ParaList paralist = NULL;
    if(t_sttree->C_next->num == 23) {
        paralist = (ParaList)malloc(sizeof(ParaList_));
        if(kind) {
            type->u.array.name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->value.c_value) + 1));
            strcpy(type->u.array.name,t_sttree->C_next->value.c_value);
            pro_vari(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        }
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
        type1->u.array.name = NULL;
        paralist = deal_c_vardec(1,type1,t_sttree->C_next);
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
    return deal_c_vardec(0,type,t_sttree->C_next->B_next);
}

/**
 * 名称：deal_compst
 * 作者：ao
 * 功能：处理compst
 */
int deal_compst(Type retype,STTree *t_sttree) {
    if(t_sttree->C_next->B_next->num == 15) {
        deal_c_deflist(t_sttree->C_next->B_next);
        if(t_sttree->C_next->B_next->B_next->num == 13) deal_stmtlist(retype,t_sttree->C_next->B_next->B_next);
    }
    else if(t_sttree->C_next->B_next->num== 13) deal_stmtlist(retype,t_sttree->C_next->B_next);
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
        ParaList paralist = deal_c_vardec(0,type,t_sttree->C_next);
        Type type1 = paralist->type;
        Type type2 = deal_exp(t_sttree->C_next->B_next->B_next);
        if(type1->kind == 0) {
            if(type1->u.basic == 0) {
                if(type2->kind == 0 && type2->u.basic == 0) return 1;
                else {
                    printf("变量需为int型@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
                    exit(1);
                }
            }
            else if(type2->kind == 0) return 1;
        }
        printf("类型不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
        exit(1);
    }
    else deal_c_vardec(0,type,t_sttree->C_next);
    return 1;
}

/**
 * 名称：deal_stmtlist
 * 作者：ao
 * 功能：处理stmtlist
 */
int deal_stmtlist(Type retype,STTree *t_sttree) {
    deal_stmt(retype,t_sttree->C_next);
    if(t_sttree->C_next->B_next) deal_stmtlist(retype,t_sttree->C_next->B_next);
    return 1;
}

/**
 * 名称：deal_stmt
 * 作者：ao
 * 功能：处理stmt
 */
int deal_stmt(Type retype,STTree *t_sttree) {
    if(t_sttree->C_next->num == 19) deal_exp(t_sttree->C_next);
    else if(t_sttree->C_next->num == 12) deal_compst(retype,t_sttree->C_next);
    else if(t_sttree->C_next->num == 44) {
        Type type1 = deal_exp(t_sttree->C_next->B_next);
        if(!type_match(retype,type1)) {
            printf("返回值类型不正确@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            exit(1);
        }
    }
    else if(t_sttree->C_next->num == 45) {
        deal_exp(t_sttree->C_next->B_next->B_next);
        addscope();
        deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next);
        delscope();
        if(t_sttree->C_next->B_next->B_next->B_next->B_next->B_next) {
            addscope();
            deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next->B_next->B_next);
            delscope();
        }
    }
    else if(t_sttree->C_next->num == 47) {
        deal_exp(t_sttree->C_next->B_next->B_next);
        addscope();
        deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next);
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
    Type type1 = NULL,type2 = NULL;
    if(t_sttree->C_next->num == 19) {
        if(t_sttree->C_next->B_next->num == 26) {
            if(j_left(t_sttree->C_next)) {
                type1 = deal_exp(t_sttree->C_next);
                type2 = deal_exp(t_sttree->C_next->B_next->B_next);
                if(type1->kind == 0) {
                    if(type1->u.basic == 0) {
                        if(type2->kind == 0 && type2->u.basic == 0) return type1;
                        else {
                            printf("变量需为int型@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
                            exit(1);
                        }
                    }
                    else if(type2->kind == 0) return type1;
                }
                else if(type1->kind == 1) {
                    if(type2->kind == 1) {
                        while(type1 != NULL) {
                            if(type2 != NULL) {
                                if(type1->u.array.size == type2->u.array.size) {
                                    type1 = type1->u.array.elem;
                                    type2 = type2->u.array.elem;
                                }
                            }
                            else break;
                        }
                        if(type1 == NULL && type2 == NULL) return type1;
                    }
                }
                else if(type1->kind == 2) {
                    if(type2->kind ==2) {
                        if(!strcmp(type1->u.structfield.name,type2->u.structfield.name)) return type1;
                    }
                }
                printf("类型不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
            else {
                printf("表达式需要为左值表达式@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
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
                    if(type1->u.array.size > t_sttree->C_next->B_next->B_next->value.i_value) return type1->u.array.elem;
                    /*Type type3 = type1;
                    while(type3->kind != 0) {
                        type3 = type3->u.array.elem;
                    }*/
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
                FieldList t_fieldlist = type1->u.structfield.structure;
                while(t_fieldlist != NULL) {
                    if(!strcmp(t_fieldlist->name,t_sttree->C_next->B_next->B_next->value.c_value)) {
                        return t_fieldlist->type;
                    }
                    else t_fieldlist = t_fieldlist->tail;
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
            type1 = looksymbol(1,1,t_sttree->C_next->value.c_value);
            if(type1) {
                paratype = para_fun(t_sttree->C_next->value.c_value);
                if(t_sttree->C_next->B_next->B_next->num == 20) {
                    if(paratype.paranum > 0) {
                        if(deal_args(paratype.paralist,t_sttree->C_next->B_next->B_next)) return type1;
                        else {
                            printf("函数参数不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                            exit(1);
                        }
                    }
                    else {
                        printf("函数无参数@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                        exit(1);
                    }
                }
                else {
                    if(paratype.paranum == 0) return type1;
                    else {
                        printf("此函数有参数@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                        exit(1);
                    }
                }
            }
            else {
                printf("此函数未声明@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
        else {
            type1 = looksymbol(1,1,t_sttree->C_next->value.c_value);
            if(type1) return type1;
            else {
                printf("此变量未声明@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                exit(1);
            }
        }
    }
    else if(t_sttree->C_next->num == 21) {
        type1 = (Type)malloc(sizeof(Type_));
        type1->kind = BASIC;
        type1->u.basic = 0;
        return type1;
    }
    else if(t_sttree->C_next->num == 22) {
        type1 = (Type)malloc(sizeof(Type_));
        type1->kind = BASIC;
        type1->u.basic = 1;
        return type1;
    }
    return type1;
}

/**
 * 名称：deal_args
 * 作者：ao
 * 功能：处理args
 */
int deal_args(ParaList paralist,STTree *t_sttree) {
    Type type1 = deal_exp(t_sttree->C_next);
    if(paralist->type->kind == 0) {
        if(paralist->type->u.basic == 0) {
            if(type1->kind == 0 && type1->u.basic == 0) return 1;
        }
        else if(type1->kind == 0) return 1;
        else return 0;
    }
    else if(paralist->type->kind == 1) {
        if(type1->kind == 1) {
            if(!strcmp(paralist->type->u.array.name,type1->u.array.name)) return 1;
        }
        return 0;
    }
    else if(paralist->type->kind == 2) {
        if(type1->kind == 2) {
            if(!strcmp(paralist->type->u.structfield.name,type1->u.structfield.name)) return 1;
        }
        return 0;
    }
    if(t_sttree->C_next->B_next) {
        if(paralist->next) {
            if(deal_args(paralist->next,t_sttree->C_next->B_next->B_next)) return 1;
        }
        return 0;
    }
    else {
        if(paralist->next == NULL) return 1;
        else return 0;
    }
}

/**
 * 名称：type_match
 * 作者：ao
 * 功能：判断两个类型是否匹配
 */
int type_match(Type type1,Type type2) {
    int judge = 0;
    if(type1->kind == type2->kind) {
        if(type1->kind == 0) {
            if(type1->u.basic == type2->u.basic) judge = 1;
        }
        else if(type1->kind == 1) {
            if(!strcmp(type1->u.array.name,type2->u.array.name)) judge = 1;
        }
        else if(type1->kind == 2) {
            if(!strcmp(type1->u.structfield.name,type2->u.structfield.name)) judge = 1;
        }
    }
    return judge;
}

/**
 * 名称：j_left
 * 作者：ao
 * 功能：判断表达式是否为左值
 */
int j_left(STTree *t_sttree) {
    if(t_sttree->C_next->num == 23) return 1;
    else if(t_sttree->C_next->num == 19) {
        if(t_sttree->C_next->B_next->num == 39) {
            if(t_sttree->C_next->B_next->B_next->num == 19) {
                if(t_sttree->C_next->B_next->B_next->B_next->num == 40) return 1;
            }
        }
        else if(t_sttree->C_next->B_next->num == 34) {
            if(t_sttree->C_next->B_next->B_next->num == 23) return 1;
        }
    }
    return 0;
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
            if(!strcmp(c_value,t_token->symbol.function.name)) {
                paratype = t_token->symbol.function.paratype;break; 
            }
        t_token = t_token->next;
        }
    }
    return paratype;
}
