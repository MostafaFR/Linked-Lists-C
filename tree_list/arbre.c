#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arbre.h"
#include "tree.h"
#include "list.h"



void initialize_arbre(arbre*A){
    A->racine = NULL;
}

void avl_print(arbre *A){
    printf("\n\n");
    node_print(A->racine, 0, node_height(A->racine));
    printf("\n\n");
}

void node_print(noeud *N, int current_level, int max_level){
    int i;
    if (N) {
        node_print(N->fils_droit, current_level + 1, max_level);
        for (i = 0; i < current_level; i++) {
            printf("       ");
        }
        printf("%s [%d]\n", N->mot, N->nb_occurences);
        node_print(N->fils_gauche, current_level + 1, max_level);
    }else {
        if (current_level < max_level) {
            node_print(NULL, current_level + 1, max_level);
            for (i = 0; i < current_level; i++) {
                printf("       ");
            }
            printf("..\n");
            node_print(NULL, current_level + 1, max_level);
        }
    }
}