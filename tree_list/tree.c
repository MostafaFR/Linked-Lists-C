#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tree.h"
#include "arbre.h"
#include "list.h"
#define Limit 1000




noeud* creerNoeud(noeud*gauche, noeud*droite, char *mot, int nb_occurences){
    noeud*New = (noeud*)malloc(sizeof(noeud));
    New->fils_gauche = gauche;
    New->fils_droit = droite;
    strcpy(New->mot,mot);
    New->nb_occurences = nb_occurences;
    return New;
}

noeud* creerNoeudVide(char *mot){
    minuscule(mot);
    noeud*New = (noeud*)malloc(sizeof(noeud));
    New = creerNoeud(NULL, NULL, mot, 1);
    return New;
}

int min(int a,int b){
    if(a>=b)
        return b;
    else
        return a;
}

int max(int a,int b){
    if(a>=b)
        return a;
    else
        return b;
}

int compare(char* str1, char* str2){
    int a = strcmp(str1, str2);
    if (a==0)
        return 0;
    if (a<0)
        return 2;
    return 1;
}

arbre* ajouterArbre(arbre*A, noeud*N){
    noeud*P = A->racine;
    int val;
    if(P == NULL)
        val = 0;
    while(P != NULL){
        if(compare(P->mot, N->mot)==1)
            P=P->fils_droit;
            val=1;
        if(compare(P->mot, N->mot)==2)
            P=P->fils_gauche;
            val = 2;
        if(compare(P->mot, N->mot)==0)
            P->nb_occurences++;
            break;
    }
    if(val==1)
        P->fils_droit=N;
    if(val==2)
        P->fils_gauche=N;
    if(val==0)
        P = N;
    return A;
}

void ajout_noeud_rec(noeud*A, noeud*N){
    if(A == NULL){
        A = N;
        return;
    }
    int val = compare(A->mot, N->mot);
    if (val == 0){
        A->nb_occurences += 1;
    }if (val == 1){
        ajout_noeud_rec(A->fils_gauche, N);
    } if (val == 2){
        ajout_noeud_rec(A->fils_droit, N);
    }
}

noeud* ajout_noeud(noeud*A, char*mot2){
    minuscule(mot2);
    if(A==NULL){
        return creerNoeudVide(mot2);
    }else{
        if(compare(A->mot, mot2)==1)
            A->fils_gauche = ajout_noeud(A->fils_gauche, mot2);
        else if(compare(A->mot, mot2)==2)
            A->fils_droit = ajout_noeud(A->fils_droit, mot2);
        else
            A->nb_occurences +=1;
        return A;
    }
}

void enlever_occurence_rec(noeud*A, char*str){
    int val = compare(A->mot, str);
    if (val == 0){
        A->nb_occurences -= 1;
        if(A->nb_occurences == 0){
            if(A->fils_gauche == NULL && A->fils_droit == NULL){
                A = NULL;
                return;
            }if(A->fils_droit == NULL){
                A = A->fils_gauche;
                return;
            }if(A->fils_gauche == NULL){
                A = A->fils_droit;
                return;
            }
        }
        return;
    }
    if (val == 1){
        enlever_occurence_rec(A->fils_gauche, str);
    }
    if (val == 2){
        enlever_occurence_rec(A->fils_droit, str);
    }
}

noeud* enlever_noeud(noeud*A){
    if(A->fils_gauche == NULL && A->fils_droit == NULL){
        return NULL;
    }else if(A->fils_droit == NULL){
        A = A->fils_gauche;
        return A;
    }else if(A->fils_gauche == NULL){
        A = A->fils_droit;
        return A;
    }else{
        noeud*successeur = (noeud*)malloc(sizeof(noeud));
        noeud*New = (noeud*)malloc(sizeof(noeud));
        successeur = A ;
        int a = 0;
        a = 1;
        New = A->fils_droit;
        while (New->fils_gauche != NULL){
            successeur = New ;
            New = New->fils_gauche;
            a = 2;
        }
        strcpy(A->mot, New->mot);
        A->nb_occurences = New->nb_occurences;
        New = enlever_noeud(New);
        if (a==1){
            successeur->fils_droit = New;
        }if (a==2){
            successeur->fils_gauche = New;
        }
        return A;
    }
}

noeud* enlever_occurence(noeud*A, char*str){
    if (A == NULL){
        printf("\n\nLe mot n'est pas dans l'arbre\n\n");
        return A;
    }
    minuscule(str);
    int val = compare(A->mot, str);
    if (val == 0){
        A->nb_occurences -= 1;
        if(A->nb_occurences == 0){
            A = enlever_noeud(A);
            printf("\nMot bien enleve et arbre arrange\n\n");
            return A;
        }
        printf("\nMot bien enleve !\n\n");
        return A;
    }else if (val == 1){
        A->fils_gauche = enlever_occurence(A->fils_gauche, str);
    }else if (val == 2){
        A->fils_droit = enlever_occurence(A->fils_droit, str);
    }
    return A;
}


char* nettoyage(char* str){
    char *str2, *res;
    res = (char*)malloc( (strlen(str)+1)*sizeof(char));
    str2 = res;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] >= 65 && str[i] <= 90){
            *str2++ = str[i] +32;
            continue;
        }
        if (strchr(" -_", str[i]) != NULL){
            continue;
        }
        *str2++ = str[i];

    }
    *str2++ = '\0';
    return res;

}

void compteur(noeud*N, int *tab, int profondeur){
    if(N != NULL){
        tab[profondeur - 1] += 1;
        compteur(N->fils_gauche, tab, profondeur+1);
        compteur(N->fils_droit, tab, profondeur+1);
    }
    return;

}

void minuscule(char*mot){
    for(int i=0; i<strlen(mot);i++){
        if (mot[i]>='A' && mot[i]<='Z'){
            mot[i] = mot[i]+32;
        }
    }
}

int check_parfait(arbre*A){
    int *res, *tab;
    res = (int*)malloc(30*sizeof(int));
    tab = res;
    for (int i=0; i<30; i++){
        tab[i] = 0;
    }
    compteur(A->racine, tab, 1);
    for (int i=0; i<30; i++){
        if (tab[i] != pow(2,i) && tab[i] != 0){
            return 0;
        }if (tab[i]==0)
            return 1;
    }return 1;
}

void display_noeud(noeud * noeud, char * lettre) {
    if (noeud == NULL)
        return;
    display_noeud(noeud->fils_gauche, lettre);
    if ( noeud->mot[0] != *lettre) {
        printf("%c-- %s[%d] \n", noeud->mot[0]-32, noeud->mot, noeud->nb_occurences);
        *lettre = noeud->mot[0];
    }else{
        printf("    %s[%d] \n", noeud->mot, noeud->nb_occurences);
    }
    display_noeud(noeud->fils_droit, lettre);
}

void display_arbre(arbre * arbre) {
    if (!arbre->racine)
        printf("Arbre vide\n");
    else {
        char lettre;
        display_noeud(arbre->racine, &lettre);
    }

}

int check_equilibre(noeud*A){
    int a = abs(node_height(A->fils_droit) - node_height(A->fils_gauche));
    if(a<=1)
        return 1;
    return 0;
}


int node_height(noeud*A){
    if(A==NULL)
        return 0;
    return max(1+node_height(A->fils_droit), 1+node_height(A->fils_gauche));
}



