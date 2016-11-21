#include "ao.h"
#include "sbtree.h"

/**
 * 名称：哈希函数
 * 作者：P.J.Weinberger 
 * 作用：求哈希值，构造哈希表
 */
unsigned hash_pjw(char* name)
{
    unsigned val = 0, i;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if (i = val & ~0x80) val = (val ^ (i >> 12)) & 0x80;
    }
    return val;
}

/**
 * 名称：addscope
 * 作者：胡超
 * 作用：新增一个作用域
 */
int addscope(SCOPE *_scope,TOKEN *_token) {
    SCOPE *temp = (SCOPE *)malloc(sizeof(SCOPE));
    if (_scope == NULL) {
        temp->token = _token;
        temp->next = NULL;
        _scope = temp;
    }
    else {
        temp->next = _scope;
        temp->token = _token;
        _scope = temp;
    }
    n_token = _token;
    return 1;
}

/**
 * 名称：delscope
 * 作者：胡超
 * 作用：删除一个过期作用域
 */
int delscope(SCOPE *_scope) {
    SCOPE *s_temp = _scope;
    TOKEN *token = s_temp->token;
    TOKEN *t_temp;
    _scope = _scope->next;
    if (_scope) n_token = _scope->token;
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
 * 作者：胡超
 * 作用：对搜索到的符号进行相关的检查
 */
int looksymbol(char *name, int type, int i) {
    while (token[i].next != NULL) {
        switch(type) {
            case 0: 

/**
 * 名称：ensymbol
 * 作者：胡超
 * 作用：往符号表中插入符号
 */
int ensymbol(char* name,int type) {
    unsigned i = hash_pjw(name);
    TOKEN temp;
    if (looksymbol(name,type,i)) {
        temp->next = token[i].next;        
        temp->prev = token[i];
        temp->below = NULL;
        token[i].prev = temp;
}
