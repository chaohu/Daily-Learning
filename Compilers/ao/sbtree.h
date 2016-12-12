#include "ao.h"

#ifndef SBTREE_H
#define SBTREE_H 1

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
    struct TOKEN *next;
    struct TOKEN *prev;
    struct TOKEN *below;
}TOKEN;

typedef struct SCOPE {
    struct TOKEN* token;
    struct SCOPE* next;
}SCOPE;

TOKEN token[128];   //符号表空间
TOKEN *n_token;     //指向当前作用域的最后一个符号
char hide_name[6];  //隐藏符号的名字
 
unsigned hash_pjw(char* name);
int addscope();//新建一层作用域
int delscope();//删除一层作用域
Type looksymbol(int function,int specifier,char *c_value);//查找符号是否在符号表中
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
Type deal_exp(STTree *t_sttree);//处理exp
int deal_args(ParaList paralist,STTree *t_sttree);//处理args
int type_match(int x_para,Type type1,Type type2,STTree *t_sttree1,STTree *t_sttree2);//判断两个类型是否匹配
int j_left(STTree *t_sttree);//判断是否为左值表达式
ParaType para_fun(char *c_value);//返回函数的参数ParaType


#endif
