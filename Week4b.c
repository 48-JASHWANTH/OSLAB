#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid;     // Process ID
    int at;      // Arrival Time
    int bt;      // Burst Time
    int ct;      // Completion Time
    int tat;     // Turnaround Time
    int wt;      // Waiting Time
    int isComplete;
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

void sjf(Process p[], int n) {
    sortByArrival(p, n);
    int completed = 0, currentTime = 0;
    
    while (completed < n) {
        int minBt = INT_MAX;
        int idx = -1;
        
        for (int i = 0; i < n; i++) {
            if (p[i].at <= currentTime && p[i].isComplete==0 && p[i].bt < minBt) {
                minBt = p[i].bt;
                idx = i;
            }
        }
        
        if (idx != -1) {
            currentTime += p[idx].bt;
            p[idx].ct = currentTime;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].isComplete = 1;
            completed++;
        } else {
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
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].isComplete = 0;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
    }

    sjf(p, n);
    printTable(p, n);

    return 0;
}
