#include "ao.h"

#ifndef IR_H
#define IR_H 1

typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct InterCodes_ *InterCodes;

typedef struct Operand_ {
    enum { N_VARIABLE, T_VARIABLE, CONSTANT, ADDRESS} kind;
    union {
        int var_no;     //变量编号
        int i_value;    //变量的整数值
        float f_value;  //变量的浮点值
    } u;
}Operand_;

typedef struct InterCode_ {
    enum { FUNC_D, PARAM, FUNC_C, ARG, ASSIGN, RELOP, BINOP, NOT} kind;
    union {
        struct { char *name;} func_d;
        struct { Operand param;} param;
        struct { char *name;} func_c;
        struct { Operand arg;} arg;
        struct { Operand right, left;} assign;
        struct { Operand result, right, left; char r_kind[3];} relop;
        struct { Operand result, op1, op2; char o_kind[2];} binop;
        struct { Operand result, op1; char o_kind[2];} notop;
    } u;
}InterCode_;

typedef struct InterCodes_ {
    InterCode code;
    InterCodes prev,next;
}InterCodes_;

InterCodes intercodes;  //中间代码链表头结点
InterCodes ics_now;      //中间代码当前节点

int translate_exp(STTree *t_sttree);
Operand newtemp();
int emit(InterCode IC);
int en_ast(InterCode_ code);

#endif
