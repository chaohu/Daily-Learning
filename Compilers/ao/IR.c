#include "ao.h"

int tnum = 0;   //临时变量编号
int lnum = 0;   //标签编号


/**
 * 函数名：translate_struct
 * 作者：ao
 * 功能：翻译结构体的中间代码
 */
Operand translate_struct(Operand op,Type type) {
    InterCode IC = (InterCode)malloc(sizeof(InterCode_));
    IC->kind = BINOP;
    IC->u.binop.result = newaddr(0);
    IC->u.binop.op1 = op;
    IC->u.binop.op2 = newiconst(_sizeof(type));
    strcpy(IC->u.binop.o_kind,"+");
    emit(IC);
    return IC->u.binop.result;
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
 * 函数名：newiconst
 * 作者：ao
 * 功能：新建一个整形常数
 */
Operand newiconst(int i) {
    Operand op = (Operand)malloc(sizeof(Operand_));
    op->kind = I_CONSTANT;
    op->u.i_value = i;
    return op;
}

/**
 * 函数名：newfconst
 * 作者：ao
 * 功能：新建一个浮点型常数
 */
Operand newfconst(float f) {
    Operand op = (Operand)malloc(sizeof(Operand_));
    op->kind = F_CONSTANT;
    op->u.f_value = f;
    return op;
}

/**
 * 函数名：newaddr
 * 作者：ao
 * 功能：新建一个地址变量
 * 说明：kind(0：普通 1：取地址 2：写地址)
 */
Operand newaddr(int kind) {
    Operand op = (Operand)malloc(sizeof(Operand_));
    if(kind == 0) {
        op->kind = N_ADDRESS;
        op->u.var_no = tnum++;
    }
    else if(kind == 1) op->kind = G_ADDRESS;
    else if(kind == 2) op->kind = P_ADDRESS;
    return op;
}

/**
 * 函数名：newlabel
 * 作者：ao
 * 功能：创建一个新的标签
 */
Operand newlabel() {
    Operand op = (Operand)malloc(sizeof(Operand_));
    op->kind = N_LABEL;
    op->u.var_no = lnum++;
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

/**
 * 函数名：_sizeof
 * 作者：ao
 * 功能：返回type的大小
 */
int _sizeof(Type type) {
    Type type1 = type;
    if(type->kind == 0) {
        if(type->u.basic) return 4;
        else return 1;
    }
    else if(type->kind == 1) {
        while(type1->kind == 1) type1 = type1->u.array.elem;
        if(type1->kind == 0) {
            if(type1->u.basic) return 4;
            else return 1;
        }
        else if(type1->kind == 2) return _sizeofstruct(type->u.structfield.structure);
    }
    else if(type->kind == 2) return _sizeofstruct(type->u.structfield.structure);
    return 0;
}

/**
 * 函数名：_sizeofstruct
 * 作者：ao
 * 功能：返回结构的大小
 */
int _sizeofstruct(FieldList fieldlist) {
    if(fieldlist != NULL) return _sizeof(fieldlist->type) + _sizeofstruct(fieldlist->tail);
    else return 0;
}
