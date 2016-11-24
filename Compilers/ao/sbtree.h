#ifndef SBTREE_H
#define SBTREE_H 1

#include "ao.h"

typedef struct Type_ *Type;
typedef struct FieldList_* FieldList;

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE } kind;
    union
    {
        //基本类型
        int basic;
        //数组类型信息包括元素类型与数组大小构成
        struct { Type elem; int size; } array;
        //结构体类型信息是一个链表
        FieldList structure;
    } u;
};
 
struct FieldList_ {
    char* name; //域的名字
    Type type;  //域的类型
    FieldList tail; //下一个域
};

struct Identity {
    char* name;
    Type type;
};

struct Function {
    char *name;
    Type retype;
    int paranum;
    Type *paratype;
};

 
struct Variable {
    char* name;
    Type type;
};

struct Array {
    int size;
    Type type;
};

struct Structure {
    char* name;
    Type type;
};

struct Structfield {
    char* name;
    Type type;
};

struct TOKEN {
    enum { IDENTITY, FUNCTION, VARIABLE, STRUCTURE } kind;
    union {
        Identity identity;
        Function function;
        Variable variable;
        Structure structure;
    } symbol;
    TOKEN *next;
    TOKEN *prev;
    TOKEN *below;
};

struct SCOPE {
    TOKEN* token;
    SCOPE* next;
};

TOKEN token[128];   //符号表空间
TOKEN *n_token;     //指向当前作用域的最后一个符号
SCOPE* scope = NULL;    //作用域栈头指针
char hide_name[3] = "$$";   //隐藏符号的名字
 
unsigned hash_pjw(char* name);
int addscope();
int delscope();
int looksymbol(char* name);
int ensymbol(char *name, TOKEN *t_token);
Type cre_type_b(STTree *sttree);
Type cre_type_a(Type elem,int size);
Type cre_type_s(STTree *t_sttree);
FieldList cre_type_f(char *name,Type type,FieldList tail);
int pro_iden(char *name, Type type);
int pro_func(char *name, Type type);
int pro_vari(char *name, Type type);
int pro_stru(char *name, Type type);
int s_tree_c(STTree *t_sttree);
int s_tree_b(STTree *t_sttree);

#endif
