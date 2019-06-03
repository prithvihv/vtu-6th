#include <stdio.h>
struct proc
{
    int id;
    int arrival;
    int burst;
    int rem;
    int wait;
    int finish;
    int turnaround;
    float ratio;
}; //structure to hold the process information
struct proc process[10];
struct proc temp;
int no;

int chkprocess(int);
int nextprocess();
void roundrobin(int, int, int[], int[]);
void srtf(int);

int main()
{
    int n, tq, choice;
    int bt[10], st[10], i, j, k;
    for (;;)
    {
        printf("Enter the choice \n");
        printf(" 1. Round Robin\n 2. SRT\n 3. Exit \n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Round Robin scheduling algorithm\n");
            printf("Enter number of processes:\n");
            scanf("%d", &n);
            printf("Enter burst time for sequences:");
            for (i = 0; i < n; i++)
            {
                scanf("%d", &bt[i]);
                st[i] = bt[i]; //service time
            }
            printf("Enter time quantum:");
            scanf("%d", &tq);
            roundrobin(n, tq, st, bt);
            break;
        case 2:
            printf("\n \n ---SHORTEST REMAINING TIME NEXT---\n \n ");
            printf("\n \n Enter the number of processes: ");
            scanf("%d", &n);
            srtf(n);
            break;
        case 3:
            // exit(0);
            return 0;
        } // end of switch
    }     // end of for
} //end of main()

/**
 * tq time quantum is the time slot 
 * n is the number of processes
 * st is the the time remaining of the bust time
 * bt is burst time 
*/
void roundrobin(int n, int tq, int st[], int bt[])
{
    int time = 0;
    // count variable is used to keep track of the number of processes that are completed
    // sq keeps track of totat time to assign to the tat
    int tat[10], wt[10], i, count = 0, swt = 0, stat = 0, temp1, sq = 0, j, k;
    float awt = 0.0, atat = 0.0;
    while (1) // keep trying till we reach the end
    {
        for (i = 0, count = 0; i < n; i++) // keep sequence 
        {
            temp1 = tq;
            if (st[i] == 0) // when service time of a process equals zero then count value is incremented
            {
                count++;
                continue;
            }

            if (st[i] > tq) // when service time of a process greater than time
            {
                st[i] = st[i] - tq; // quantum value subtracted from service time
            }
            else if (st[i] >= 0)
            {
                temp1 = st[i]; // temp1 stores the service time of a process
                st[i] = 0;     // making service time equals 0
            }
            sq = sq + temp1; // utilizing temp1 value to calculate turn around time
            tat[i] = sq;     // turn around time
        }
        if (n == count) // it indicates all processes have completed their task because the count value
            break;      // incremented when service time equals 0
    }                   //end of while

    for (i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i]; // waiting time calculated from the turnaround time burst time
        swt = swt + wt[i];      // summation of wait time
        stat = stat + tat[i];   // summation of turnaround time
    }
    awt = (float)swt / n;   // average wait time
    atat = (float)stat / n; // average turnaround time
    printf("Process_no Burst time Wait time Turn around time\n");
    for (i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    printf("Avg wait time is %f\n Avg turn around time is %f\n", awt, atat);
}

// check if the theirs still remaining burstTime to process
int chkprocess(int s)
{
    int i;
    for (i = 1; i <= s; i++)
    {
        if (process[i].rem != 0)
            return 1;
    }
    return 0;
}

// find the next process to execute based on shortest bust time
int nextprocess()
{
    int min, l, i;
    min = 32000; //any limit assumed
    for (i = 1; i <= no; i++) // no keeps track of all the process that have already arrived
    {
        if (process[i].rem != 0 && process[i].rem < min)
        {
            min = process[i].rem;
            l = i;
        }
    }
    return l;
} // end of nextprocess

void srtf(int n)
{
    int i, j, k, time = 0;
    float tavg, wavg;
    // take input and store into datastructure
    for (i = 1; i <= n; i++) // start from one and go til the end !
    {
        process[i].id = i;
        printf("\n\nEnter the arrival time for process %d: ", i);
        scanf("%d", &(process[i].arrival));
        printf("Enter the burst time for process %d: ", i);
        scanf("%d", &(process[i].burst));
        process[i].rem = process[i].burst;
    }
    // bubble sort to sort based on arrival time
    for (i = 1; i <= n; i++)
    {
        for (j = i + 1; j <= n; j++)
        {
            if (process[i].arrival > process[j].arrival)
            {
                temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
    no = 0; // keeps track of the processes that are currently running
    j = 1;  // allways looks at the process to execute
    while (chkprocess(n) == 1)
    {
        // check if the next few process are coming in right now
        if (process[no + 1].arrival == time)
        {
            while (process[no + 1].arrival == time)
                no++;
            if (process[j].rem == 0) // ? fail save bad code
                process[j].finish = time;
            j = nextprocess(); // need to calculate nextProcess cause more process were added
        }

        if (process[j].rem != 0) // to calculate the waiting time of a process
        {
            process[j].rem--;
            // update waiting time for all the the processes
            for (i = 1; i <= no; i++)
            {
                if (i != j && process[i].rem != 0)
                    process[i].wait++;
            }
        }
        else
        {
            process[j].finish = time;
            j = nextprocess(); // process we were working on completed so find nextProcess
            time--;            // we dont use this iteration to make calculations we just update j value
            k = j;             // ? badcode store last process so we can access and update for the last iteration
        }
        time++;
    }
    process[k].finish = time;
    printf("\n\n\t\t\t---SHORTEST REMAINING TIME FIRST---");
    printf("\n\n Process Arrival Burst Waiting Finishing turnaround Tr/Tb\n");
    printf("%5s %9s %7s %10s %8s %9s\n\n", "id", "time", "time", "time",
           "time", "time");
    for (i = 1; i <= n; i++)
    {
        process[i].turnaround = process[i].wait + process[i].burst; // calc of turnaround
        process[i].ratio = (float)process[i].turnaround /
                           (float)process[i].burst;
        printf("%5d %8d %7d %8d %10d %9d %10.1f ", process[i].id,
               process[i].arrival, process[i].burst, process[i].wait, process[i].finish,
               process[i].turnaround, process[i].ratio);
        tavg = tavg + process[i].turnaround; //summation of turnaround        time
        wavg = wavg + process[i].wait;       // summation of waiting time
        printf("\n\n");
    }
    tavg = tavg / n; // average turnaround time
    wavg = wavg / n; // average wait time
    printf("tavg=%f\t wavg=%f\n", tavg, wavg);
} // end of srtf