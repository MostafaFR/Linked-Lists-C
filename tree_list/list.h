#ifndef LIST_H
    #define LIST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "tree.h"
    #define Limit 1000

    typedef struct Element{
        char mot[Limit];
        int nb_occurences;
        struct Element *next;
    }Element;

    typedef struct List{
        struct Element *head;
        struct Element *tail;
    }List;


    List* pack_list(arbre * arbre);
    void pack_list_rec(noeud * noeud, List*liste);
    void display_list(List* liste);
    void initialize_list (List *list);
    void insert_end_list(List*liste,char* mot, int nb_occurences);
    float similarite(List*liste1,List*liste2);
    void supprimerListe(List*liste);

#endif /* !LIST_H */
