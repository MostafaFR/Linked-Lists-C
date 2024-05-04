#ifndef tree_H
    #define tree_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define Limit 1000


    typedef struct T_Noeud{
        struct T_Noeud *fils_gauche;
        struct T_Noeud *fils_droit;
        char mot[Limit];
        int nb_occurences;
    }noeud;

    typedef struct T_arbre{
        struct T_Noeud *racine;
    }arbre;


    noeud* creerNoeud(noeud*gauche, noeud*droite, char *mot, int nb_occurences);
    noeud* creerNoeudVide(char *mot);
    int min(int a,int b);
    int max(int a,int b);
    int compare(char* str1, char* str2);
    arbre* ajouterArbre(arbre*A, noeud*N);
    void ajout_noeud_rec(noeud*A, noeud*N);
    noeud* ajout_noeud(noeud*A, char*mot2);
    void enlever_occurence_rec(noeud*A, char*str);
    noeud* enlever_occurence(noeud*A, char*str);
    int check_parfait(arbre*A);
    noeud* enlever_noeud(noeud*A);
    char* nettoyage(char* str);
    void display_arbre(arbre * arbre);
    void display_noeud(noeud * noeud, char * letter);
    int node_height(noeud*A);
    void minuscule(char*mot);
    int check_equilibre(noeud*A);

#endif /* !tree_H */
