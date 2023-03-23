#include <stdio.h>
void findWaitingTime(int n, int processes[], int bt[], int wt[], int at[])
{
    wt[0] = 0;
    for (int i = 1; i < n; i++)
        wt[i] = at[i - 1] + wt[i - 1] + bt[i - 1] - at[i];
}

void findTurnAroundTime(int n, int processes[], int bt[], int wt[], int tat[])
{
    for (int i = 0; i < n; ++i)
        tat[i] = wt[i] + bt[i];
}

void findavgTime(int n, int processes[], int bt[], int wt[], int tat[])
{
    float av_wtime = 0, av_btime = 0, av_ttime = 0;
    for (int i = 0; i < n; i++)
    {
        av_wtime += wt[i];
        av_btime += bt[i];
        av_ttime += tat[i];
    }
    printf("Average Wait-time: \t%f seconds\n", av_wtime / n);
    printf("Average Burst-time: \t%f seconds\n", av_btime / n);
    printf("Average Turn-time: \t%f seconds\n", av_ttime / n);
}

int main()
{
    int processes[] = {1, 2, 3};
    int n = sizeof processes / sizeof processes[0];
    int bt[] = {10, 5, 2};
    int at[] = {2, 10, 12};
    int wt[3];
    int tat[3];

    findWaitingTime(n, processes, bt, wt, at);
    findTurnAroundTime(n, processes, bt, wt, tat);

    printf(" Process \tarrival \tburst \twait \tturnaround\n");
    for (int i = 0; i < n; ++i)
    {
        printf(" %d", i + 1);
        printf("\t\t%d ", at[i]);
        printf("\t\t%d ", bt[i]);
        printf("\t%d   ", wt[i]);
        printf("\t%d \n", tat[i]);
    }

    findavgTime(n, processes, bt, wt, tat);
    return 0;
}
