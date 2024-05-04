#define N 5
typedef struct Element{
    char data[N+1];
    struct Element *next;
}Element;

typedef struct List{
    struct Element *head; 
    struct Element *tail;
}List;

/*Initialisation de toutes les fonctions dans linked_list.c*/

void initialize (List *list);
Element* separation(char* str);
void ReconstuctionStr(Element* element, char* str);
Element* dernierElement(Element* elem);
char* retirerZeros(char* str);
void insert_empty_list (List *list, char *str);
void insert_begining_list (List *list, char *str);
void insert_end_list (List *list, char *str);
int insert_after_position (List *list, char *str, int p);
int remove_elem (List *list, int p);
int compare (char *str1, char *str2);
int sort(List *list);
void display(List* list);
void destruct (List *list);
void freeElement(Element*element);
void sum (List *list);
