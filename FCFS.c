// Essam Mohamed Shaltout

#include <stdio.h>

int getFirstNotVisited(int * visited, int n)
{
    for(int i = 0; i < n; i++)
    {
        if(!visited[i]) return i;
    }
    return -1;
}

int findMin(int * arr, int n ,int * visited)
{
    int min = getFirstNotVisited(visited,n);
    for(int i = 0; i < (n-1); i++)
    {
        if(arr[i] < arr[min] && !visited[i]) min = i;
    }
    return min;
}

void calculateTurnAroundTimeForIndex(int * waiting_time, int * brust_time, int * turnaround_time, int index)
{
    turnaround_time[index] = waiting_time[index] + brust_time[index];
}

void calculateTurnAroundTime(int * waiting_time, int * brust_time, int * turnaround_time, int n)
{
    for(int i = 0; i < n; i ++)
        calculateTurnAroundTimeForIndex(waiting_time, brust_time, turnaround_time, i);
}

void calculateWaitingTime(int * arrival_time, int * waiting_time, int n, int * turnaround_time, int * brust_time, int * visited, int * end_time)
{
    int min;
    min = findMin(arrival_time, n, visited);
    visited[min] = 1;
    waiting_time[min] = 0;
    int previous_min = min;
    end_time[min] = brust_time[min] + arrival_time[min];
    for(int i = 0; i < (n-1); i++)
    {
        min = findMin(arrival_time,n,visited);
        end_time[min] = end_time[previous_min] + brust_time[min];
        waiting_time[min] = end_time[previous_min] - arrival_time[min];
        if(waiting_time[min] < 0) 
        {
            waiting_time[min] = 0;
            end_time[min] = arrival_time[min] + brust_time[min];
        }
        visited[min] = 1;
        previous_min = min;
    }
}

double calculateAverage(int arr[], int n)
{
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += arr[i];
    return ((double) sum)/n;
}

int main(void)
{
    int n;
    printf("Please Enter Number of processes : ");
    scanf("%d",&n);
    int arrival_time[n], brust_time[n], waiting_time[n], turnaround_time[n], visited[n],end_time[n];


    for(int i = 0; i < n; i++)
    {
        printf("Please Enter Process %d arrival time : ",i+1);
        scanf("%d",&arrival_time[i]);
        printf("Please Enter Process %d brust time : ",i+1);
        scanf("%d",&brust_time[i]);
    }

    for(int i = 0; i < n; i++)
        visited[i] = 0;

    calculateWaitingTime(arrival_time, waiting_time, n, turnaround_time, brust_time, visited, end_time);
    calculateTurnAroundTime(waiting_time,brust_time,turnaround_time,n);
    double average_waiting_time = calculateAverage(waiting_time, n);
    double average_turnaround_time = calculateAverage(turnaround_time, n);

    printf("Process\tArrival Time\tBrust Time \tWaiting Time \tTurnaround Time\n");    
    for(int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], brust_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("\nAverage Waiting Time : %F\nAverage Turnaround Time: %F\n",average_waiting_time,average_turnaround_time);
    return 0;
}