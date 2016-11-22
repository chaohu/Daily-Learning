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
int ensymbol(char* name,int type,int paranum) {
    unsigned i = hash_pjw(name);
    TOKEN *t_token;
    if (looksymbol(name)) {
        t_token = (TOKEN *)malloc(sizeof(TOKEN));
        switch(type) {
            case 0: { 
                t_token->kind = t_token->IDENTITY;
                strcpy(t_token->symbol.identity.name,name);
                t_token->symbol.identity.type.kind = t_token->symbol.identity.type.BASIC;
                t_token->symbol.identity.type.u.basic = 0;
            }
            case 1: { 
                t_token->kind = t_token->FUNCTION;
                strcpy(t_token->symbol.function.name,name);
            case 2: t_token->kind = t_token->VARIABLE;
            case 3: t_token->kind = t_token->STRUCTURE;
        }
       
        t_token->next = token[i].next;
        token[i].next->prev = t_token;
        t_token->prev = &token[i];
        token[i].next = t_token;
        t_token->below = NULL;
        n_token->below = t_token;
        n_token = t_token;
        return 1;
    }
    else {
        printf("error symbol already exit!");
        return 0;
    }
}

/**
 * 名称：pro_iden
 * 作者：ao
 * 功能：为一个新的identity符号进行初始化的操作
 */
int pro_iden(char *name,TOKEN *t_token) {
    t_token->kind = t_token->IDENTITY;
    strcpy(t_token->symbol.identity.name,name);
    t_token->symbol.identity.type.kind = t_token->symbol.identity.type.BASIC;
    t_token->symbol.identity.type.u.basic = 0;
}

/**
 * 名称：pro_func
 * 作者：ao
 * 功能：为一个新的function符号进行初始化的操作
 */
int pro_func(char *name,int paranum) {
}

/**
 * 名称：pro_vari
 * 作者：ao
 * 功能：为一个新的variable符号进行初始化的操作
 */
int pro_vari(char *name) {
}

/**
 * 名称：pro_stru
 * 作者：ao
 * 功能：为一个新的structure符号进行初始化的操作
 */
int pro_stru(char *name) {
}
