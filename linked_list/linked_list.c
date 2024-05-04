#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"

#define N 5
#define Limit 100000

/*pour créer et initialiser une liste vide.*/
void initialize (List *list){
    list->head = NULL;  //Pointeur head vide
    list->tail = NULL;  //Pointeur tail vide
} 

char* retirerZeros(char* str){
    while(*str == '0')  //Selectionne le chiffre suivant tant que c'est 0
        str++;        
    if (!strcmp(str, "")) //Verifie si str est composé que de 0, retourne un seul 0
        return "0"; 
    return str;     //Retourne le pointeur au rang pour lequel le chiffre est different de 0
}

Element* separation(char* str){
    int i;
    Element* first = (Element*)malloc(sizeof(struct Element));     //first est un pointeur sur le premier élément de notre nombre separé
    Element* position = (Element*)malloc(sizeof(struct Element));   //position est un pointeur qui avance au fur et à mesure des nombres séparé
    position = NULL;
    if (strlen(str) > N){        
        for (i = 0; i<N; i++){
            first->data[i] = *str;      //Si notre nombre dépasse les N chiffres, on place ses N premiers
            str++;                      //chiffres dans l'élément pointé par début.
        }
        first->data[N] = '\0';          //Ajoute \0 a la fin du premier element de la separation du nombre
        first->next = (Element*)malloc(sizeof(struct Element));
        position = first->next;         //Selectionne l'element suivant
        while (strlen(str) > N)         //Ensuite et tant qu'il reste de N chiffres à notre nombre,
        {                               //on conitnue notre découpe en avanéant au fur et é mesure position
            for (i = 0; i<N; i++)
            {
                position->data[i] = *str;   
                str++;
            }
            position->data[N] = '\0';
            position->next = (Element*)malloc(sizeof(struct Element));
            position = position->next;
        }
    }
    else{
        position = first;           //Si on a moins de N chiffres dans notre nombre, position=first pour le bon fonctionnement de la suite
    }
    i = 0;                          //Une fois qu'on a moins de N chiffres, on stocke chaque chiffre dans l'élément pointé par position
    while (*str != '\0')
    {
        position->data[i] = *str;
        str++;
        i++;
    }

    position->data[i] = '\0';                   
    position->next = (Element*)malloc(sizeof(struct Element));  //Enfin, on génére l'élément qui marque la fin de notre nombre (pour lequel data = "")
    position = position->next;
    strcpy(position->data, "");
    position->next = NULL;
    return first;
}
 /*Va recontruire le nombre a travers les elements separé de 5chiffres */
void ReconstuctionStr(Element* element, char* str){
    Element* position = element;    //position est un pointeur sur le premier élément de notre nombre separé
    strcpy(str, "");                 
    while(strcmp(position->data, "") != 0){     //Tant qu'on n'arrive pas à la fin du nombre, on concatene les chiffre de l'element suivant
        strcat(str, position->data);
        position = position->next;
    }
}

/*Selectionnement le dernier element d'un nombre, permettra de passer au nombre stocké dans les éléments suivant*/
Element* dernierElement(Element* elem){
    Element* dernier = elem;      //Tant que data est différent de "", on passe à l'élément suivant
    while(strcmp(dernier->data, "") != 0)    //On retourne alors un pointeur sur l'élément pour lequel data = "", qui marque la dernier de l'élément passé en paramètre
        dernier = dernier->next;
    return dernier;
}

/*Permet de lirer la mémoire alloué aux éléments stockant un nombre*/
void freeElement(Element*element){
    Element*tmp = element; 
    element = element->next;  
    while (strcmp(element->data, "") != 0){
        free(tmp);
        tmp = element;
        element = element->next;
    }
    free(tmp);
    free(element);
}

/*pour insérer un nombre représenté par la
chaîne de caractères str dans la liste chaînée list si la liste est initialement vide.*/
void insert_empty_list (List *list, char *str){
    if (list->head == NULL){
        Element*New = separation(str);  //New est un pointeur sur le premier élément de notre nombre separé
        list->head = New;       //On fait pointer head et tail sur le nouvel élément new
        list->tail = New;
    }
}

/*pour insérer un nombre représenté par
la chaîne de caractères str au début de la liste chaînée list si la liste contient initialement
des éléments.*/
void insert_begining_list (List *list, char *str){
    if (list->head != NULL){
        Element*New = separation(str);      //New est un pointeur sur le premier élément de notre nombre separé
        dernierElement(New)->next = list->head;     //On lie le next du nouvel élement à l'ancien
        list->head = New;       //Changement du head pour l'insertion en début de liste
    }else{
        insert_empty_list(list, str);   // Si Liste vide, alors on utilise la fonction approrié
    }
}

/*pour insérer un nombre représenté par la
chaîne de caractères str à la fin de la liste list si la liste contient initialement des éléments.*/
void insert_end_list (List *list, char *str){
    if (list->head != NULL){
        Element*New = separation(str);      //New est un pointeur sur le premier élément de notre nombre separé
        dernierElement(list->tail)->next = New;     //On lie le next du dernier élement de la liste au nouveau
        list->tail = New;       //On lie le next du nouvel élement à l'ancien
    }else{
        insert_empty_list(list, str);       // Si Liste vide, alors on utilise la fonction approrié
    }
}

/*pour insérer un nombre
représenté par la chaîne de caractères str après le pème nombre dans la liste si la liste
contient initialement des éléments. Cette fonction retourne 0 si l’insertion a été réalisée et
-1 en cas d’échec (si la position du nombre à ajouter, indiqué par l’utilisateur, n’existe pas
dans la liste).*/
int insert_after_position (List *list, char *str, int p){
    if (list->head == NULL || p<0){     //Retourne -1 si la liste est vide ou la position negative
        return -1;
    }
    if(p==0){   //Ajoute le nombre en début de liste si la position est egale a 0
        insert_begining_list(list,str);
        return 0;
    }

    Element*position = list->head;      //Selectionne Le premier élement
    int i=1; 
    while(dernierElement(position)->next != NULL && p!=i){  //On parcours les premiers élement des nombre avec un compteur pour trouver la position
        position = dernierElement(position)->next;
        i++;
    }
    if(p!=i){   // Retour -1 si la psition est supérieur aux nombre stocké dans la liste 
        return -1;
    }
    if(dernierElement(position)->next == NULL){ //ajoute en fin de liste si la position entrée est égale au dernier nombre de la liste
        insert_end_list(list,str);
        return 0;
    }

    Element*New = separation(str);  //New est un pointeur sur le premier élément de notre nombre separé
    dernierElement(New)->next = dernierElement(position)->next;     //On fait pointer le nouvel élement sur son next approrié
    dernierElement(position)->next = New;       //On fait pointer le next de l'élément a la position p sur le nouveau nombre separé
    return 0;
}

/*pour supprimer le pème nombre représenté par une chaîne
de caractères dans la liste si la liste contient initialement des éléments. Cette fonction
retourne 0 si la suppression a été réalisée et -1 en cas d’échec (si la liste est vide ou si la
position du nombre à supprimer, indiqué par l’utilisateur, n’existe pas dans la liste).*/
int remove_elem (List *list, int p){
    if (list->head == NULL || p<=0){ //Retourne -1 si list vide ou p<=0
        return -1;
    }
    if(p==1){ //Supprime le premier element de la liste si p=1
        Element* tmp = list->head;
        list->head = dernierElement(list->head)->next;
        freeElement(tmp);
        return 0;
    }
    
    Element*N1 = list->head;
    Element*N2 = dernierElement(list->head)->next;
    int m=2;                
    while(p!=m && dernierElement(N2)->next != NULL){    //On parcours les premiers élement des nombre avec un compteur pour trouver la position
        m++;
        N1 = N2;
        N2 = dernierElement(N2)->next;
    }
    if(p!=m){   // Retour -1 si la psition est supérieur aux nombre stocké dans la liste 
        return -1;
    }
    if(dernierElement(N2)->next == NULL){            //supprimele dernier element de la liste si la position entrée est égale au dernier nombre de la liste
        dernierElement(N1)->next = NULL;
        list->tail = N1;
        freeElement(N2);
        return 0;
    }
    dernierElement(N1)->next = dernierElement(N2)->next;    //Fait pointer l'element precedent à l'element suivant
    freeElement(N2);    //Libere la memoire
    return 0;
}

/*pour comparer les deux nombres représentés par
les chaînes de caractères str1 et str2. Cette fonction retourne 1 si le premier nombre
représenté par str1 est plus grand que le deuxième représenté par str2, et retourne 2 si
c’est l’autre cas.*/
int compare(char* str1, char* str2)
{
    if (strlen(str1) > strlen(str2))    
        return 1;
    if (strlen(str2) > strlen(str1))    
        return 2;
    if (*str1 > *str2)                  
        return 1;                       
    if (*str2 > *str1)                  
        return 2;
    if (strlen(str1) == 1 && *str1 == *str2)    
        return 2;
    return compare(++str1, ++str2);     
}
 

int sort(List *list){
    if (list->head == NULL){
        return -1;
    }
    Element*N1,*N2,*N3,*tmp;        //On initialise les élément qui vont nous servir a selectionner les element
    char V2[Limit],V3[Limit];
    int indicateur = 1;
    while(indicateur == 1){     //variable indicateur qui nous permet de savoir si la liste est trié
        indicateur = 0;
        N2=list->head;
        N3=dernierElement(N2)->next;
        N1=NULL;
        while(N3 != NULL){  //On parcours tous les élements de la liste tant que l'on est pas arrivé au dernier
            ReconstuctionStr(N2, V2);
            ReconstuctionStr(N3, V3);
            if (compare(retirerZeros(V2),retirerZeros(V3)) == 1){  //Compare les deux nombres selectionné après avoir retiré les zeros au début
                if(N1 == NULL){
                    list->head = N3;
                }else{
                    dernierElement(N1)->next=N3;
                }
                dernierElement(N2)->next=dernierElement(N3)->next;
                dernierElement(N3)->next=N2;
                tmp =N2;
                N2=N3;
                N3=tmp;
                if (dernierElement(N3)->next == NULL){  //Si l'on a selectionné le dernier élement, on fait pointer le tail sur le bon après avoir permuté les nombres
                    list->tail = N3;
                }
                indicateur = 1;
            }
            N1=N2;
            N2=N3;
            N3=dernierElement(N3)->next;
        }
    }
    return 0;
}

/*pour afficher les nombres représentés dans la liste. Cette
fonction doit afficher « EMPTY LIST » si la liste est vide.*/
void display(List* list){
    printf("==== Votre liste ====\n\n");
    if (list->head == NULL){
        printf("EMPTY LIST\n");         //Pour afficher la liste, on parcourt la liste, on reconstitue le nombre
    }else{                                //représenté é l'aide de nombre_correspondant, et on l'affiche
    
        char nombre[Limit] = "";
        
        Element* position = list->head;
            while(position != NULL){

                ReconstuctionStr(position, nombre);
                printf("%s\n", nombre);
                position = dernierElement(position)->next;
                
            }
    }
    printf("\n======================\n");
}

/*qui détruit la liste toute entière.*/
void destruct (List *list){
    Element* position = dernierElement(list->head)->next;
    while(position != NULL){        //Tant que l'on parcours les element et que ce n'est pas le dernier, on supprime
        freeElement(list->head);    
        list->head = position;
        position = dernierElement(list->head)->next;
    }
    freeElement(list->head);    //libere l'element head et initialise une liste vide
    list->head = NULL;
    list->tail = NULL;
}



void sum (List *list){
    char nombre[Limit] = "";
    if (list->head == NULL){    //Si liste vide
        printf("\nImpossible : la liste est vide\n");
        return;
    }                                
    if(dernierElement(list->head)->next == NULL){   //Si la liste contient 1 nombre seulement
        ReconstuctionStr(list->head, nombre);
        insert_end_list(list,nombre); 
        return;
    }
    char sum[Limit]= "0";
    int retenue=0,b;
    Element* position = list->head;
    while(position != NULL){        //Parcours les element de la liste dans le but de les reconstruire et de la sommer avec la chaine de caractere sum
        ReconstuctionStr(position, nombre);
        unsigned long longueur = fmax(strlen(nombre),strlen(sum));
        retenue = 0;
        while(strlen(sum)<longueur){    //Ajoute des zeros pour rendre la longueur de chaine de caractere egale a celle que l'on va sommer
            char tmp[Limit] ="0";
            strcat(tmp, sum);
            strcpy(sum,tmp);
        }
        while(strlen(nombre)<longueur){    //Ajoute des zeros pour rendre la longueur de chaine de caractere egale a celle que l'on va sommer
            char tmp[Limit] ="0";
            strcat(tmp, nombre);
            strcpy(nombre,tmp);
        }
        for(int p=1;p<=strlen(nombre);p++){ //Parcours chaque chiffre et le somme avec celui de la meme position dans l'autre nombre
            int a = (int)(sum[strlen(sum)-p]-'0');
            int b = (int)(nombre[strlen(nombre)-p]-'0');
            int intTmp = (a+b) + retenue;
            char strTmp[Limit]="0";
            sprintf(strTmp,"%d",intTmp);
            if(intTmp<10){
                sum[strlen(sum)-p] = strTmp[0];
                retenue = 0;
            }else{
                sum[strlen(sum)-p] = strTmp[1];
                retenue = 1;
            }
        }
        position = position->next;
        if(retenue){        //On ajoute un 1 au début de la chaine de caractere si il y a une retenue
            char tmp[Limit] ="1";
            strcat(tmp, sum);
            strcpy(sum,tmp);
        }
    }
    insert_end_list(list,retirerZeros(sum)); //On insert en fin de liste la somme après avoir retiré tous les zéros
}