#include "definitii.h"

int allocWorked(void *pointer,char *function)
{
    if(pointer==NULL)
    {
        printf("Nu s-a putut aloca memorie in %s\n",function);
        return 0;
    }
    return 1;
}

int verifyFile(FILE *file,char *fileName)
{
    if(file==NULL)
    {
        printf("Nu s-a putut deschide fisierul %s.\n",fileName);
        return 1;
    }
    return 0;
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

void freeTeam(Team *team)
{
    if(team==NULL)
        return;
    if(team->name!=NULL)
        free(team->name);
    free(team);
}

void playMatch(Team *team1,Team *team2,Queue *winners,Queue *losers, int **matrix)
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

int **createMatrix(int size)
{
    int **matrix=(int**)malloc(size*sizeof(int*));
    for(int i=0;i<size;i++)
        matrix[i]=(int*)calloc(size,sizeof(int));
    return matrix;
}

void writeMatrix(FILE *output,int **matrix)
{
    for(int i=0;i<NR_ECHIPE;i++)
    {
        for(int j=0;j<NR_ECHIPE;j++)
            fprintf(output,"%d ",matrix[i][j]);
        fprintf(output,"\n");
    }
}

void freeMatrix(int **matrix,int size)
{
    if(matrix==NULL)
        return;
    
    for(int i=0;i<size;i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

double computePrestige(Team *team)
{
    if(team==NULL)
        return -1;
    int l=1+log2(NR_ECHIPE);
    double p=(Q_CONST*pow((2-Q_CONST),team->wins))/((1<<l)+(pow((2-Q_CONST),l))*(Q_CONST-1));
    return p;
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