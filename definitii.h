#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LENGTH 100
#define NR_ECHIPE 32
#define Q_CONST 0.15

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
//Simuleaza un meci, pune echipele in coada corespunzatoare si scrie rezultatul pe matrice.
void playMatch(Team *team1,Team *team2,Queue *winners,Queue *losers, int matrix[NR_ECHIPE][NR_ECHIPE]);
//Scrie in fisierul OUTPUT matricea MATRIX.
void writeMatrix(FILE *output,int matrix[NR_ECHIPE][NR_ECHIPE]);
//Calculeaza si returneaza prestigiul unei echipe.
double computePrestige(Team *team);
// Printeaza pe ecran echipele din Q.
void printTeams(Queue *q);

// Verifica daca coada este goala.
int isEmpty(Queue *q);
//Creaza o coada noua.
Queue *createQueue();
//Adauga TEAM in coada Q.
void enQueue(Queue *q,Team *team);
//Returneaza o echipa din coada Q.
Team *deQueue(Queue *q);
//Sterge coada Q.
void deleteQueue(Queue **q);
//Scrie prestigiul si numele echipelor din Q in fisierul OUTPUT.
void WritePrestiges(FILE *output,Queue *q);