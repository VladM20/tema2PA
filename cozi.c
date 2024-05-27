#include "definitii.h"

int isEmpty(Queue *q)
{
    return q->front==NULL;
}

void freeTeam(Team *team)
{
    if(team==NULL)
        return;
    if(team->name!=NULL)
        free(team->name);
    free(team);
}

void copyTeam(Team *source,Team *destination)
{
    if(source==NULL || destination==NULL)
        return;

    destination->name=(char*)malloc((strlen(source->name)+1)*sizeof(char));
    if(!allocWorked(destination->name,"copyTeam(destination->name)"))
        return;
    strcpy(destination->name,source->name);
    destination->wins=source->wins;
    destination->points=source->points;
    destination->position=source->position;
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

void WritePrestiges(FILE *output,Queue *q)
{
    if(q==NULL)
        return;
    Node *current=q->front;
    while(current!=NULL)
    {
        fprintf(output,"%.4f %s\n",computePrestige(current->team),current->team->name);
        current=current->next;
    }
}