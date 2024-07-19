#include <stdio.h>
#define ProcessNumber 4 //プロセスの数
#define FIXED_TIME 2 //定時間

//処理時間順(完成)
void SortByProcessingTime (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
{
    //ソートする(処理時間が早い順にソート)
    for ( int i = 0; i < ProcessNumber; i++)
    {
        for ( int j = i ; j < ProcessNumber - 1 - i; j++)
        {
            if ( ProcessTime[j] > ProcessTime[j + 1] )
            {
                int t;
                t = ProcessTime[j];
                ProcessTime[j] = ProcessTime[j + 1];
                ProcessTime[j + 1] = t;
                t = ArrivalTime[j];
                ArrivalTime[j] = ArrivalTime[j + 1];
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

int finish_check ( int ProcessTime[ProcessNumber] )
{
    for ( int i = 0; i < ProcessNumber; i++)
    {
        if ( ProcessTime[i] != 0 )
        {
            return 0;
        }
    }
    return 1;
}

//ラウンドロビン
void RoundRobin (char Name[ProcessNumber], int ArrivalTime[ProcessNumber], int ProcessTime[ProcessNumber])
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
                ArrivalTime[j] = ArrivalTime[j + 1];
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
    int count = ArrivalTime[0];
    int sum = 0;
    int array[10000];
    int array_now = 0;
    int array_final = 1;
    array[array_now] = 0;
    int k;
    int l = 1;
    //定時間FIXED_TIMEでラウンドロビン
    while (1)
    {
        //プロセスの処理
        if ( ProcessTime[array[array_now]] > FIXED_TIME )
        {
            count = count + FIXED_TIME;
            ProcessTime[array[array_now]] = ProcessTime[array[array_now]] - FIXED_TIME;
            k = 1;
            // printf ("%c\n",Name[array[array_now]]);
        }
        else if ( 0 < ProcessTime[array[array_now]]  && ProcessTime[array[array_now]] <= FIXED_TIME )
        {
            count = count + ProcessTime[array[array_now]];
            ProcessTime[array[array_now]] = 0;
            sum = sum + count - ArrivalTime[array[array_now]];
            k = 0;
            // printf ("%c is finished\n",Name[array[array_now]]);
        }
        //全てのプロセスが終了したか確認
        if ( finish_check ( &ProcessTime[0] ) )
        {
            break;
        }
        //到着時刻を過ぎ、まだ処理がされていないプロセスを配列の最後に置く
        for ( int j = l; j < ProcessNumber; j++)
        {
            if (count >= ArrivalTime[j])
            {
                l = l + 1;
                array[array_final] = j;
                array_final = array_final + 1;
            }
        }
        //今の処理で終了してないプロセスは配列の最後に置く
        if ( k == 1 )
        {
            array[array_final] = array[array_now];
            array_final = array_final + 1;
        }
        array_now = array_now + 1;
    }
    printf ("定時間%d秒のラウンドロビン:%.2f秒\n" , FIXED_TIME, (double) sum / ProcessNumber);
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
        fclose (fp);
        SortByProcessingTime ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
        ArrivalOrder ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
        RoundRobin ( &Name[0], &ArrivalTime[0], &ProcessTime[0]);
    }
    return 0;
}
