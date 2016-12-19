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
    IC->kind = _BINOP;
    IC->u.binop.result = newaddr(0);
    IC->u.binop.op1 = op;
    IC->u.binop.op2 = newiconst(_sizeof(0,type));
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
 * 说明：kind(0:普通 1:取地址 2:读写变量地址 3:读写临时地址)
 */
Operand newaddr(int kind) {
    Operand op = (Operand)malloc(sizeof(Operand_));
    if(kind == 0) {
        op->kind = N_ADDRESS;
        op->u.var_no = tnum++;
    }
    else if(kind == 1) op->kind = G_ADDRESS;
    else if(kind == 2) op->kind = P_N_ADDRESS;
    else if(kind == 3) op->kind = P_T_ADDRESS;
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
 * 说明：chose（0：分配 1：实际）
 */
int _sizeof(int chose,Type type) {
    Type type1 = type;
    int size = 0;
    if(type->kind == 0) {
        if(type->u.basic) size = 1;
        else size = 4;
    }
    else if(type->kind == 1) {
        while(type1->kind == 1) {
            size = size + type1->u.array.size;
            type1 = type1->u.array.elem;
        }
        if(type1->kind == 0) {
            if(type1->u.basic == 0) size = 4 * size;
        }
        else if(type1->kind == 2) size = size * _sizeofstruct(type->u.structfield.structure);
    }
    else if(type->kind == 2) size = _sizeofstruct(type->u.structfield.structure);
    if(chose) return size;
    else {
        if(size%4) return (size/4 +1) * 4;
        else return size;
    }
}

/**
 * 函数名：_sizeofarray
 * 作者：ao
 * 功能：返回数组结构基础类型的大小
 */
int _sizeofarrayb(Type type) {
    Type type1 = type;
    while(type1->kind == 1) type1 = type1->u.array.elem;
    if(type1->kind == 0) {
        if(type1->u.basic) return 1;
        else return 4;
    }
    else if(type1->kind == 2) return _sizeofstruct(type1->u.structfield.structure);
    return 1;
}

/**
 * 函数名：_sizeofstruct
 * 作者：ao
 * 功能：返回结构的大小
 */
int _sizeofstruct(FieldList fieldlist) {
    if(fieldlist != NULL) return _sizeof(0,fieldlist->type) + _sizeofstruct(fieldlist->tail);
    else return 0;
}

/**
 * 函数名：out_ic
 * 作者：ao
 * 功能：将中间代码打印至文件ir.txt
 */
int out_ic() {
    ics_now = intercodes;
    while(ics_now != NULL) {
        switch(ics_now->code->kind) {
            case 0: printf("FUNCTION %s\n",ics_now->code->u.func_d.name);break;
            case 1: {
                printf("PARAM ");
                out_op(ics_now->code->u.param.param);
                printf("\n");
                break;
            }
            case 2: printf("CALL %s\n",ics_now->code->u.func_c.name);
            case 3: {
                printf("DEC ");
                out_op(ics_now->code->u.dec.var);
                printf(" %d\n",ics_now->code->u.dec.size);
                break;
            }
            case 4: {
                printf("ARG ");
                out_op(ics_now->code->u.arg.arg);
                printf("\n");
                break;
            }
            case 5: {
                out_op(ics_now->code->u.assign.left);
                printf(" := ");
                out_op(ics_now->code->u.assign.right);
                printf("\n");
                break;
            }
            case 6: {
                out_op(ics_now->code->u.relop.result);
                printf(" := ");
                out_op(ics_now->code->u.relop.left);
                printf(" %s ",ics_now->code->u.relop.r_kind);
                out_op(ics_now->code->u.relop.right);
                printf("\n");
                break;
            } 
            case 7: {
                out_op(ics_now->code->u.binop.result);
                printf(" := ");
                out_op(ics_now->code->u.binop.op1);
                printf(" %s ",ics_now->code->u.binop.o_kind);
                out_op(ics_now->code->u.binop.op2);
                printf("\n");
                break;
            }
            case 8: {
                out_op(ics_now->code->u.notop.result);
                printf(" := !");
                out_op(ics_now->code->u.notop.op);
                printf("\n");
                break;
            }
            case 9: {
                printf("RETURN ");
                out_op(ics_now->code->u.retop.result);
                printf("\n");
                break;
            }
            case 10: {
                printf("IF ");
                out_op(ics_now->code->u.ifop.relop);
                printf(" GOTO ");
                out_op(ics_now->code->u.ifop.label);
                printf("\n");
                break;
            }
            case 11: {
                printf("LABEL ");
                out_op(ics_now->code->u.label.label);
                printf(" :\n");
                break;
            }
            case 12: {
                printf("GOTO ");
                out_op(ics_now->code->u.gtop.gtop);
                printf("\n");
                break;
            }
        }
        ics_now = ics_now->next;
    }
    return 1;
}

/**
 * 函数名：out_op
 * 作者：ao
 * 功能：打印操作符
 */
int out_op(Operand op) {
    switch(op->kind) {
        case 0: printf("v%d",op->u.var_no);break;
        case 1: printf("t%d",op->u.var_no);break;
        case 2: printf("#%d",op->u.i_value);break;
        case 3: printf("#%f",op->u.f_value);break;
        case 4: printf("t%d",op->u.var_no);break;
        case 5: printf("&v%d",op->u.var_no);break;
        case 6: printf("*v%d",op->u.var_no);break;
        case 7: printf("*t%d",op->u.var_no);break;
        case 8: printf("label%d",op->u.var_no);break;
    }
    return 1;
}
