#include "ao.h"
#include "sbtree.h"

int semantic(STTree *t_sttree) { 
    if(t_sttree != NULL) {
        if(t_sttree->num == 4) {
            if(t_sttree->C_next->num == 36) {
                Type type;
                type = cre_type_b(t_sttree->C_next);
                if(t_sttree->B_next->num == 9) {
                    //pro_func(t_sttree->B_next->C_next->value.c_value,type,type);
                }
                else if(t_sttree->B_next->num == 3) {
                }
                t_sttree = t_sttree->C_next;
            }
            else if(t_sttree->C_next->num == 5) {
                t_sttree = t_sttree->C_next;
                if(t_sttree->B_next->num == 6||t_sttree->B_next->num == 41) {
                    Type type;
                    if(t_sttree->B_next->num == 6) {
                        type = cre_type_s(t_sttree->B_next->B_next);
                        pro_stru(t_sttree->B_next->C_next->value.c_value,type);
                        t_sttree = t_sttree->B_next->B_next->B_next->B_next;
                    }
                    else {
                        type = cre_type_s(t_sttree->B_next);
                        pro_stru(hide_name,type);
                        t_sttree = t_sttree->B_next->B_next->B_next;
                    }
                }
            }
        }
        else if(t_sttree->num == 41) addscope();
        else if(t_sttree->num == 42) delscope();
        s_tree_c(t_sttree->C_next);
        s_tree_b(t_sttree->B_next);
    }
    return 1;
}

int s_tree_c(STTree *t_sttree) {
    if(t_sttree != NULL) {
        if(t_sttree->num == 2) {
        }
    }
    return 1;
}

int s_tree_b(STTree *t_sttree) {
    if(t_sttree != NULL) {
        if(t_sttree->num ==2) {
        }
    }
    return 1;
}

/**
 * 名称：deal_specifier
 * 作者：ao
 * 功能：处理specifier
 */
Type deal_specifier(STTree *t_sttree) {
    Type type;
    if(t_sttree->C_next->num == 36) {
        type = cre_type_b(t_sttree->C_next);
    }
    else if(t_sttree->C_next->num == 5) {
        type = deal_structspecifier(t_sttree->C_next);
    }
    return type;
}

/**
 * 名称：deal_structspecifier
 * 作者：ao
 * 功能：处理structspecifier
 */
Type deal_structspecifier(STTree *t_sttree) {
}
