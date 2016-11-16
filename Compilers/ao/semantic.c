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
int addscope() {
    SCOPE* temp = (SCOPE *)malloc(sizeof(SCOPE));
    temp->next = NULL;
}

/**
 * 名称：delscope
 * 作者：胡超
 * 作用：删除一个过期作用域
 */
int delscope() {

}

/**
 * 名称：looksymbol
 * 作者：胡超
 * 作用：对搜索到的符号进行相关的检查
 */
int looksymbol(char* name, int type) {
    unsigned x = hash_pjw(name);
    while (token[x] != NULL) {
        switch(type) {
            case 0: 

/**
 * 名称：ensymbol
 * 作者：胡超
 * 作用：往符号表中插入符号
 */
int ensymbol(char* name) {
}
