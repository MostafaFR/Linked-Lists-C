#ifndef ARBRE_H 
    #define ARBRE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #include "list.h"
    #define Limit 1000


    void node_print(noeud *N, int current_level, int max_level);
    void avl_print(arbre *A);
    void initialize_arbre(arbre*A);

#endif /* !ARBRE_H */