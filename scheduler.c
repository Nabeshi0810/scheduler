#include <stdio.h>
#define ProcessNumber 4 //プロセスの数
#define FIXED TIME 2 //定時間

//処理時間順(完成)
void SortByProcessingTime (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
{
    //ソートする(処理時間が小さい順にソート)
    for ( int i = 0; i < ProcessNumber; i++)
    {
        for ( int j = i ; j < ProcessNumber - 1; j++)
        {
            if ( ProcessTime[j] > ProcessTime[j + 1] )
            {
                int t;
                t = ProcessTime[j];
                ProcessTime[j] = ProcessTime[j + 1];
                ProcessTime[j + 1] = t;
                t = ArrivalTime[j];
                ArrivalTime[j] = ArrivalTime[j +1];
                ArrivalTime[j + 1] = t;
                char s;
                s = Name[j];
                Name[j] = Name[j + 1];
                Name[j + 1] = s;
            }
        }
    }
    //時間順に処理
    int count = ArrivalTime[0];
    int sum = 0;
    for ( int i = 0; i < ProcessNumber; i++)
    {
        if ( count < ArrivalTime[i])
        {
            count = ArrivalTime[i];
        }
        count = count + ProcessTime[i];
        sum = sum + count - ArrivalTime[i];;
    }
    printf ("処理時間順による平均応答時間:%.2f秒\n", (double) sum / ProcessNumber);
}

//到着時間順 (完成)
void ArrivalOrder (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
{
    //到着順にソート
    for ( int i = 0; i < ProcessNumber; i++)
    {
        for ( int j = i ; j < ProcessNumber - 1; j++)
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

//ラウンドロビン
void  RoundRobin (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
{
    //到着順にソート
    for ( int i = 0; i < ProcessNumber; i++)
    {
        for ( int j = i ; j < ProcessNumber - 1; j++)
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
    //定時間2でラウンドロビン
    int count = ArrivalTime[0];
    int sum = 0;
    int t;
    while (1)
    {
        
    }
    printf ("定時間2のラウンドロビン:%.2f秒\n", (double) sum / ProcessNumber);
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
        SortByProcessingTime ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
        ArrivalOrder ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
        RoundRobin ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
    }
    fclose (fp);
    return 0;
}
