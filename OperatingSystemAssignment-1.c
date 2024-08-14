#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void FCFS()
{
    int n, i, j;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int start_time[n], end_time[n], arrival_time[n], rt[n], burst_time[n], waiting_time[n], turnaround_time[n], execution_order[n];
    float tat = 0.0, twt = 0.0;
    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time & burst time of Process %d : ", i + 1);
        scanf("%d %d", &arrival_time[i], &burst_time[i]);
        rt[i] = burst_time[i];
    }
    int tt = 0;
    int ct = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(arrival_time[j] <= ct && rt[j] > 0)
            {
                //printf("\nSelected Index is : %d", j);
                //printf("\nBurst Time of Selected index is : %d", burst_time[j]);
                execution_order[tt] = j;
                start_time[tt] = ct;

                ct += burst_time[j];

                turnaround_time[j] = ct - arrival_time[j];
                waiting_time[j] = turnaround_time[j] - burst_time[j];
                tat += turnaround_time[j];
                twt += waiting_time[j];
                rt[j] -= burst_time[j];
                end_time[tt] = ct;
                //printf("\n Value of Completion Time: %d", ct);
                //printf("\nTurnaround time of Process %d is : %d", j, turnaround_time[j]);
                //printf("\nWaiting Time of Process %d is : %d", j, waiting_time[j]);
                tt++;
            }
        }
        if(tt == 0 && execution_order[i] != j)
            ct++;

    }



    printf("\nGantt Chart:\n");
    for(i = 0; i < n; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < n; i++)
        printf("\tP%d\t|", execution_order[i] + 1);
    printf("\n");

    for(i = 0; i < n; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", start_time[0]);
    for(i = 0; i < n; i++)
    {
        printf("\t%d\t", end_time[i]);
    }
    printf("\n\n");



    printf("Process #\tArrival time\tBurst time\t Turnaround time\tWaiting time\n");
    printf("====================================================================================");

    for(i = 0; i < n; i++)
    {
        printf("\n\n     %d\t           %d\t          %d\t             %d\t                   %d", i + 1, arrival_time[i], burst_time[i], turnaround_time[i], waiting_time[i]);
    }

    printf("\n\n=====================================================================================\n");

    printf("\n\n****\t\t Overall Details \t\t****\n");
    printf("\n\tTotal Turnaround Time : %.2f", tat);
    printf("\n\tAverage Turnaround Time : %.2f", tat / n);
    printf("\n\tTotal Waiting Time : %.2f", twt);
    printf("\n\tAverage Waiting Time : %.2f", twt / n);
    printf("\n\tThroughput : %.2f", ct / (float)n);

}
void SJF_Non()
{
    int n, i, j, completed = 0, tt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int shortest_index[n*n], at[n], tat[n], wt[n], bt[n], rt[n], st[n+n], et[n+n], ct = 0, execution_order[n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time of Process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    i = 1;
    shortest_index[0] = -1;
    do
    {
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (rt[j] < shortest) && (rt[j] > 0))
            {
                shortest = rt[j];
                shortest_index[i] = j;
                printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);


            }
        }


        if(shortest_index[i] != -1 && shortest_index[i] != shortest_index[i-1])
        {
            st[tt] = ct;
            execution_order[tt] = shortest_index[i];
            tt++;
            rt[shortest_index[i]] -= bt[shortest_index[i]];
            ct += bt[shortest_index[i]];


            if(rt[shortest_index[i]] == 0)
            {
                printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("===============================================================================\n");
    for(i = 0; i < n; i++)
    {
        printf("\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t     %d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n===============================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
}




/*void sort_by_arrival_time(struct Process processes[], int n) {
    struct Process temp;
    int i, j;
	for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}*/



void SRTF()
{
    int n, i, j, completed = 0, tt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int shortest_index[n*n*n], at[n], tat[n], wt[n], bt[n], rt[n], st[n+n+n], et[n+n+n], ct = 0, execution_order[n+n], shortest[n*n*n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time and burst time of Process %d: ", i+1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    i = 1;
    shortest_index[0] = -1;
    shortest[0] = 9999;
    do
    {
        shortest_index[i] = -1; shortest[i] = 9999;

        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (rt[j] < shortest[i]) && (rt[j] > 0))
            {
                shortest[i] = rt[j];
                shortest_index[i] = j;
            }
        }
        if(shortest_index[i] != shortest_index[i-1] && at[shortest_index[i]] <= ct && rt[shortest_index[i]] <= shortest[i] && rt[shortest_index[i]] > 0)
        {
            //printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);
            execution_order[tt] = shortest_index[i];
            st[tt] = ct;
            tt++;
        }
        rt[shortest_index[i]] -= 1;
        ct++;
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
        }
        i++;
    }while(completed != n);

    //printf("\n\tValue of tt: %d\tValue of i : %d\n", tt, i);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n\nProcess #\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("===============================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t   %d\t\t   %d\t\t    %d", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n===============================================================================");
    printf("\n\n\n\t\t********\tOverall Details \t***********");
    printf("\n\t\t\tTotal Turnaround Time : %.2f", ttat);
    printf("\n\t\t\tAverage Turnaround Time : %.2f", ttat/n);
    printf("\n\t\t\tTotal Waiting Time : %.2f", twt);
    printf("\n\t\t\tAverage Waiting Time : %.2f", twt/n);
    printf("\n\t\t\tThroughput : %.2f\n\n", ct/(float)n);
}

void Priority_Non()
{
    printf("\t\tProgram for implementing Priority Scheduling Algorithm Non-preemptive\n");
    int n, i, j, completed = 0, tt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int shortest_index[n*n], at[n], tat[n], wt[n], bt[n], priority[n], rt[n], st[n+n], et[n+n], ct = 0, execution_order[n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time and priority value of Process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
        rt[i] = bt[i];
    }

    i = 1;
    shortest_index[0] = -1;
    do
    {
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (priority[j] < shortest) && (rt[j] > 0))
            {
                shortest = priority[j];
                shortest_index[i] = j;
            }
        }
        rt[shortest_index[i]] -= bt[shortest_index[i]];
        execution_order[tt] = shortest_index[i];
        st[tt] = ct;
        tt++;
        ct += bt[shortest_index[i]];
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tPriority Value\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("==============================================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t    %d\t\t     %d", i + 1, priority[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n==============================================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
}

// Function to swap two variables
/*void Swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}*/

void Priority_Preemptive()
{
    printf("\n\n*****\t\tPriority Preemptive Scheduling Algorithm\t\t****\n");
    int n, i, j, completed = 0, tt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int shortest_index[n*n*n], at[n], tat[n], wt[n], bt[n], priority[n], rt[n], st[n+n+n], et[n+n+n], ct = 0, execution_order[n+n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
    {
        printf("Enter arrival time, burst time and priority value of Process %d: ", i+1);
        scanf("%d %d %d", &at[i], &bt[i], &priority[i]);
        rt[i] = bt[i];
    }

    i = 1;
    shortest_index[0] = -1;
    do
    {
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (priority[j] < shortest) && (rt[j] > 0))
            {
                shortest = priority[j];
                shortest_index[i] = j;
                if(shortest_index[i] != shortest_index[i-1])
                {
                    //printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);
                    execution_order[tt] = shortest_index[i];
                    st[tt] = ct;
                    tt++;
                }
            }
        }
        rt[shortest_index[i]] -= 1;
        ct++;
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tPriority Value\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("==============================================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t    %d\t\t     %d", i + 1, priority[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n==============================================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
}



float FCFS_Com(int n, int arrival_time[], int burst_time[])
{
    printf("\n\n****\t\tFCFS Algorithm\t\t****\n\n");
    int i, j, rt[n];
    int start_time[n], end_time[n], waiting_time[n], turnaround_time[n], execution_order[n];
    float tat = 0.0, twt = 0.0;
    int tt = 0;
    int ct = 0;
    for(i = 0; i < n; i++)
        rt[i] = burst_time[i];
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(arrival_time[j] <= ct && rt[j] > 0)
            {
                //printf("\nSelected Index is : %d", j);
                //printf("\nBurst Time of Selected index is : %d", burst_time[j]);
                execution_order[tt] = j;
                start_time[tt] = ct;

                ct += burst_time[j];

                turnaround_time[j] = ct - arrival_time[j];
                waiting_time[j] = turnaround_time[j] - burst_time[j];
                tat += turnaround_time[j];
                twt += waiting_time[j];
                rt[j] -= burst_time[j];
                end_time[tt] = ct;
                tt++;
            }
        }
        if(tt == 0 && execution_order[i] != j)
            ct++;
    }



    printf("\nGantt Chart:\n");
    for(i = 0; i < n; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < n; i++)
        printf("\tP%d\t|", execution_order[i] + 1);
    printf("\n");

    for(i = 0; i < n; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", start_time[0]);
    for(i = 0; i < n; i++)
    {
        printf("\t%d\t", end_time[i]);
    }
    printf("\n\n");



    printf("Process #\tArrival time\tBurst time\t Turnaround time\tWaiting time\n");
    printf("====================================================================================");

    for(i = 0; i < n; i++)
    {
        printf("\n\n     %d\t           %d\t          %d\t             %d\t                   %d", i + 1, arrival_time[i], burst_time[i], turnaround_time[i], waiting_time[i]);
    }

    printf("\n\n=====================================================================================\n");

    printf("\n\n****\t\t Overall Details \t\t****\n");
    printf("\n\tTotal Turnaround Time : %.2f", tat);
    printf("\n\tAverage Turnaround Time : %.2f", tat / n);
    printf("\n\tTotal Waiting Time : %.2f", twt);
    printf("\n\tAverage Waiting Time : %.2f", twt / n);
    printf("\n\tThroughput : %.2f", ct / (float)n);
    return (twt / n);
}



float SJF_Com(int n, int at[], int bt[])
{
    printf("\n\n****\t\tSJF Non-preemptive Algorithm\t\t****\n\n");
    int i, j, completed = 0, tt = 0, rt[n];
    int shortest_index[n*n*n], tat[n], wt[n], st[n+n], et[n+n], ct = 0, execution_order[n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
        rt[i] = bt[i];

    i = 1;
    shortest_index[0] = -1;
    do
    {
        //printf("\nValue of I : %d", i);
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            //printf("\n\n\tArrival Time : %d\tRemaining Time : %d", at[j], rt[j]);
            if((at[j] <= ct) && (rt[j] < shortest) && (rt[j] > 0))
            {
                shortest = rt[j];
                shortest_index[i] = j;
                //printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);


            }
        }


        if(shortest_index[i] != -1 && shortest_index[i] != shortest_index[i-1])
        {
            st[tt] = ct;
            execution_order[tt] = shortest_index[i];
            tt++;
            rt[shortest_index[i]] -= bt[shortest_index[i]];
            ct += bt[shortest_index[i]];


            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("===============================================================================\n");
    for(i = 0; i < n; i++)
    {
        printf("\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t     %d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n===============================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
    return (twt / n);
}


float SRTF_COM(int n, int at[], int bt[])
{
    printf("\n\n****\t\tSRTF (SJF Preemptive) Algorithm\t\t****\n\n");
    int i, j, completed = 0, tt = 0;
    int shortest_index[n*n*n], tat[n], wt[n], rt[n], st[n+n+n], et[n+n+n], ct = 0, execution_order[n+n], shortest[n*n*n];
    float ttat = 0.0, twt = 0.0;
    for(i = 0; i < n; i++)
        rt[i] = bt[i];
    i = 1;
    shortest_index[0] = -1;
    shortest[0] = 9999;
    do
    {
        shortest_index[i] = -1; shortest[i] = 9999;

        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (rt[j] < shortest[i]) && (rt[j] > 0))
            {
                shortest[i] = rt[j];
                shortest_index[i] = j;
            }
        }
        if(shortest_index[i] != shortest_index[i-1] && at[shortest_index[i]] <= ct && rt[shortest_index[i]] <= shortest[i] && rt[shortest_index[i]] > 0)
        {
            //printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);
            execution_order[tt] = shortest_index[i];
            st[tt] = ct;
            tt++;
        }
        rt[shortest_index[i]] -= 1;
        ct++;
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
        }
        i++;
    }while(completed != n);

    //printf("\n\tValue of tt: %d\tValue of i : %d\n", tt, i);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n\nProcess #\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("===============================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t   %d\t\t   %d\t\t    %d", i + 1, at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n===============================================================================");
    printf("\n\n\n\t\t********\tOverall Details \t***********");
    printf("\n\t\t\tTotal Turnaround Time : %.2f", ttat);
    printf("\n\t\t\tAverage Turnaround Time : %.2f", ttat/n);
    printf("\n\t\t\tTotal Waiting Time : %.2f", twt);
    printf("\n\t\t\tAverage Waiting Time : %.2f", twt/n);
    printf("\n\t\t\tThroughput : %.2f\n\n", ct/(float)n);
    return (twt / n);
}


float PRIORITY_NCOM(int n, int at[], int bt[],int priority[])
{
    printf("\n\n****\t\tPriority Non-preemptive Algorithm\t\t****\n\n");
    int i, j, completed = 0, tt = 0, rt[n];
    int shortest_index[n*n*n], tat[n], wt[n], st[n+n+n], et[n+n+n], ct = 0, execution_order[n+n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
        rt[i] = bt[i];

    i = 1;
    shortest_index[0] = -1;
    do
    {
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (priority[j] < shortest) && (rt[j] > 0))
            {
                shortest = priority[j];
                shortest_index[i] = j;
            }
        }
        rt[shortest_index[i]] -= bt[shortest_index[i]];
        execution_order[tt] = shortest_index[i];
        st[tt] = ct;
        tt++;
        ct += bt[shortest_index[i]];
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tPriority Value\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("==============================================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t    %d\t\t     %d", i + 1, priority[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n==============================================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
    return (twt / n);
}

float PRIORITY_PCOM(int n,int at[],int bt[],int priority[])
{
    printf("\n\n*****\t\tPriority Preemptive Scheduling Algorithm\t\t****\n");
    int i, j, completed = 0, tt = 0;
    int shortest_index[n*n*n], tat[n], wt[n], rt[n], st[n+n+n], et[n+n+n], ct = 0, execution_order[n+n+n]; //, pid[n*n];
    float ttat = 0.0, twt = 0.0;

    for(i = 0; i < n; i++)
        rt[i] = bt[i];

    i = 1;
    shortest_index[0] = -1;
    do
    {
        shortest_index[i] = -1;
        int shortest = 9999;
        for(j = 0; j < n; j++)
        {
            if((at[j] <= ct) && (priority[j] < shortest) && (rt[j] > 0))
            {
                shortest = priority[j];
                shortest_index[i] = j;
                if(shortest_index[i] != shortest_index[i-1])
                {
                    //printf("\nShortest Index: %d\t Value of i: %d", shortest_index[i], i);
                    execution_order[tt] = shortest_index[i];
                    st[tt] = ct;
                    tt++;
                }
            }
        }
        rt[shortest_index[i]] -= 1;
        ct++;
        if(shortest_index[i] != -1)
        {
            if(rt[shortest_index[i]] == 0)
            {
                //printf("\nFor checking end time: %d\n", shortest_index[i]);
                et[shortest_index[i]] = ct;
                tat[shortest_index[i]] = et[shortest_index[i]] - at[shortest_index[i]];
                wt[shortest_index[i]] = tat[shortest_index[i]] - bt[shortest_index[i]];
                ttat += tat[shortest_index[i]];
                twt += wt[shortest_index[i]];
                completed++;
            }
            i++;
        }
    }while(completed != n);

    printf("\nGantt Chart: \n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n|");
    for(i = 0; i < tt; i++)
        printf("\tP%d\t|", execution_order[i] + 1);

    printf("\n");
    for(i = 0; i < tt; i++)
        printf("----------------");
    printf("-\n");
    printf("%d\t", st[0]);
    for(i = 1; i < tt; i++)
        printf("\t%d\t", st[i]);
    printf("\t%d", et[execution_order[tt-1]]);
    printf("\n\n");
    printf("\n");
    printf("\n\nProcess #\tPriority Value\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("==============================================================================================");
    for(i = 0; i < n; i++)
    {
        printf("\n\n    %d\t\t     %d\t\t     %d\t\t     %d\t\t    %d\t\t     %d", i + 1, priority[i], at[i], bt[i], wt[i], tat[i]);
    }
    printf("\n\n==============================================================================================");
    printf("\n\n\n********\tOverall Details \t***********");
    printf("\nTotal Turnaround Time : %.2f", ttat);
    printf("\nAverage Turnaround Time : %.2f", ttat/n);
    printf("\nTotal Waiting Time : %.2f", twt);
    printf("\nAverage Waiting Time : %.2f", twt/n);
    printf("\nThroughput : %.2f\n\n", ct/(float)n);
    return (twt / n);
}

void compare_algorithms()
{
        printf("\n\n\t\tComparison between Scheduling Algorithms\t\t\n\n");
    int i, n;
    float fcfs, sjf, srtf, priority_n, priority_p;
    printf("Enter number of Processes : ");
    scanf("%d", &n);
    int arrival_time[n], burst_time[n], priority[n];
    for(i = 0; i < n; i++)
    {
        printf("Enter Arrival time, Burst time and Priority value of Process %d : ", i + 1);
        scanf("%d %d %d", &arrival_time[i], &burst_time[i], &priority[i]);
    }
    fcfs = FCFS_Com(n, arrival_time, burst_time);
    sjf = SJF_Com(n, arrival_time, burst_time);
    srtf = SRTF_COM(n, arrival_time, burst_time);
    priority_n = PRIORITY_NCOM(n, arrival_time,burst_time, priority);
    priority_p = PRIORITY_PCOM(n, arrival_time, burst_time, priority);
    printf("************\t\t\t OVERALL COMPARISON \t\t\t**************************");
    printf("\n\t\tFCFS Average Waiting Time : %.2f", fcfs);
    printf("\n\t\tSJF Average Waiting Time : %.2f", sjf);
    printf("\n\t\tSRTF Average Waiting Time : %.2f", srtf);
    printf("\n\t\tPriority Non-preemptive Average Waiting Time : %.2f", priority_n);
    printf("\n\t\tPriority Preemptive Average Waiting Time : %.2f", priority_p);

    float comp[5]; comp[0] = fcfs; comp[1] = sjf; comp[2] = srtf; comp[3] = priority_n; comp[4] = priority_p;

    float shortest = fcfs;
    int shortest_index;
    for(i = 0; i < 5; i++)
    {
        if(comp[i] < shortest)
        {
            shortest_index = i;
            shortest = comp[i];
        }

    }

    switch(shortest_index)
    {
    case 0:
        printf("\n\n\t\tFCFS is the optimal scheduling algorithm in this scenario with Average Waiting Time of %.2f", fcfs);
        break;
    case 1:
        printf("\n\n\t\tSJF is the optimal scheduling algorithm in this scenario with Average Waiting Time of %.2f", sjf);
        break;
    case 2:
        printf("\n\n\t\tSRTF is the optimal scheduling algorithm in this scenario with Average Waiting Time of %.2f", srtf);
        break;
    case 3:
        printf("\n\n\t\tPriority Non-Preemptive is the optimal scheduling algorithm in this scenario with Average Waiting Time of %.2f", priority_n);
        break;
    case 4:
        printf("\n\n\t\tPriority Preemptive is the optimal scheduling algorithm in this scenario with Average Waiting Time of %.2f", priority_p);
        break;
    default:
        printf("\n\n\t\tAll the scheduling algorithms are equally optimal.");
    }
}


int main() {


    int choice;
    do {
        printf("\n\nChoose a scheduling algorithm:\n");
        printf("1. FCFS\n");
        printf("2. SJF Non-preemptive\n");
        printf("3. Priority Non-preemptive\n");
        printf("4. SRTF\n");
        printf("5. Preemptive Priority\n");
        printf("6. Compare Scheduling Algorithms\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nExecuting FCFS Scheduling Algorithm:\n");
                FCFS();
                break;
            case 2:
                printf("\nExecuting SJF Scheduling Algorithm:\n");
                SJF_Non();
                break;
            case 3:
                printf("\nExecuting Priority Scheduling Algorithm:\n");
                Priority_Non();
                break;
            case 4:
                // Implement SRTF scheduling if needed
                SRTF();
                break;
            case 5:
                // Implement Preemptive Priority scheduling if needed
                Priority_Preemptive();
                break;
            case 6:
                compare_algorithms();
                break;
            case 7:
                printf("\nExiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

