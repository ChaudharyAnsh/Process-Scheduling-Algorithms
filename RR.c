#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int processes[100][5];
    /*
        status = -1, completed
                  0, old
                  1, new
                  2, not yet available

        status, arrival, burst, waiting, turnaround
    */
    int n = 3;
    int time = 0, left_jobs = n;

    int initial_bursts[n];

    processes[0][0] = 2;
    processes[0][1] = 2;
    processes[0][2] = 10;

    processes[1][0] = 2;
    processes[1][1] = 1;
    processes[1][2] = 2;

    processes[2][0] = 2;
    processes[2][1] = 20;
    processes[2][2] = 5;

    for (int i = 0; i < n; ++i)
        initial_bursts[i] = processes[i][2];
    int i = 0, quantum = 2;
    float av_wait = 0,
          av_turn = 0,
          av_burst = 0;

    for (int i = 0; i < n; i++)
        av_burst += processes[i][2];

    while (left_jobs > 0)
    {
    find_job:
        for (int j = 0; j < n; j++)
            if (processes[j][0] == 2 && time >= processes[j][1])
                processes[j][0] = 1;

        for (int j = 0; j < n; j++)
        {
            if (processes[(i + j) % n][0] == 0 || processes[(i + j) % n][0] == 1)
            {
                i = (i + j) % n;
                goto execution;
            }
        }
        time++;
        goto find_job;

    execution:
        fflush(stdout);
        if (processes[i][0] == 1)
        {
            processes[i][3] = time - processes[i][1];
            processes[i][0] = 0;
        }
        time += min(processes[i][2], quantum);
        processes[i][2] -= min(processes[i][2], quantum);
        if (processes[i][2] == 0)
        {
            // turnaround = curren time - (arrival + wait)
            processes[i][4] = time - (processes[i][1] + processes[i][3]);
            left_jobs--;
            processes[i][0] = -1;
        }
        i = (i + 1) % n;
    }

    printf("out\n");
    fflush(stdout);
    for (int i = 0; i < n; i++)
    {
        av_turn += processes[i][4];
        av_wait += processes[i][3];
    }
    printf(" Process \tarrival \tburst \twait \tturnaround\n");
    for (int i = 0; i < n; ++i)
    {
        printf(" %d", i + 1);
        printf("\t\t%d ", processes[i][1]);
        printf("\t\t%d ", initial_bursts[i]);
        printf("\t%d   ", processes[i][3]);
        printf("\t%d \n", processes[i][4]);
    }

    printf("Average Wait Time : \t%f\n", av_wait / n);
    printf("Average Turn Time : \t%f\n", av_turn / n);
    printf("Average Burst Time : \t%f\n", av_burst / n);
}