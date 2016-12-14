#include "ir.h"

int tnum = 0;   //临时变量编号

/**
 * 函数名：translate_exp
 * 作者：ao
 * 功能：翻译语法单元exp的中间代码
 */
int translate_exp(STTree *t_sttree,struct ast *tp) {
    switch(t_sttree->C_next->num) {
        case 19: {
            switch(t_sttree->C_next->B_next->num) {
                case 26: {
                    Operand op1 = (Operand)malloc(sizeof(Operand_));
                    //if(t_sttree->C_next->C_next
                }
                case 32: ;
                case 33: ;
                case 27: ;
                case 28: ;
                case 29: ;
                case 30: ;
                case 31: ;
                case 39: ;
                case 34: ;
            } 
        }
        case 37: ;
        case 29: ;
        case 35: ;
        case 23: ;
        case 21: ;
        case 22: ;
    }
    return 1;
}

/**
 * 函数名：newtemp
 * 作者：ao
 * 功能：创建一个临时变量
 */
Operand newtemp() {
    Operand op = (Operand)malloc(sizeof(Operand_));
    op->kind = T_VARIABLE;
    op->u.var_no = tnum++;
    return op;
}

/**
 * 函数名：emit
 * 作者：ao
 * 功能：输出四元式
 */
int emit(InterCode IC) {
    InterCodes ICS = (InterCodes)malloc(sizeof(InterCodes_));
    ICS->code = IC;
    if(ics_now) {
        ics_now->next = ICS;
        ICS->prev = ics_now;
        ICS->next = NULL;
        ics_now = ICS;
    }
    else {
        ICS->next = NULL;
        ICS->prev = NULL;
        intercodes = ICS;
        ics_now = ICS;
    } 
    return 1;
}
