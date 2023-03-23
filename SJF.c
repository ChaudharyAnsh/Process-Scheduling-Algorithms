#include <stdio.h>

int main()
{

    int processes[100][5];
    /*
        id, arrival, burst, waiting, turnaround
    */
    int n = 3;
    int time = 0, left_jobs = n;
    float av_wait = 0,
          av_turn = 0,
          av_burst = 0;

    processes[0][0] = 1;
    processes[0][1] = 2;
    processes[0][2] = 10;

    processes[1][0] = 2;
    processes[1][1] = 10;
    processes[1][2] = 2;

    processes[2][0] = 3;
    processes[2][1] = 12;
    processes[2][2] = 5;

    while (left_jobs != 0)
    {
        int i = 0;
        while (processes[i][1] <= time && i < n)
            i++;

        if (i == 0 && (processes[0][0] == -1 || processes[0][1] > time))
        {
            time++;
            continue;
        }
        int mn = 0;
        for (int j = 0; j < i; ++j)
        {
            if (processes[j][0] == -1)
                continue;
            if (processes[j][2] < processes[mn][2])
                mn = j;
        }
        processes[mn][3] = time - processes[mn][1];
        processes[mn][4] = processes[mn][2];
        processes[mn][0] = -1;
        time += processes[mn][2];
        left_jobs -= 1;
    }

    for (int i = 0; i < n; ++i)
    {
        av_wait += processes[i][3];
        av_turn += processes[i][4];
        av_burst += processes[i][2];
    }

    printf(" Process \tarrival \tburst \twait \tturnaround\n");
    for (int i = 0; i < n; ++i)
    {
        printf(" %d", i + 1);
        printf("\t\t%d ", processes[i][1]);
        printf("\t\t%d ", processes[i][2]);
        printf("\t%d   ", processes[i][3]);
        printf("\t%d \n", processes[i][4]);
    }

    printf("Average Wait Time : \t%f\n", av_wait / n);
    printf("Average Turn Time : \t%f\n", av_turn / n);
    printf("Average Burst Time : \t%f\n", av_burst / n);
}
