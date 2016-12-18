#include "ao.h"

int hide_num = 0;   //隐藏变量名

int semantic(STTree *t_sttree) {
    char st_name[12] = "sb_file.txt";
    if(!(sb_file = fopen(st_name, "w"))) {
        perror(st_name);
        return 1;
    }
    if(t_sttree->C_next) {
        addscope();
        deal_extdeflist(t_sttree->C_next);
        delscope();
    }
    fclose(sb_file);
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
    Tp_Op tp_op;
    tp_op.type = NULL;
    tp_op.op = NULL;
    if(t_sttree->C_next->B_next->num == 7) {
        tp_op = looksymbol(1,0,t_sttree->C_next->B_next->C_next->value.c_value);
        if(tp_op.type == NULL) {
            printf("错误：结构体类型\"%s\"未定义!@line:%d,column:%d\n",t_sttree->C_next->B_next->C_next->value.c_value,t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
        }
    }
    else  {
        tp_op.type = (Type)malloc(sizeof(Type_));
        tp_op.type->kind= STRUCTURE;
        if(t_sttree->C_next->B_next->C_next) {
            if(looksymbol(1,0,t_sttree->C_next->B_next->C_next->value.c_value).type == NULL) {
                addscope();
                tp_op.type->u.structfield.name = (char*)malloc(sizeof(char)*(strlen(t_sttree->C_next->B_next->C_next->value.c_value) + 1));
                strcpy(tp_op.type->u.structfield.name,t_sttree->C_next->B_next->C_next->value.c_value);
                tp_op.type->u.structfield.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next->B_next);
                delscope();
                pro_stru(0,t_sttree->C_next->B_next->C_next->value.c_value,tp_op.type,t_sttree->C_next->B_next->loc_info);
            }
            else {
                printf("错误：结构体类型\"%s\"已存在@line:%d column:%d\n",t_sttree->C_next->B_next->C_next->value.c_value,t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
            }
        }
        else {
            addscope();
            sprintf(hide_name,"%d",hide_num);
            hide_num++;
            strcpy(tp_op.type->u.structfield.name,hide_name);
            tp_op.type->u.structfield.structure = deal_s_deflist(t_sttree->C_next->B_next->B_next);
            delscope();
            pro_stru(0,hide_name,tp_op.type,t_sttree->C_next->loc_info);
        }
    }
    return tp_op.type;
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
    if(t_sttree->C_next->B_next) {
        printf("错误：不能结构体中初始化@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
    }
    return deal_s_vardec(0,type,t_sttree->C_next);
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
        else {
            pro_iden(t_sttree->C_next->value.c_value,type,t_sttree->C_next->loc_info);
        }
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
    InterCode IC = (InterCode)malloc(sizeof(InterCode_));
    IC->kind = FUNC_D;
    strcpy(IC->u.func_d.name,t_sttree->C_next->value.c_value);
    if(t_sttree->C_next->B_next->B_next->num == 10) {
        int paranum = 0;
        ParaList paralist = deal_varlist(&paranum,t_sttree->C_next->B_next->B_next);
        if(pro_func(t_sttree->C_next->value.c_value,retype,paranum,paralist,t_sttree->C_next->loc_info)) {
            emit(IC);
            InterCode _IC[paranum];
            while(paralist) {
                paranum--;
                _IC[paranum] = (InterCode)malloc(sizeof(InterCode_));
                _IC[paranum]->kind = PARAM;
                _IC[paranum]->u.param.param = looksymbol(1,1,paralist->name).op;
                emit(_IC[paranum]);
                paralist = paralist->next;
            }
        }
    }
    else if(pro_func(t_sttree->C_next->value.c_value,retype,0,NULL,t_sttree->C_next->loc_info)) emit(IC);
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
        ParaList paralist = deal_c_vardec(0,type,t_sttree->C_next);
        Type type1 = paralist->type;
        Tp_Op tp_op = deal_exp(t_sttree->C_next->B_next->B_next);
        if(type1 && tp_op.type) {
            if(type_match(1,type1,tp_op.type,t_sttree->C_next,t_sttree->C_next->B_next->B_next)) {
                if(type->kind == 0) {
                    if(t_sttree->C_next->C_next->num == 23) {
                        InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                        IC->kind = ASSIGN;
                        IC->u.assign.left = looksymbol(1,1,t_sttree->C_next->C_next->value.c_value).op;
                        IC->u.assign.right = tp_op.op;
                        emit(IC);
                        return 1;
                    }
                    else {
                        printf("错误：暂时不支持对数组定义时初始化\n");
                        return 0;
                    }
                }
                else {
                    printf("错误：暂时不支持结构数组的翻译\n");
                    return 0;
                }
            }
            else return 0;
        }
        else return 0;
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
        Tp_Op tp_op = deal_exp(t_sttree->C_next->B_next);
        if(!type_match(0,retype,tp_op.type,t_sttree->C_next->B_next,t_sttree->C_next->B_next)) {
            printf("错误：返回值类型不正确@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
        }
        else {
            InterCode IC = (InterCode)malloc(sizeof(InterCode_));
            IC->kind = RETURN;
            IC->u.retop.result = tp_op.op;
            emit(IC);
        }
    }
    else if(t_sttree->C_next->num == 45) {
        Tp_Op tp_op = deal_exp(t_sttree->C_next->B_next->B_next);
        InterCode ICI = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICL1 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICL2 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICG1 = (InterCode)malloc(sizeof(InterCode_));
        ICI->kind = IF;
        ICI->u.ifop.relop = tp_op.op;
        ICL1->kind = LABEL;
        ICL1->u.label.label = newlabel();
        ICL2->kind = LABEL;
        ICL2->u.label.label = newlabel();
        ICI->u.ifop.label = ICL1->u.label.label;
        ICG1->kind = GOTO;
        ICG1->u.gtop.gtop = ICL2->u.label.label;
        addscope();
        emit(ICI);
        emit(ICG1);
        emit(ICL1);
        deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next);
        delscope();
        if(t_sttree->C_next->B_next->B_next->B_next->B_next->B_next) {
            InterCode ICL3 = (InterCode)malloc(sizeof(InterCode_));
            InterCode ICG2 = (InterCode)malloc(sizeof(InterCode_));
            ICL3->kind = LABEL;
            ICL3->u.label.label = newlabel();
            ICG2->kind = GOTO;
            ICG2->u.gtop.gtop = ICL3->u.label.label;
            emit(ICG2);
            addscope();
            emit(ICL2);
            deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next->B_next->B_next);
            delscope();
            emit(ICL3);
        }
        else emit(ICL2);
    }
    else if(t_sttree->C_next->num == 47) {
        Tp_Op tp_op = deal_exp(t_sttree->C_next->B_next->B_next);
        InterCode ICI = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICL1 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICL2 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICL3 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICG1 = (InterCode)malloc(sizeof(InterCode_));
        InterCode ICG2 = (InterCode)malloc(sizeof(InterCode_));
        ICL1->kind = LABEL;
        ICL1->u.label.label = newlabel();
        ICL1->kind = LABEL;
        ICL2->u.label.label = newlabel();
        ICL3->kind = LABEL;
        ICL3->u.label.label = newlabel();
        ICI->kind = IF;
        ICI->u.ifop.relop = tp_op.op;
        ICI->u.ifop.label = ICL2->u.label.label;
        ICG1->kind = GOTO;
        ICG1->u.gtop.gtop = ICL3->u.label.label;
        ICG2->kind = GOTO;
        ICG2->u.gtop.gtop = ICL1->u.label.label;
        emit(ICL1);
        emit(ICI);
        emit(ICG1);
        addscope();
        emit(ICL2);
        deal_stmt(retype,t_sttree->C_next->B_next->B_next->B_next->B_next);
        emit(ICG2);
        delscope();
        emit(ICL3);
    }
    return 1;
}

/**
 * 名称：deal_exp
 * 作者：ao
 * 功能：处理exp
 */
Tp_Op deal_exp(STTree *t_sttree) {
    Tp_Op tp_op1,tp_op2;
    tp_op1.type = NULL;
    tp_op1.op = NULL;
    tp_op2.type = NULL;
    tp_op2.op= NULL;
    if(t_sttree->C_next->num == 19) {
        if(t_sttree->C_next->B_next->num == 26) {
            if(j_left(t_sttree->C_next)) {
                tp_op1 = deal_exp(t_sttree->C_next);
                tp_op2 = deal_exp(t_sttree->C_next->B_next->B_next);
                if(tp_op1.type && tp_op2.type) {
                    type_match(1,tp_op1.type,tp_op2.type,t_sttree->C_next,t_sttree->C_next->B_next->B_next);

                    InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                    IC->kind = ASSIGN;
                    IC->u.assign.left = tp_op1.op;
                    IC->u.assign.right = tp_op2.op;
                    emit(IC);
                }
                return tp_op1;
            }
            else {
                printf("错误：表达式需要为左值表达式@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else if(t_sttree->C_next->B_next->num == 32 || t_sttree->C_next->B_next->num == 33) {
            tp_op1 = deal_exp(t_sttree->C_next);
            tp_op2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(tp_op1.type->kind == 0 && tp_op2.type->kind == 0 && tp_op1.type->u.basic == 0 && tp_op2.type->u.basic == 0) {
                Operand op = newtemp();
                InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                IC->kind = RELOP;
                IC->u.relop.result = op; 
                IC->u.relop.left = tp_op1.op;
                IC->u.relop.right = tp_op2.op;
                strcpy(IC->u.relop.r_kind,t_sttree->C_next->B_next->value.c_value);
                emit(IC);
                tp_op1.op = op;
                return tp_op1;
            }
            else {
                printf("错误：两者类型必需均为int型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else if(t_sttree->C_next->B_next->num == 27) {
            tp_op1 = deal_exp(t_sttree->C_next);
            tp_op2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(tp_op1.type->kind == 0 && tp_op2.type->kind == 0) {
                tp_op1.type->u.basic = 1;
                Operand op = newtemp();
                InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                IC->kind = RELOP;
                IC->u.relop.result = op;
                IC->u.relop.left = tp_op1.op;
                IC->u.relop.right = tp_op1.op;
                strcpy(IC->u.relop.r_kind,t_sttree->C_next->B_next->value.c_value);
                emit(IC);
                tp_op1.op = op;
                return tp_op1;
            }
            else {
                printf("错误：两者类型必须均为int或float@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else if(t_sttree->C_next->B_next->num == 28 || t_sttree->C_next->B_next->num == 29 || t_sttree->C_next->B_next->num == 30 || t_sttree->C_next->B_next->num == 31) {
            tp_op1 = deal_exp(t_sttree->C_next);
            tp_op2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(tp_op1.type->kind == 0 && tp_op2.type->kind == 0) {
                if(tp_op1.type->u.basic || tp_op2.type->u.basic) tp_op1.type->u.basic = 1;
                Operand op = newtemp();
                InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                IC->kind = BINOP;
                IC->u.binop.result = op;
                IC->u.binop.op1 = tp_op1.op;
                IC->u.binop.op2 = tp_op2.op;
                strcpy(IC->u.binop.o_kind,t_sttree->C_next->B_next->value.c_value);
                emit(IC);
                tp_op1.op = op;
                return tp_op1;
            }
            else {
                printf("错误：两者类型必须均为int或float@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else if(t_sttree->C_next->B_next->num == 39) {
            tp_op1 = deal_exp(t_sttree->C_next);
            tp_op2 = deal_exp(t_sttree->C_next->B_next->B_next);
            if(tp_op1.type->kind == 1) {
                if(tp_op2.type->kind == 0 && tp_op2.type->u.basic == 0) {
                    if(tp_op1.type->u.array.size > t_sttree->C_next->B_next->B_next->value.i_value) {
                        InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                        
                        IC->kind = BINOP;
                        IC->u.binop.result = newaddr(0);
                        IC->u.binop.op1 = tp_op1.op;
                        IC->u.binop.op2 = newiconst(_sizeof(tp_op1.type)*t_sttree->C_next->B_next->B_next->value.i_value);
                        emit(IC);
                        tp_op1.type = tp_op1.type->u.array.elem;
                        if(tp_op1.type->kind == 0) {
                            tp_op1.op = newaddr(2);
                            tp_op1.op->u.var_no = IC->u.binop.result->u.var_no;
                        }
                        else tp_op1.op = IC->u.binop.result;
                        return tp_op1;
                    }
                    else printf("错误：数组访问越界@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                }
                else {
                    printf("错误：需为int@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
                }
            }
            else {
                printf("错误：变量不是数组类型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else if(t_sttree->C_next->B_next->num == 34) {
            tp_op1 = deal_exp(t_sttree->C_next);
            if(tp_op1.type->kind == 2){
                FieldList t_fieldlist = tp_op1.type->u.structfield.structure;
                while(t_fieldlist != NULL) {
                    if(!strcmp(t_fieldlist->name,t_sttree->C_next->B_next->B_next->value.c_value)) {
                        Operand op = newaddr(2);
                        op->u.var_no = tp_op1.op->u.var_no;
                        tp_op1.type = t_fieldlist->type;
                        tp_op1.op = op;
                        return tp_op1;
                    }
                    else {
                        tp_op1.op = translate_struct(tp_op1.op,t_fieldlist->type);
                        t_fieldlist = t_fieldlist->tail;
                    }
                }
                printf("错误：该结构体没有此成员@line:%d column:%d\n",t_sttree->C_next->B_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->B_next->loc_info.first_column);
            }
            else {
                printf("错误：变量需为结构体类型@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
    }
    else if(t_sttree->C_next->num == 37) {
        return deal_exp(t_sttree->C_next->B_next);
    }
    else if(t_sttree->C_next->num == 29) {
        tp_op1 = deal_exp(t_sttree->C_next->B_next);
        if(tp_op1.type->kind == 0) {
            Operand op1 = newtemp();
            InterCode IC = (InterCode)malloc(sizeof(InterCode_));
            IC->kind = BINOP;
            IC->u.binop.result = op1;
            IC->u.binop.op1 = newiconst(0);
            IC->u.binop.op1 = tp_op1.op;
            strcpy(IC->u.binop.o_kind,"-");
            emit(IC);
            tp_op1.op = op1;
            return tp_op1;
        }
        else {
            printf("错误：变量需为int或float型@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
        }
    }
    else if(t_sttree->C_next->num == 35) {
        tp_op1 = deal_exp(t_sttree->C_next->B_next);
        if(tp_op1.type->kind == 0 && tp_op1.type->u.basic == 0) {
            Operand op1 = newtemp();
            InterCode IC = (InterCode)malloc(sizeof(InterCode_));
            IC->kind = NOT;
            IC->u.notop.result = op1;
            IC->u.notop.op = tp_op1.op;
            strcpy(IC->u.notop.o_kind,"!");
            emit(IC);
            tp_op1.op = op1;
            return tp_op1;
        }
        else {
            printf("错误：变量需为int型@line:%d column:%d\n",t_sttree->C_next->B_next->loc_info.first_line,t_sttree->C_next->B_next->loc_info.first_column);
        }
    }
    else if(t_sttree->C_next->num == 23) {
        if(t_sttree->C_next->B_next) {
            ParaType paratype;
            tp_op1 = looksymbol(1,1,t_sttree->C_next->value.c_value);
            if(tp_op1.type) {
                InterCode IC = (InterCode)malloc(sizeof(InterCode_));
                IC->kind = FUNC_C;
                IC->u.func_c.name = (char *)malloc(sizeof(char)*(strlen(t_sttree->C_next->value.c_value)+1));
                strcpy(IC->u.func_c.name,t_sttree->C_next->value.c_value);
                paratype = para_fun(t_sttree->C_next->value.c_value);
                if(t_sttree->C_next->B_next->B_next->num == 20) {
                    if(paratype.paranum > 0) {
                        if(deal_args(paratype.paralist,t_sttree->C_next->B_next->B_next)) {
                            emit(IC);
                            return tp_op1;
                        }
                        else {
                            printf("错误：函数参数不匹配@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                        }
                    }
                    else {
                        printf("错误：函数无参数@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                    }
                }
                else {
                    if(paratype.paranum == 0) {
                        emit(IC);
                        return tp_op1;
                    }
                    else {
                        printf("错误：此函数有参数@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
                    }
                }
            }
            else {
                printf("错误：此函数未声明@line:%d column:%d\n",t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
        }
        else {
            tp_op1 = looksymbol(1,1,t_sttree->C_next->value.c_value);
            if(tp_op1.type == NULL) {
                printf("错误：变量\"%s\"未声明@line:%d column:%d\n",t_sttree->C_next->value.c_value,t_sttree->C_next->loc_info.first_line,t_sttree->C_next->loc_info.first_column);
            }
            return tp_op1;
        }
    }
    else if(t_sttree->C_next->num == 21) {
        tp_op1.op = newiconst(t_sttree->C_next->value.i_value);
        tp_op1.type = (Type)malloc(sizeof(Type_));
        tp_op1.type->kind = BASIC;
        tp_op1.type->u.basic = 0;
        return tp_op1;
    }
    else if(t_sttree->C_next->num == 22) {
        tp_op1.op = newfconst(t_sttree->C_next->value.f_value);
        tp_op1.type = (Type)malloc(sizeof(Type_));
        tp_op1.type->kind = BASIC;
        tp_op1.type->u.basic = 1;
        return tp_op1;
    }
    return tp_op1;
}

/**
 * 名称：deal_args
 * 作者：ao
 * 功能：处理args
 */
int deal_args(ParaList paralist,STTree *t_sttree) {
    Tp_Op tp_op;
    InterCode IC = (InterCode)malloc(sizeof(InterCode_));
    tp_op.op = NULL;
    tp_op.type = NULL;
    tp_op = deal_exp(t_sttree->C_next);
    IC->kind = ARG;
    IC->u.arg.arg = tp_op.op;
    if(paralist->type->kind == 0) {
        if(paralist->type->u.basic == 0) {
            if(tp_op.type->kind == 0 && tp_op.type->u.basic == 0) {
                emit(IC);
                return 1;
            }
        }
        else if(tp_op.type->kind == 0) {
            emit(IC);
            return 1;
        }
        else return 0;
    }
    else if(paralist->type->kind == 1) {
        if(tp_op.type->kind == 1) {
            if(!strcmp(paralist->type->u.array.name,tp_op.type->u.array.name)) {
                emit(IC);
                return 1;
            }
        }
        return 0;
    }
    else if(paralist->type->kind == 2) {
        if(tp_op.type->kind == 2) {
            if(!strcmp(paralist->type->u.structfield.name,tp_op.type->u.structfield.name)) {
                emit(IC);
                return 1;
            }
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
 * 说明：x_para(0:参数 1:普通)
 */
int type_match(int x_para,Type type1,Type type2,STTree *t_sttree1,STTree *t_sttree2) {
    int judge = 0;
    if(type1->kind == type2->kind) {
        if(type1->kind == 0) {
            if(x_para) {
                if(type1->u.basic == 0) {
                    if(type2->kind == 0 && type2->u.basic == 0) judge = 1;
                    else {
                        printf("错误：变量需为int型@line:%d column:%d\n",t_sttree1->loc_info.first_line,t_sttree2->loc_info.first_column);
                    }
                }
                else if(type2->kind == 0) judge = 1;
            }
            else {
                if(type1->u.basic == type2->u.basic) judge = 1;
            }
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
                if(type1 == NULL && type2 == NULL) judge = 1;
            }
            if(x_para) printf("错误：类型不匹配@line:%d column:%d\n",t_sttree1->loc_info.first_line,t_sttree2->loc_info.first_column);
        }
        else if(type1->kind == 2) {
            if(type2->kind ==2) {
                if(!strcmp(type1->u.structfield.name,type2->u.structfield.name)) judge = 1;
            }
            if(x_para) printf("错误：类型不匹配@line:%d column:%d\n",t_sttree1->loc_info.first_line,t_sttree2->loc_info.first_column);
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
