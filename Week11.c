#include <stdio.h>
#include <stdlib.h>

int np, nr, alloc[100][100], need[100][100], avail[100], total[100][100];

void takeInput() {
    printf("Enter no. of processes: ");
    scanf("%d", &np);
    printf("Enter no. of resources: ");
    scanf("%d", &nr);
    for (int i = 0; i < np; i++) {
        printf("Enter allocated and total resources for process %d\n", i);
        for (int j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);
        for (int j = 0; j < nr; j++)
            scanf("%d", &total[i][j]);
        for (int j = 0; j < nr; j++)
            need[i][j] = total[i][j] - alloc[i][j];
    }
    printf("Enter available resources: ");
    for (int i = 0; i < nr; i++)
        scanf("%d", &avail[i]);
}

void printTable() {
    printf("Process  \tAlloc\t\tTotal\t\tNeed\n");
    char k = 'A';
    printf("\t");
    for (int i = 0; i < nr; i++)
        printf("%c ", k + i);
    printf("\t");
    for (int i = 0; i < nr; i++)
        printf("%c ", k + i);
    printf("\t");
    for (int i = 0; i < nr; i++)
        printf("%c ", k + i);
    printf("\n");
    for (int i = 0; i < np; i++) {
        printf("P%d\t", i);
        for (int j = 0; j < nr; j++)
            printf("%d ", alloc[i][j]);
        printf("\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", total[i][j]);
        printf("\t");
        for (int j = 0; j < nr; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

int checkStatus(int status[]) {
    int cnt = 0;
    for (int i = 0; i < np; i++)
        if (!status[i])
            cnt++;
    return cnt;
}

void banker() {
    int status[100] = {0}, flag, cnt = 0, prev = np;
    do {
        flag = 0;
        for (int i = 0; i < np; i++) {
            if (!status[i]) {
                int safe = 1;
                for (int j = 0; j < nr; j++) {
                    if (avail[j] < need[i][j]) {
                        safe = 0;
                        break;
                    }
                }
                if (safe) {
                    flag = 1;
                    status[i] = 1;
                    for (int j = 0; j < nr; j++)
                        avail[j] += alloc[i][j];
                    cnt++;
                }
            }
        }
    } while (cnt < np && flag);

    if (cnt == np) {
        printf("Safe sequence exists.\n");
    } else {
        printf("Unsafe state detected.\n");
    }
}

void deadlockDetection() {
    int marked[100] = {0};
    for (int i = 0; i < np; i++) {
        if (!marked[i]) {
            int deadlock = 1;
            for (int j = 0; j < nr; j++) {
                if (need[i][j] > avail[j]) {
                    deadlock = 0;
                    break;
                }
            }
            if (deadlock) {
                printf("Process P%d is in deadlock.\n", i);
                marked[i] = 1;
            }
        }
    }
}

int main() {
    int choice;
    takeInput();
    printTable();
    do {
        printf("Select 1.Banker's algorithm 2.Deadlock detection 3.Exit: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                banker();
                break;
            case 2:
                deadlockDetection();
                break;
            default:
                exit(0);
        }
    } while (1);
}
