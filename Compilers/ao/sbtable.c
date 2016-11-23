#include "ao.h"
#include "sbtree.h"

/**
 * 名称：哈希函数
 * 作者：P.J.Weinberger 
 * 功能：求哈希值，构造哈希表
 */
unsigned hash_pjw(char* name)
{
    unsigned val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if ((i = val) & ~0x80) val = (val ^ (i >> 12)) & 0x80;
    }
    return val;
}

/**
 * 名称：addscope
 * 作者：ao
 * 功能：新增一个符号作用域
 */
int addscope(TOKEN *_token) {
    SCOPE *temp = (SCOPE *)malloc(sizeof(SCOPE));
    if (scope == NULL) {
        temp->token = _token;
        temp->next = NULL;
        scope = temp;
    }
    else {
        temp->next = scope;
        temp->token = _token;
        scope = temp;
    }
    n_token = _token;
    return 1;
}

/**
 * 名称：delscope
 * 作者：ao
 * 功能：删除一个过期的符号作用域
 */
int delscope() {
    SCOPE *s_temp = scope;
    TOKEN *token = s_temp->token;
    TOKEN *t_temp;
    scope = scope->next;
    if (scope) n_token = scope->token;
    else n_token = NULL;
    free(s_temp);
    while(token != NULL) {
        token->prev->next = token->next;
        t_temp = token;
        token = token->below;
    }
    return 1;
}

/**
 * 名称：looksymbol
 * 作者：ao
 * 功能：对搜索到的符号进行相关的检查
 */
int looksymbol(char *name) {
    TOKEN *t_token = scope->token;
    char *t_name;
    int type;
    while(t_token) {
        type = t_token->kind;
        switch(type) {
            case 0: t_name = t_token->symbol.identity.name;
            case 1: t_name = t_token->symbol.function.name;
            case 2: t_name = t_token->symbol.variable.name;
            case 3: t_name = t_token->symbol.structure.name;
        }
        if (strcmp(name,t_name)) return 0;
        else t_token = t_token->below;
    }
    return 1;
}

/**
 * 名称：ensymbol
 * 作者：ao
 * 功能：往符号表中插入符号
 */
int ensymbol(char *name, TOKEN *t_token) {
    unsigned i = hash_pjw(name);
    t_token->next = token[i].next;
    token[i].next->prev = t_token;
    t_token->prev = &token[i];
    token[i].next = t_token;
    t_token->below = NULL;
    n_token->below = t_token;
    n_token = t_token;
    return 1;
}

/**
 * 名称：cre_type_b
 * 作者：ao
 * 功能：够造一个基本类型type
 */
Type cre_type_b(STTree *t_sttree) {
    Type t_temp = (Type)malloc(sizeof(Type_));
    t_temp->kind = t_temp->BASIC;
    if(strcmp(t_sttree->value.c_value,"int")) t_temp->u.basic = 0;
    else t_temp->u.basic = 1;
    return t_temp;
}

/**
 * 名称：cre_type_a
 * 作者：ao
 * 功能：构造一个数组类型type
 */
Type cre_type_a(Type elem,int size) {
    Type t_temp = (Type)malloc(sizeof(Type_));
    t_temp->kind = t_temp->ARRAY;
    t_temp->u.array.elem = elem;
    t_temp->u.array.size = size;
    return t_temp;
}

/**
 * 名称：cre_type_s
 * 作者：ao
 * 功能：构造一个结构类型type
 */
Type cre_type_s(FieldList structure) {
    Type t_temp = (Type)malloc(sizeof(Type_));
    t_temp->kind = t_temp->STRUCTURE;
    t_temp->u.structure = structure;
    return t_temp;
}

/**
 * 名称：cre_type_f
 * 作者：ao
 * 功能：构造一个FieldList
 */
FieldList cre_type_f(char *name,Type type,FieldList tail) {
    FieldList f_temp = (FieldList)malloc(sizeof(FieldList_));
    strcpy(f_temp->name,name);
    f_temp->type = type;
    f_temp->tail = tail;
    return f_temp;
}

/**
 * 名称：pro_iden
 * 作者：ao
 * 功能：为一个新的identity符号进行初始化的操作
 */
int pro_iden(char *name, Type type) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(name)) {
        t_token->kind = t_token->IDENTITY;
        strcpy(t_token->symbol.identity.name,name);
        t_token->symbol.identity.type = type;
        ensymbol(name,t_token);
    }
    else printf("error, symbol repeat!");
    return 1;
}

/**
 * 名称：pro_func
 * 作者：ao
 * 功能：为一个新的function符号进行初始化的操作
 */
int pro_func(char *name,Type retype, int paranum, Type *paratype) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(name)) {
        t_token->kind = t_token->FUNCTION;
        strcpy(t_token->symbol.function.name,name);
        t_token->symbol.function.retype = retype;
        t_token->symbol.function.paranum = paranum;
        t_token->symbol.function.paratype = paratype;
        ensymbol(name,t_token);
    }
    else printf("error, symbol repeat!");
    return 1;
}

/**
 * 名称：pro_vari
 * 作者：ao
 * 功能：为一个新的variable符号进行初始化的操作
 */
int pro_vari(char *name,Type type) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if(looksymbol(name)) {
        t_token->kind = t_token->VARIABLE;
        strcpy(t_token->symbol.variable.name,name);
        t_token->symbol.variable.type = type;
        ensymbol(name,t_token);
    }
    else printf("error, symbol repeat!");
    return 1;
}

/**
 * 名称：pro_stru
 * 作者：ao
 * 功能：为一个新的structure符号进行初始化的操作
 */
int pro_stru(char *name, Type type) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(name)) {
        t_token->kind = t_token->STRUCTURE;
        strcpy(t_token->symbol.structure.name,name);
        t_token->symbol.structure.type = type;
        ensymbol(name,t_token);
    }
    else printf("error, symbol repeat!");
    return 1;
}
