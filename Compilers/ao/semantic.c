#include "ao.h"
#include "sbtree.h"

int semantic(STTree *t_sttree) { 
    if(t_sttree != NULL) {
        if(t_sttree->num == 4) {
            if(t_sttree->C_next->num == 36) {
                cre_type_b(t_sttree->C_next);
                t_sttree = t_sttree->C_next;
            }
            else if(t_sttree->C_next->num == 5) {
                while(t_sttree->C_next
            }
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

Type cre_type_s(STTree *t_sttree) {
    if(
