#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid; //
    int status;
    int arriv; //
    int wait;  //
    int burst; //
    int turn;  //
    int prior; //
} p;

struct comparePriority
{
    bool operator()(const process &p1, const process &p2)
    {
        return p1.prior > p2.prior;
    }
};

void add_processes(priority_queue<process, vector<process>, comparePriority> &high,
                   priority_queue<process, vector<process>, comparePriority> &med,
                   priority_queue<process, vector<process>, comparePriority> &low,
                   vector<process> &processes,
                   int time)
{

    for (int i = 0; i < processes.size(); ++i)
    {
        if (processes[i].status == 2 && processes[i].arriv <= time)
        {
            if (processes[i].prior > 10)
                high.push(processes[i]);

            else if (processes[i].prior > 5)
                med.push(processes[i]);

            else
                low.push(processes[i]);

            processes[i].status = 1;
        }
    }
}

int main()
{

    vector<process> processes;
    priority_queue<process, vector<process>, comparePriority> high_queue;
    priority_queue<process, vector<process>, comparePriority> med_queue;
    priority_queue<process, vector<process>, comparePriority> low_queue;

    processes.push_back({0, 2, 14, 0, 9, 0, 12});
    processes.push_back({1, 2, 10, 0, 5, 0, 7});
    processes.push_back({2, 2, 9, 0, 6, 0, 2});
    processes.push_back({3, 2, 3, 0, 2, 0, 5});
    processes.push_back({4, 2, 7, 0, 5, 0, 9});

    int time = 0, n = processes.size(), left_jobs = n;
    // add_processes(high_queue, med_queue, low_queue, processes, time);
    while (left_jobs > 0)
    {
        int t = time;
        add_processes(high_queue, med_queue, low_queue, processes, time);
        // cout << processes[0].status << "\n";
        while (!high_queue.empty())
        {
            process p = high_queue.top();
            processes[p.pid].wait = time - p.arriv;
            processes[p.pid].turn = p.burst;
            processes[p.pid].status = -1;

            printf("Executing process %d from high \tqueue starting at %d till %d\n", p.pid, time, time + p.burst);

            time += p.burst;
            high_queue.pop();
            left_jobs--;
            goto next;
        }

        while (!med_queue.empty())
        {
            process p = med_queue.top();
            processes[p.pid].wait = time - p.arriv;
            processes[p.pid].turn = p.burst;
            processes[p.pid].status = -1;

            printf("Executing process %d from medium queue starting at %d till %d\n", p.pid, time, time + p.burst);

            time += p.burst;
            med_queue.pop();
            left_jobs--;
            goto next;
        }
        while (!low_queue.empty())
        {
            process p = low_queue.top();
            processes[p.pid].wait = time - p.arriv;
            processes[p.pid].turn = p.burst;
            processes[p.pid].status = -1;

            printf("Executing process %d from low \tqueue starting at %d till %d\n", p.pid, time, time + p.burst);

            time += p.burst;
            low_queue.pop();
            left_jobs--;
            goto next;
        }
    next:
        if (time == t)
            time++;
    }

    float av_wait = 0,
          av_turn = 0,
          av_burst = 0;

    for (int i = 0; i < n; i++)
    {
        av_turn += processes[i].turn;
        av_wait += processes[i].wait;
        av_burst += processes[i].burst;
    }

    printf(" Process \tarrival \tburst \twait \tturnaround\n");
    for (int i = 0; i < n; ++i)
    {
        printf(" %d", processes[i].pid);
        printf("\t\t%d ", processes[i].arriv);
        printf("\t\t%d ", processes[i].burst);
        printf("\t%d   ", processes[i].wait);
        printf("\t%d \n", processes[i].turn);
    }

    printf("Average Wait Time : \t%f\n", av_wait / n);
    printf("Average Turn Time : \t%f\n", av_turn / n);
    printf("Average Burst Time : \t%f\n", av_burst / n);
}
