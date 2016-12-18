#include "ao.h"
#include "sbtree.h"

#ifndef IR_H
#define IR_H 1

typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct InterCodes_ *InterCodes;

typedef struct Operand_ {
    enum { N_VARIABLE, T_VARIABLE, I_CONSTANT, F_CONSTANT, N_ADDRESS, G_ADDRESS, P_ADDRESS, N_LABEL} kind;
    union {
        int var_no;     //变量编号
        int i_value;    //变量的整数值
        float f_value;  //变量的浮点值
    } u;
}Operand_;

typedef struct InterCode_ {
    enum { FUNC_D, PARAM, FUNC_C, ARG, ASSIGN, RELOP, BINOP, NOT, RETURN, IF, LABEL, GOTO, ADDR} kind;
    union {
        struct { char *name;} func_d;
        struct { Operand param;} param;
        struct { char *name;} func_c;
        struct { Operand arg;} arg;
        struct { Operand right, left;} assign;
        struct { Operand result, right, left; char r_kind[3];} relop;
        struct { Operand result, op1, op2; char o_kind[2];} binop;
        struct { Operand result, op; char o_kind[2];} notop;
        struct { Operand result;} retop;
        struct { Operand relop,label;} ifop;
        struct { Operand label;} label;
        struct { Operand gtop;} gtop;
        struct { Operand result, op; char o_kind[2];} addr;
    } u;
}InterCode_;

typedef struct InterCodes_ {
    InterCode code;
    InterCodes prev,next;
}InterCodes_;

InterCodes intercodes;  //中间代码链表头结点
InterCodes ics_now;      //中间代码当前节点

Operand translate_struct(Operand op,Type type); //翻译结构体的中间代码
Operand newtemp();      //新建一个临时变量
Operand newiconst(int i);    //新建一个整形常数
Operand newfconst(float f);    //新建一个浮点型常数
Operand newaddr(int kind);     //新建一个普通地址变量
Operand newlabel();     //新建一个标签
int emit(InterCode IC); //输出一句中间代码
int _sizeof(Type type);          //返回type大小
int _sizeofstruct(FieldList fieldlist); //返回结构的大小

#endif
