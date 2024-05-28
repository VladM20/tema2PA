#include "definitii.h"

int isEmpty(Queue *q)
{
    return q->front==NULL;
}

Queue *createQueue()
{
    Queue *q=(Queue*)malloc(sizeof(Queue));
    if(!allocWorked(q,"createQueue(q)"))
        return NULL;

    q->front=NULL;
    q->rear=NULL;
    return q;
}

void enQueue(Queue *q,Team *team)
{
    if(q==NULL || team==NULL)
    {
        printf("Parametrii gresiti in enQueue\n");
        return;
    }

    Node *newNode=(Node*)malloc(sizeof(Node));
    if(!allocWorked(newNode,"enQueue(newNode)"))
        return;
    
    newNode->team=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newNode->team,"enQueue(newNode->team)"))
        return;
    
    copyTeam(team,newNode->team);
    newNode->next=NULL;

    if(q->rear==NULL)
    {
        q->front=newNode;
        q->rear=newNode;
    }
    else
    {
        q->rear->next=newNode;
        q->rear=newNode;
    }
}

Team *deQueue(Queue *q)
{
    if(isEmpty(q))
        return NULL;

    Node *temp=q->front;
    q->front=q->front->next;

    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"deQueue(newTeam)"))
        return NULL;

    copyTeam(temp->team,newTeam);
    if(isEmpty(q))
        q->rear=NULL;
    freeTeam(temp->team);
    free(temp);
    return newTeam;
}

void deleteQueue(Queue **q)
{
    if(*q==NULL)
        return;
    
    Node *nextNode;
    while(!isEmpty(*q))
    {
        nextNode=(*q)->front->next;
        freeTeam((*q)->front->team);
        free((*q)->front);
        (*q)->front=nextNode;
    }
    free(*q);
    *q=NULL;
}