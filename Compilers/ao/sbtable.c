#include "ao.h"
#include "sbtree.h"

SCOPE *scope = NULL;    //作用域栈头指针
int scope_num = 0;      //作用域层数
/**
 * 名称：哈希函数
 * 作者：P.J.Weinberger 
 * 功能：求哈希值，构造哈希表
 */
unsigned hash_pjw(char* name)
{
    unsigned val = 0;
    unsigned i = 0;
    for (; *name; ++name)
    {
        val = (val << 2) + *name;
        if ((i = val & ~0x7f)) val = (val ^ (i >> 12)) & 0x7f;
    }
    return val;
}

/**
 * 名称：addscope
 * 作者：ao
 * 功能：新增一个符号作用域
 */
int addscope() {
    scope_num++;
    fprintf(sb_file,"%s%d%s","\n****************第",scope_num,"层作用域****************\nname\ttoken\ttype\tline\tcolumn\thash\n");
    //printf("\n****************第%d层作用域****************",scope_num);
    //printf("\nname\ttoken\ttype\tline\tcolumn\thash\n");
    SCOPE *temp = (SCOPE *)malloc(sizeof(SCOPE));
    if (scope == NULL) {
        temp->token = NULL;
        temp->next = NULL;
        scope = temp;
    }
    else {
        temp->next = scope;
        temp->token = NULL;
        scope = temp;
    }
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
    if(scope) {
        n_token = scope->token;
        if(n_token) {
            while(n_token->below) {
                n_token = n_token->below;
            }
        }
    }
    else n_token = NULL;
    free(s_temp);
    while(token != NULL) {
        token->prev->next = token->next;
        if(token->next) token->next->prev = token->prev;
        t_temp = token;
        token = token->below;
        free(t_temp);
    }
    fprintf(sb_file,"%s%d%s","**************第",scope_num,"层作用域结束**************\n");
    //printf("**************第%d层作用域结束**************\n",scope_num);
    scope_num--;
    return 1;
}

/**
 * 名称：looksymbol
 * 作者：ao
 * 功能：检查symbol是否存在，若存在返回symbol类型
 * 说明：kind(0:ID,1:FU,2:VA,3:ST)  specifier(0:类型 1：变量)
 *       function(0:查redefine 1:查exit)
 */
Type looksymbol(int function,int specifier,char *c_value) {
    Type type = NULL;
    TOKEN *t_token = NULL;
    if(function) {
        unsigned num = hash_pjw(c_value);
        t_token = token[num].next;
    }
    else t_token = scope->token;
    while(t_token) {
        switch(t_token->kind) {
            case 0: {
                if(specifier) {
                    if(!strcmp(c_value,t_token->symbol.identity.name)) return t_token->symbol.identity.type;
                }
                break;
            }
            case 1: {
                if(specifier) {
                    if(!strcmp(c_value,t_token->symbol.function.name)) return t_token->symbol.function.retype;
                }
                break;
            }
            case 2: {
                if(specifier) {
                    if(!strcmp(c_value,t_token->symbol.variable.name)) return t_token->symbol.variable.type;
                }
                break;
            }
            case 3: {
                if(specifier) {
                    if(t_token->symbol.structure.specifier) {
                        if(!strcmp(c_value,t_token->symbol.structure.name)) return t_token->symbol.structure.type;
                    }
                }
                else {
                    if(t_token->symbol.structure.specifier == 0) {
                        if(!strcmp(c_value,t_token->symbol.structure.name)) return t_token->symbol.structure.type;
                    }
                }
                break;
            }
        }
        if(function) t_token = t_token->next;
        else t_token = t_token->below;
    }
    return type;
}

/**
 * 名称：ensymbol
 * 作者：ao
 * 功能：往符号表中插入符号
 */
int ensymbol(char *name, TOKEN *t_token) {
    int t_num = -1;
    unsigned i = hash_pjw(name);
    switch(t_token->kind) {
        case 0: t_num = t_token->symbol.identity.type->kind;break;
        case 1: t_num = t_token->symbol.function.retype->kind;break;
        case 2: t_num = t_token->symbol.variable.type->kind;break;
        case 3: t_num = t_token->symbol.structure.type->kind;break;
    }
    fprintf(sb_file,"%s%s%d%s%d%s%d%s%d%s%d\n",name,"\t\t",t_token->kind,"\t\t",t_num,"\t\t",t_token->loc_info.first_line,"\t\t",t_token->loc_info.first_column,"\t\t",i);
    //printf("%s\t%d\t%d\t%d\t%d\t%d\n",name,t_token->kind,t_num,t_token->loc_info.first_line,t_token->loc_info.first_column,i);
    if(token[i].next == NULL) {
        token[i].next = t_token;
        t_token->prev = &token[i];
    }
    else {
        t_token->next = token[i].next;
        token[i].next->prev = t_token;
        t_token->prev = &token[i];
        token[i].next = t_token;
    }
    t_token->below = NULL;
    if(n_token) {
        n_token->below = t_token;
        n_token = t_token;
    }
    else {
        scope->token = t_token;
        n_token = t_token;
    }
    return 1;
}

/**
 * 名称：pro_iden
 * 作者：ao
 * 功能：为一个新的identity符号进行初始化的操作
 */
int pro_iden(char *name, Type type, yyltype loc_info) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(0,1,name) == NULL) {
        t_token->kind = IDENTITY;
        t_token->symbol.identity.name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(t_token->symbol.identity.name,name);
        t_token->symbol.identity.type = type;
        t_token->loc_info = loc_info;
        t_token->next = NULL;
        t_token->prev = NULL;
        t_token->below = NULL;
        ensymbol(name,t_token);
    }
    else {
        printf("Error, symbol redefine! @line:%d column:%d\n",loc_info.first_line,loc_info.first_column);
        //exit(1);
    }
    return 1;
}

/**
 * 名称：pro_func
 * 作者：ao
 * 功能：为一个新的function符号进行初始化的操作
 */
int pro_func(char *name,Type retype,int paranum,ParaList paralist,yyltype loc_info) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(0,1,name) == NULL) {
        t_token->kind = FUNCTION;
        t_token->symbol.function.name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(t_token->symbol.function.name,name);
        t_token->symbol.function.retype = retype;
        t_token->symbol.function.paratype.paranum= paranum;
        t_token->symbol.function.paratype.paralist= paralist;
        t_token->loc_info = loc_info;
        t_token->next = NULL;
        t_token->prev = NULL;
        t_token->below = NULL;       
        ensymbol(name,t_token);
    }
    else {
        printf("Error, symbol redefine! @line:%d column:%d\n",loc_info.first_line,loc_info.first_column);
        //exit(1);
    }
    return 1;
}

/**
 * 名称：pro_vari
 * 作者：ao
 * 功能：为一个新的variable符号进行初始化的操作
 */
int pro_vari(char *name,Type type,yyltype loc_info) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if(looksymbol(0,1,name) == NULL) {
        t_token->kind = VARIABLE;
        t_token->symbol.variable.name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(t_token->symbol.variable.name,name);
        t_token->symbol.variable.type = type;
        t_token->loc_info = loc_info;
        t_token->next = NULL;
        t_token->prev = NULL;
        t_token->below = NULL;
        ensymbol(name,t_token);
    }
    else {
        printf("Error, symbol redefine! @line:%d column:%d\n",loc_info.first_line,loc_info.first_column);
        //exit(1);
    }
    return 1;
}

/**
 * 名称：pro_stru
 * 作者：ao
 * 功能：为一个新的structure符号进行初始化的操作
 * 说明：specifier(0:类型 1：变量)
 */
int pro_stru(int specifier,char *name, Type type,yyltype loc_info) {
    TOKEN *t_token = (TOKEN *)malloc(sizeof(TOKEN));
    if (looksymbol(0,specifier,name) == NULL) {
        t_token->kind = _STRUCTURE;
        t_token->symbol.structure.specifier= specifier;
        t_token->symbol.structure.name = (char*)malloc(sizeof(char)*(strlen(name)+1));
        strcpy(t_token->symbol.structure.name,name);
        t_token->symbol.structure.type = type;
        t_token->loc_info = loc_info;
        t_token->next = NULL;
        t_token->prev = NULL;
        t_token->below = NULL;
        ensymbol(name,t_token);
    }
    else {
        printf("Error, symbol redefine! @line:%d column:%d\n",loc_info.first_line,loc_info.first_column);
        //exit(1);
    }
    return 1;
}
