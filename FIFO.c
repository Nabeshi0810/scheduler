//到着時間順
#include <stdio.h>
#define ProcessNumber 4 //プロセスの数

void ArrivalOrder (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
{
    //ソートする(到着時間の早い順にソート)
    for ( int i = 0; i < ProcessNumber; i++)
    {
        for ( int j = i ; j < ProcessNumber - 1 - i; j++)
        {
            if ( ArrivalTime[j] > ArrivalTime[j + 1] )
            {
                int t;
                t = ArrivalTime[j];
                ArrivalTime[j] = ArrivalTime[j +1];
                ArrivalTime[j + 1] = t;
                t = ProcessTime[j];
                ProcessTime[j] = ProcessTime[j + 1];
                ProcessTime[j + 1] = t;
                char s;
                s = Name[j];
                Name[j] = Name[j + 1];
                Name[j + 1] = s;
            }
        }
    }
    //到着順に処理
    int count = ArrivalTime[0];
    int sum = 0;
    for ( int  i = 0; i < ProcessNumber; i++)
    {
        if ( count < ArrivalTime[i] )
        {
            count = ArrivalTime[i];
        }
        count = count + ProcessTime[i];
        sum = sum + count - ArrivalTime[i];
    }
    printf ("到着時間順による平均応答時間:%.2f秒\n", (double) sum / ProcessNumber );
}

int main (void)
{
    FILE *fp;
    fp = fopen ("./scheduler.txt" , "r");
    char Name[ProcessNumber];
    int  ArrivalTime[ProcessNumber];
    int  ProcessTime[ProcessNumber];
    if (fp == NULL)
    {
        printf ("open fault\n");
        return 0;
    }
    else
    {
        for ( int i = 0; i < ProcessNumber; i++)
        {
            fscanf ( fp, "%s %d %d", &Name[i], &ArrivalTime[i], &ProcessTime[i]);
        }
        ArrivalOrder ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
        fclose (fp);
    }
    return 0;
}
