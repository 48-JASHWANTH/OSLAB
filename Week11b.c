#include <stdio.h>

int main() {
    int n, m, i, j, k, alloc[20][20], request[20][20], avail[20];
    
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of Resources: ");
    scanf("%d", &m);
    
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter the Request Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }
    
    printf("Enter the Available Matrix: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    
    int finish[n], work[m];
    
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }
    
    for (i = 0; i < n; i++) {
        finish[i] = 0;
    }
    
    for (k = 0; k < n; k++) {
        int flag = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    finish[i] = 1;
                    flag = 1;
                }
            }
        }
        if (!flag) {
            break;
        }
    }
    
    // Check if all processes are finished
    int deadlocked = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlocked = 1;
            break;
        }
    }
    
    if (deadlocked) {
        printf("Deadlock detected!\n");
    } else {
        printf("No deadlock detected.\n");
    }
    
    return 0;
}
