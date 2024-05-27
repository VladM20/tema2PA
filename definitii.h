#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct Team
{
    int position;
    int wins;
    char *name;
    float points;
} Team;

typedef struct Node
{
    Team *team;
    struct Node *next;
} Node;

typedef struct Queue
{
    Node *front,*rear;
} Queue;

//Verifica alocarea dinamica a POINTER.
int allocWorked(void *pointer,char *function);
//Sterge ' ','\n','\r', daca sunt, din NAME.
void truncateWhiteSpace(char *name);
//Citeste o echipa din INPUT si returneaza un pointer catre aceasta.
Team *readTeam(FILE *input,int position);


//Verifica daca coada este goala.
int isEmpty(Queue *q);
//Creaza o coada noua.
Queue *createQueue();
//Adauga TEAM in coada Q.
void enQueue(Queue *q,Team *team);
//Returneaza o echipa din coada Q.
Team *deQueue(Queue *q);