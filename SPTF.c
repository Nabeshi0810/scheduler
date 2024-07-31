//処理時間順
#include <stdio.h>
#define ProcessNumber 4 

int next_process  (int count, int Finished_process_array[ProcessNumber], int ArrivalTime[ProcessNumber])
{
    for ( int i = 0; i < ProcessNumber; i++)
    {
        if ( ArrivalTime[i] <= count && Finished_process_array[i] == 0)
        {
            Finished_process_array[i] == 1;
            return i; 
        }
    }
    return ProcessNumber;
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
    int count = 0;
    int sum = 0;
    int Finished_process_array[ProcessNumber];
    for ( int j = 0; j < ProcessNumber; j++)
    {
        Finished_process_array[j] = 0;
    }
    while (1)
    {
        int j = next_process (count, &Finished_process_array[0], &ArrivalTime[0]);
        if (j == ProcessNumber)
        {
            count = count + 1;
        }
        else
        {
            count = count + ProcessTime[j];
            sum = sum + count - ArrivalTime[j];
            ProcessTime[j] = 0;
            Finished_process_array[j] = 1;
        }
        if ( finish_check ( &ProcessTime[0] )  == 1)
        {
            break;
        }
    }
    printf ("処理時間順による平均応答時間:%.2f秒\n", (double) sum / ProcessNumber);
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
        fclose (fp);
    }
    return 0;
}
