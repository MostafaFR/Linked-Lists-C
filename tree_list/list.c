#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "list.h"
#include "arbre.h"

//voila

float similarite(List*liste1, List*liste2){
    float similarites = 0;
    float tot = 0;
    float taille2 = 0;

    Element* position1 = liste1->head;
    Element* position2 = liste2->head;
    Element* tmp = liste2->head;
    while (position1 != NULL){
        int conti = 1;
        tot+=position1->nb_occurences;
        while (position2!=NULL && conti == 1){
            int a = strcmp(position1->mot, position2->mot);
            if (a==0){
                if(position2->nb_occurences > position1->nb_occurences)
                    similarites+=position1->nb_occurences;
                else
                    similarites+=position2->nb_occurences;
                conti = 0;
                position2=tmp;
            }
            else if(a>0){
                position2 = position2->next;
            }else{
                conti = 0;
                position2=tmp;
            }
        }
        position1 = position1->next;
        position2=tmp;
    }
    Element* new_pos = liste2->head;
    while(new_pos != NULL){
        taille2+=new_pos->nb_occurences;
        new_pos=new_pos->next;
    }
    tot += (taille2-similarites);
    if (tot == 0.0)
        return 1.0;
    return  (similarites/tot);
}

List* pack_list(arbre * A){
    if (A->racine == NULL){
        printf("Impossible, Arbre vide\n");
        return NULL;
    }
    else {
        List* liste = (List*)malloc(sizeof(List));
        initialize_list(liste);
        pack_list_rec(A->racine, liste);
        return liste;
    }
}

void pack_list_rec(noeud * N, List*liste){
    if (N == NULL)
        return;

    pack_list_rec(N->fils_gauche, liste);

    insert_end_list(liste, N->mot, N->nb_occurences);

    pack_list_rec(N->fils_droit, liste);

}

void supprimerListe(List*liste){
    Element *actuel = liste->head;
    while (actuel != NULL){
        Element*aSupprimer = actuel;
        actuel = actuel->next;
        free(aSupprimer);
    }
}

void insert_end_list(List*liste, char* mot, int nb_occurences){
    Element*New = (Element*)malloc(sizeof(struct Element));
    if(liste->head==NULL){
        liste->head=New;
        liste->tail=New;
    }else{
        New->next=NULL;
        liste->tail->next=New;
        liste->tail = liste->tail->next;
    }

    strcpy(New->mot, mot);
    New->nb_occurences = nb_occurences;
    New->next = NULL;

}

void initialize_list (List *list){
    list->head = NULL;  //Pointeur head vide
    list->tail = NULL;  //Pointeur tail vide
}



void display_list(List* liste){
    if (liste->head == NULL){
        printf("EMPTY List\n");         //Pour afficher la liste, on parcourt la liste, on reconstitue le nombre
    }else{                                //représenté é l'aide de nombre_correspondant, et on l'affiche
        Element* position = liste->head;
        printf("%s[%d]", position->mot, position->nb_occurences);
        position = position->next;
        while(position != NULL){
            printf("-%s[%d]", position->mot, position->nb_occurences);
            position = position->next;

        }
    }
}
