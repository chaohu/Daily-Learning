#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef AO_H
#define AO_H 1

//ao.h
extern FILE* yyin;
extern int yydebug;
extern int yyparse(void);
extern void yyerror(char const*);
typedef struct Operand_ *Operand;
typedef struct InterCode_ *InterCode;
typedef struct InterCodes_ *InterCodes;

#undef YYDEBUG
#define YYDEBUG 1

#undef YYLTYPE
#define YYLTYPE yyltype

typedef struct YYLTYPE {    //结点坐标信息结构
	int first_line;
	int first_column;
	int last_line;
	int last_column;
} yyltype;

union T_value{      //结点值联合
	int i_value;
	float f_value;
	char c_value[20];
};

typedef struct STTree{
    int num;                //结点类型编号
	char content[17];       //结点名
	yyltype loc_info;       //结点坐标信息
	union T_value value;    //结点值
	int t_value;            //结点种类
	struct STTree *C_next;  //子结点
	struct STTree *B_next;  //兄弟结点
}STTree;

STTree *_sttree;

int syntaxtree(STTree *);
int o_tree_c(STTree *);
int o_tree_b(STTree *);
int semantic(STTree *t_sttree);
STTree *cretree_i(int num,char *content,yyltype loc_info,int t_value,int i_value);
STTree *cretree_f(int num,char *content,yyltype loc_info,int t_value,float f_value);
STTree *cretree_c(int num,char *content,yyltype loc_info,int t_value,char *c_value);
STTree *entree(int num,char *content,yyltype loc_info,int n,...);


//sbtree.h
FILE *sb_file;
typedef struct Type_ *Type;
typedef struct FieldList_ *FieldList;
typedef struct ParaList_ *ParaList;

struct StructField {
    char* name;
    FieldList structure;
};

typedef struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE } kind;
    union
    {
        //基本类型
        int basic;      //0：int，1：float
        //数组类型信息包括元素类型与数组大小构成
        struct {Type elem; int size; char *name; } array;
        //结构体类型信息是一个链表
        struct StructField structfield;
    } u;
}Type_;

typedef struct FieldList_ {
    char* name; //域的名字
    Type type;  //域的类型
    FieldList tail; //下一个域
}FieldList_;

typedef struct Identity {
    char* name;
    Type type;
}Identity;

//function参数结构
typedef struct ParaType {
    int paranum;
    ParaList paralist;
}ParaType;

//function参数列表
typedef struct ParaList_ {
    char *name;
    Type type;
    ParaList next;
}ParaList_;

typedef struct Function {
    char *name;
    Type retype;
    ParaType paratype;
}Function;

typedef struct Variable {
    char* name;
    Type type;
}Variable;

typedef struct Structure {
    int specifier;   //specifier(0:类型 1:变量)
    char* name;
    Type type;
}Structure;

typedef struct TOKEN {
    enum { IDENTITY, FUNCTION, VARIABLE, _STRUCTURE } kind;
    union {
        Identity identity;
        Function function;
        Variable variable;
        Structure structure;
    } symbol;
    yyltype loc_info;
    int s_num;
    struct TOKEN *next;
    struct TOKEN *prev;
    struct TOKEN *below;
}TOKEN;

typedef struct SCOPE {
    struct TOKEN* token;
    struct SCOPE* next;
}SCOPE;

typedef struct Tp_Op { 
    Type type;
    Operand op; 
}Tp_Op;

TOKEN token[128];   //符号表空间
TOKEN *n_token;     //指向当前作用域的最后一个符号
char hide_name[6];  //隐藏符号的名字

unsigned hash_pjw(char* name);
int addscope();//新建一层作用域
int delscope();//删除一层作用域
Tp_Op looksymbol(int function,int specifier,char *c_value);//查找符号是否在符号表中
int ensymbol(char *name, TOKEN *t_token);//将符号加入符号表
int pro_iden(char *name,Type type,yyltype loc_info);//初始化一个新的indentity符号
int pro_func(char *name,Type retype,int paranum,ParaList paralist,yyltype loc_info);//初始化一个新的function符号
int pro_vari(char *name,Type type,yyltype loc_info);//初始化一个新的variable符号
int pro_stru(int specifier,char *name,Type type,yyltype loc_info);//初始化一个新的structure符号
int semantic(STTree *t_sttree);//分析函数入口
int deal_extdeflist(STTree *t_sttree);
int deal_extdef(STTree *t_sttree);  //处理extdef
Type deal_specifier(STTree *t_sttree);
Type deal_structspecifier(STTree *t_sttree);
FieldList deal_s_deflist(STTree *t_sttree); //处理结构体中的deflist
FieldList deal_s_def(STTree *t_sttree);//处理结构体中的def
FieldList deal_s_declist(Type type,STTree *t_sttree);//处理结构体中的declist
FieldList deal_s_dec(Type type,STTree *t_sttree);//处理结构体中的dec
FieldList deal_s_vardec(int kind,Type type,STTree *t_sttree);//处理结构体中的vardec
int deal_extdeclist(Type type,STTree *t_sttree);//处理extdeclist
ParaList deal_c_vardec(int kind,Type type,STTree *t_sttree);//处理函数体中的vardec
int deal_fundec(Type retype,STTree *t_sttree);  //处理fundec
ParaList deal_varlist(int *paranum,STTree *t_sttree);//处理varlist
ParaList deal_paramdec(STTree *t_sttree);//处理paramdec
int deal_compst(Type retype,STTree *t_sttree);  //处理compst
int deal_c_deflist(STTree *t_sttree);//处理函数体中的deflist
int deal_c_def(STTree *t_sttree);//处理函数体中的def
int deal_c_declist(Type type,STTree *t_sttree);//处理函数体中的declist
int deal_c_dec(Type type,STTree *t_sttree);//处理函数体中的dec
//int deal_c_vardec(int kind,Type type,STTree *t_sttree);//处理函数体中的vardec
int deal_stmtlist(Type retype,STTree *t_sttree);//处理stmtlist
int deal_stmt(Type retype,STTree *t_sttree);//处理stmt
Tp_Op deal_exp(STTree *t_sttree);//处理exp
int deal_args(ParaList paralist,STTree *t_sttree);//处理args
int type_match(int x_para,Type type1,Type type2,STTree *t_sttree1,STTree *t_sttree2);//判断两个类型是否匹配
int j_left(STTree *t_sttree);//判断是否为左值表达式
ParaType para_fun(char *c_value);//返回函数的参数ParaType

//ir.h
typedef struct Operand_ {
    enum { N_VARIABLE, T_VARIABLE, I_CONSTANT, F_CONSTANT, N_ADDRESS, G_ADDRESS, P_N_ADDRESS, P_T_ADDRESS, N_LABEL} kind;
    union {
        int var_no;     //变量编号
        int i_value;    //变量的整数值
        float f_value;  //变量的浮点值
    } u;
}Operand_;

typedef struct InterCode_ {
    enum { _FUNC_D, _PARAM, _FUNC_C, _DEC, _ARG, _ASSIGN, _RELOP, _BINOP, _NOT, _RETURN, _IF, _LABEL, _GOTO} kind;
    union {
        struct { char *name;} func_d;
        struct { Operand param;} param;
        struct { Operand reop; char *name;} func_c;
        struct { Operand var; int size;} dec;
        struct { Operand arg;} arg;
        struct { Operand right, left;} assign;
        struct { Operand result, right, left; char r_kind[3];} relop;
        struct { Operand result, op1, op2; char o_kind[2];} binop;
        struct { Operand result, op;} notop;
        struct { Operand result;} retop;
        struct { Operand relop,label;} ifop;
        struct { Operand label;} label;
        struct { Operand gtop;} gtop;
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
int _sizeof(int chose,Type type);          //返回type的大小
int _sizeofarrayb(Type type);    //返回数组的大小
int _sizeofstruct(FieldList fieldlist); //返回结构的大小
int out_ic();   //打印中间代码至文件ir.txt
int out_op(Operand op); //打印操作符

#endif
