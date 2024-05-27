#include "definitii.h"

#define NR_ECHIPE 32

int allocWorked(void *pointer,char *function)
{
    if(pointer==NULL)
    {
        printf("Nu s-a putut aloca memorie in %s\n",function);
        return 0;
    }
    return 1;
}

void truncateWhiteSpace(char *name)
{
    if(name==NULL)
        return;
    int length=strlen(name);
    while(length>0 && (name[length-1]==' ' || name[length-1]=='\n'  || name[length-1]=='\r'))
        length--;
    name[length]='\0';
}

Team *readTeam(FILE *input,int position)
{
    Team *newTeam=(Team*)malloc(sizeof(Team));
    if(!allocWorked(newTeam,"readTeam(newTeam)"))
        return NULL;
    char name[MAX_LENGTH];
    fscanf(input,"%f",&newTeam->points);
    fgetc(input);   //Pentru spatiul de dupa punctaj
    fgets(name,MAX_LENGTH,input);
    newTeam->name=strdup(name);
    truncateWhiteSpace(newTeam->name);
    newTeam->position=position;
    newTeam->wins=0;
    return newTeam;
}

void playMatch(Team *team1,Team *team2,Queue *winners,Queue *losers, int matrix[NR_ECHIPE][NR_ECHIPE])
{
    if(team1==NULL || team2==NULL || winners==NULL || losers==NULL || team1->name==NULL || team2->name==NULL)
    {
        printf("Parametrii gresiti in playMatch.\n");
        return;
    }
    if(team1->points==team2->points)
    {
        int deciding=strcmp(team1->name,team2->name);
        if(deciding>0)      //castiga team1
        {
            team1->wins++;
            enQueue(winners,team1);
            enQueue(losers,team2);
            matrix[team2->position][team1->position]=1;
        }
        if(deciding<0)      //castiga team2
        {
            team2->wins++;
            enQueue(winners,team2);
            enQueue(losers,team1);
            matrix[team1->position][team2->position]=1;
        }
        return;
    }
    if(team1->points<team2->points)     //castiga team2
    {
        team2->wins++;
        enQueue(winners,team2);
        enQueue(losers,team1);
        matrix[team1->position][team2->position]=1;
        return;
    }
    if(team1->points>team2->points)     //castiga team1
    {
        team1->wins++;
        enQueue(winners,team1);
        enQueue(losers,team2);
        matrix[team2->position][team1->position]=1;
        return;
    }
}

void writeMatrix(FILE *output,int matrix[NR_ECHIPE][NR_ECHIPE])
{
    for(int i=0;i<NR_ECHIPE;i++)
    {
        for(int j=0;j<NR_ECHIPE;j++)
            fprintf(output,"%d ",matrix[i][j]);
        fprintf(output,"\n");
    }
}

void printTeams(Queue *q)
{
    Node *temp=q->front;
    for(int j=0;temp!=NULL;j++)
    {
        printf("%s (%.2f)\n",temp->team->name,temp->team->points);
        temp=temp->next;
    }
}

int main(int argc,char* argv[])
{
    int matrix[NR_ECHIPE][NR_ECHIPE]={0};
    FILE *input=fopen(argv[1],"rt");
    Queue *winners=createQueue(),*losers=createQueue();
    for(int i=0;i<NR_ECHIPE;i+=2)  //Citire din fisier + Prima runda
    {
        Team *team1=readTeam(input,i);
        Team *team2=readTeam(input,i+1);
        playMatch(team1,team2,winners,losers,matrix);
    }
    fclose(input);

    FILE *outputGraf=fopen(argv[2],"wt");
    int remainingTeams=NR_ECHIPE/2;
    while(remainingTeams>1)
    {
        for(int i=0;i<remainingTeams;i+=2)
        {
            Team *team1=deQueue(winners);
            Team *team2=deQueue(winners);
            if(team1==NULL || team2==NULL)
                break;
            playMatch(team1,team2,winners,losers,matrix);
        }
        remainingTeams/=2;
    }
    writeMatrix(outputGraf,matrix);
    return 0;
}