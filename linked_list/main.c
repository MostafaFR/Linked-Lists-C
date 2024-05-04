#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

#define N 5
#define Limit 100000

int nombreValide(char* str){
    int valide = 1;
    int i = 0;
    int vrai_debut = 0;
    while (valide && i < strlen(str))
    {
        if ('0' > str[i] || '9' < str[i]) 
            valide = 0;
        else
            i++;
    }
    return valide;
} 

int main(){
    List* maListe = (List*)malloc(sizeof(struct List));
    initialize(maListe);
    char nombre[Limit];
    int position;
    char choix_utilisateur[Limit];
    char choix = '0';
    char poubelle[Limit];
    int destruction;
    system("cls");
    printf("Bienvenue dans votre programme de gestion de liste !\n");
    while (choix != '9')
    {
        printf("\nVoici les actions que vous pouvez entreprendre :\n");
        printf("\n1/ Ajouter un nombre en debut de liste");
        printf("\n2/ Ajouter un nombre en fin de liste");
        printf("\n3/ Ajouter un nombre a une certaine position dans la liste");
        printf("\n4/ Supprimer un nombre d'une certaine position dans la liste");
        printf("\n5/ Trier la liste par ordre croissant");
        printf("\n6/ Afficher la liste");
        printf("\n7/ Detruire la liste toute entiere");
        printf("\n8/ Inserez la somme total des elements a la fin de la liste");
        printf("\n9/ Quitter");
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
            case '1':
                system("cls");
                printf("--------------- Ajout d'un nombre en debut de liste ---------------\n\n");
                printf("Entrez le nombre que vous voulez ajouter (sans espaces !) : ");
                scanf("%s",nombre);
                gets(poubelle);
                if (nombreValide(nombre)){
                    insert_begining_list(maListe, nombre);
                    printf("\nNombre ajoute avec succes !\n\n");
                }else{
                    printf("\nNombre invalide\n\n");
                }
                display(maListe);
                break;
            case '2':
                system("cls");
                system("cls");
                printf("--------------- Ajout d'un nombre en fin de liste ---------------\n\n");
                printf("Entrez le nombre que vous voulez ajouter (sans espaces !) : ");
                scanf("%s", nombre);
                gets(poubelle);
                if (nombreValide(nombre))
                {
                    insert_end_list(maListe, nombre);
                    printf("\nNombre ajoute avec succes !\n\n");
                }
                else
                    printf("\nNombre invalide\n\n");
                display(maListe);
                break;
            case '3':
                system("cls");
                printf("--------------- Ajout d'un nombre a une certaine position dans la liste ---------------\n\n");
                printf("Entrez le nombre que vous voulez ajouter (sans espaces !) : ");
                scanf("%s", nombre);
                gets(poubelle);
                printf("Entrez la position du nombre apres lequel vous voulez inserer ce nombre : ");
                scanf("%d", &position);
                gets(poubelle);
                if (nombreValide(nombre))
                {
                    if(insert_after_position(maListe, nombre, position))
                        printf("\nImpossible d'ajouter le nombre a la position specifiee\n\n");
                    else
                        printf("\nNombre ajoute avec succes !\n\n");
                }
                else
                    printf("\nNombre invalide\n\n");
                display(maListe);
                break;
            case '4':
                system("cls");
                printf("--------------- Suppression d'un nombre de la liste ---------------\n\n");
                if (maListe->head == NULL)
                    printf("Impossible : la liste est vide\n\n");
                else
                {
                    printf("Entrez la position du nombre que vous voulez supprimer : ");
                    scanf("%d", &position);
                    gets(poubelle);
                    if (remove_elem(maListe, position))
                        printf("\nPosition invalide\n\n");
                    else
                        printf("\nSuppression reussie\n\n");
                }
                display(maListe);

                break;
            case '5':
                system("cls");
                printf("--------------- Tri de la liste dans l'ordre croissant ---------------\n\n");
                if (sort(maListe))
                    printf("Tri impossible (la liste est vide)\n\n");
                else
                    printf(("Tri realise avec succes !\n\n"));
                display(maListe);
                break;
            case '6':
                system("cls");
                display(maListe);
                break;
            case '7':
                system("cls");
                printf("--------------- Destruction de la liste ---------------\n\n");
                if (maListe->head == NULL)
                    printf("Destruction impossible, la liste est deja vide\n");
                else
                {
                    printf("Voulez vous vraiment supprimer tout le contenu de la liste ? (1 pour oui, 0 pour non) : ");
                    scanf("%d", &destruction);
                    gets(poubelle);
                    if (destruction)
                        destruct(maListe);
                }
                printf("\n");
                display(maListe);
                break;
            case '8':
                system("cls");
                printf("---= AJOUT DE LA SOMME DES ELEMENT EN FIN DE LISTE ---=\n\n");
                if (maListe->head == NULL)
                {
                    printf("Destruction impossible, la liste est deja vide\n");
                }
                else
                    sum(maListe);
                display(maListe);
                break;
            case '9':
                system("cls");
                break;
            default:
                printf("Choix invalide\n");
                break;
            }
        }
    }
    return 0;
}