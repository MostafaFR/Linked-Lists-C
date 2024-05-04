#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"
#include "arbre.h"
#define Limit 1000


int motValide(char* str)
{
    int valide = 1;
    int i = 0;
    int vrai_debut = 0;
    while (valide && i < strlen(str))
    {
        if (str[i] < 'A' || (str[i] < 'a' && str[i] > 'Z') || str[i] > 'z')
            valide = 0;
        else
            i++;
    }
    return valide;
}

int main(){
    arbre* tab[10];
    List* tab_l[10];
    int index = 0;
    for(int i=0;i<10;i++){
        arbre* A = (arbre*)malloc(sizeof(struct T_arbre));
        A->racine = NULL;
        tab[i] = A;
        List* l = (List*)malloc(sizeof(struct List));
        l->head = NULL;
        l->tail = NULL;
        tab_l[i] = l;
    }
    // tab[index] = (arbre*)malloc(sizeof(arbre));
    // initialize_arbre(tab[index]);
    // initialize_list(tab_l[index]);
    char mot[Limit];
    int position;
    char choix_utilisateur[Limit];
    char choix_arbre[Limit];
    char choixb = '0';
    char choix = '0';
    char poubelle[Limit];
    int destruction;
    printf("Bienvenue dans votre programme de gestion de liste !\n");
    while (choix != '9')
    {
        printf("\n\n\n=============== ARBRE %d ===============\n\n", index);
        printf("\nVoici les actions que vous pouvez entreprendre :\n");
        printf("\n0. Changer d arbre");
        printf("\n1. Creer un nouvel arbre");
        printf("\n2. Affichage dictionnaire et avance");
        printf("\n3. Ajouter un mot dans un arbre");
        printf("\n4. Retirer un mot d un arbre");
        printf("\n5. Verifier si un arbre est parfait");
        printf("\n6. Verifier si un arbre est equilibre");
        printf("\n7. Transformer un arbre en un lexique en liste lineairement chainee et afficher le lexique");
        printf("\n8. Tester la similarite entre deux textes");
        printf("\n9. Quitter");
        destruction = 0;
        printf("\n\nEntrez le numero correspondant a votre choix : ");
        scanf("%s",choix_utilisateur);
        printf("\n");
        if (strlen(choix_utilisateur) > 2)
            printf("Choix invalide\n");
        else
        {
            choix = choix_utilisateur[0];
            switch (choix){
            case '0':
            {
                system("cls");
                printf("=============== Selection d un autre arbre ===============\n\n");
                printf("Entrer le numero d'index de l'arbre: ");
                int tmp = 0;
                scanf("%d",&tmp);
                if (tmp>=0 && tmp<=9){
                    index = tmp;
                    printf("\n\nL arbre d'index %d est selectione\n", index);
                    display_arbre(tab[index]);
                    break;
                }
                printf("\n\nIndex toujours � %d car mauvaise valeur (doit etre en 0 et 9)");
                gets(poubelle);
            }
                break;
            case '1':
            {
                system("cls");
                printf("=============== Creation d'un nouvel arbre ===============\n\n");
                printf("Entrez le mot que vous voulez ajouter (sans espaces !) : ");
                scanf("%s",mot);
                gets(poubelle);
                if (motValide(mot)){
                    tab[index]->racine = creerNoeudVide(mot);
                    printf("\nNoeud cree avec succes !\n\n");
                }else{
                    printf("\nMot invalide (uniquement l'alphabet majuscule et minuscule)\n\n");
                }
                display_arbre(tab[index]);
            
                }
                break;
            case '2':
            {
                system("cls");
                printf("\n\n\n===== SELECTIONNER LE TYPE D AFFICHAGE POUR ARBRE %d =====\n\n", index);
                printf("\n0. Affichage dictionnaire");
                printf("\n1. Affichage avance");
                printf("\n2. Affichage liste");
                printf("\n\nVeuillez selectionner : ");
                scanf("%s",choix_arbre);
                gets(poubelle);
                choixb = choix_arbre[0];
                if (choixb=='0'){
                    printf("=============== Affichage dictionnaire arbre %d ===============\n\n", index);
                    display_arbre(tab[index]);
                }
                if (choixb=='1'){
                    printf("=============== Affichage avance arbre %d ===============\n\n", index);
                    avl_print(tab[index]);
                }
                if (choixb=='2')
                {
                    printf("=============== Affichage liste arbre %d ===============\n\n", index);
                    supprimerListe(tab_l[index]);
                    tab_l[index] = pack_list(tab[index]);
                    display_list(tab_l[index]);
                }
                }
                break;
            case '3':
            {
                system("cls");
                printf("=============== Ajout d'un mot dans un arbre ===============\n\n");
                printf("Entrez le mot que vous voulez ajouter (sans espaces !) : ");
                scanf("%s",mot);
                gets(poubelle);
                if (motValide(mot)){
                    tab[index]->racine = ajout_noeud(tab[index]->racine, mot);
                    printf("\nMot bien ajoute !\n\n");
                }else{
                    printf("\nMot invalide (uniquement l'alphabet majuscule et minuscule)\n\n");
                }
                display_arbre(tab[index]);
                }
                break;
            case '4':
            {
                system("cls");
                printf("=============== Retirer un mot de l'arbre ===============\n\n");
                display_arbre(tab[index]);
                printf("\n\nEntrez le mot que vous voulez ajouter (sans espaces !) : ");
                scanf("%s",mot);
                gets(poubelle);
                if (motValide(mot)){
                    tab[index]->racine = enlever_occurence(tab[index]->racine, mot);
                }else{
                    printf("\nMot invalide (uniquement l'alphabet majuscule et minuscule)\n\n");
                }
                display_arbre(tab[index]);
            }
                break;
            case '5':
                {
                system("cls");
                printf("=============== Verification parfait ===============\n\n");
                int veref = check_parfait(tab[index]);
                if (veref == 0){
                    printf("\nPAS PARFAIT\n\n");
                    avl_print(tab[index]);
                    break;
                }printf("PARFAIT\n\n");
                avl_print(tab[index]);
                }
                break;
            case '6':
                {
                system("cls");
                printf("=============== Verification equilibre ===============\n\n");
                int veref = check_equilibre(tab[index]->racine);
                if (veref == 0){
                    printf("\nPAS EQULIBRE\n\n");
                    avl_print(tab[index]);
                    break;
                }printf("EQUILIBRE\n\n");
                avl_print(tab[index]);
                }
                break;
            case '7':
                {
                system("cls");
                printf("=============== Liste Chainee ===============\n\n");
                supprimerListe(tab_l[index]);
                tab_l[index] = pack_list(tab[index]);
                display_list(tab_l[index]);
                }
                break;
            case '8':
                {
                system("cls");
                printf("=============== Comparaison Listes Chainees ===============\n\n");
                printf("Saisissez deux index (0-9) pour comparer les lexiques: ");
                int a=0;
                int b= 0;
                scanf("%d %d",&a,&b);
                if(a<=9 && a>=0 && b>=0 && b<=9){
                    supprimerListe(tab_l[a]);
                    supprimerListe(tab_l[b]);
                    tab_l[a] = pack_list(tab[a]);
                    tab_l[b] = pack_list(tab[b]);
                    if (tab_l[a] && tab_l[b]){
                        printf("\n\nListe chainee pour l arbre d index %d\n", a);
                        display_list(tab_l[a]);
                        printf("\n\nListe chainee pour l arbre d index %d\n", b);
                        display_list(tab_l[b]);
                        float simi = similarite(tab_l[a], tab_l[b]);
                        printf("\n\n\nL'indice de jaccard est de : %.2f", simi);
                    }else{
                        printf("ERREUR");
                    }
                    break;
                }
                printf("\n\nles index doivent etre compris entre 0 et 9");
                break;
                }
            case '9':
                system("cls");
                for(int i=0; i<10; i++){
                }
                break;
            default:
                system("cls");
                printf("Choix invalide\n");
                display_arbre(tab[index]);
                break;
            }
        }
    }
    return 0;
}

