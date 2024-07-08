#include <stdio.h>

typedef struct {
    int pid;     // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int remaining_bt;
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
} Process;

void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void roundRobin(Process p[], int n, int tq) {
    sortByArrival(p, n);
    int completed = 0, currentTime = 0;
    
    while (completed < n) {
        int allIdle = 1;
        
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].remaining_bt > 0) {
                allIdle = 0;
                
                if (p[i].remaining_bt > tq) {
                    currentTime += tq;
                    p[i].remaining_bt -= tq;
                } else {
                    currentTime += p[i].remaining_bt;
                    p[i].remaining_bt = 0;
                    p[i].ct = currentTime;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    completed++;
                }
            }
        }
        
        if (allIdle) {
            currentTime++;
        }
    }
}

void printTable(Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
}

int main() {
    int n, tq;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &tq);
    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining_bt = p[i].bt;
    }

    roundRobin(p, n, tq);
    printTable(p, n);

    return 0;
}
