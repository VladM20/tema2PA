#include "definitii.h"

int main(int argc,char* argv[])
{
    int **matrix=createMatrix(NR_ECHIPE);
    FILE *input=fopen(argv[1],"rt");
    if(verifyFile(input,argv[1]))
        return 5;

    Queue *winners=createQueue(),*losers=createQueue();
    for(int i=0;i<NR_ECHIPE;i+=2)  //Citire din fisier + Prima runda
    {
        Team *team1=readTeam(input,i);
        Team *team2=readTeam(input,i+1);
        playMatch(team1,team2,winners,losers,matrix);
    }
    fclose(input);

    FILE *outputGraf=fopen(argv[2],"wt");
    if(verifyFile(outputGraf,argv[2]))
        return 5;

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
    fclose(outputGraf);

    enQueue(losers,deQueue(winners));       //Muta echipa castigatoare in aceeasi coada cu restul.
    FILE *outputScor=fopen(argv[3],"wt");
    if(verifyFile(outputScor,argv[3]))
        return 5;

    WritePrestiges(outputScor,losers);
    fclose(outputScor);
    deleteQueue(&winners);
    deleteQueue(&losers);
    return 0;
}