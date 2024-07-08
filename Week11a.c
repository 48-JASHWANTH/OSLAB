#include <stdio.h>

int main() {
    int n, m, alloc[20][20], max[20][20], avail[50]; 
    
    printf("Enter the number of Processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of Resources: ");
    scanf("%d", &m);
    
    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the Available Matrix: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }
    
    int need[n][m], finish[n], safesequence[n], work[m],ind = 0;
    
    // Calculating NEED matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    
    printf("NEED matrix is:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf(" %d ", need[i][j]);
        }
        printf("\n");
    }
    

    for (int i = 0; i < m; i++) {
        work[i] = avail[i];
    }
    
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    safesequence[ind++] = i;
                    for (int y = 0; y < m; y++) {
                        work[y] += alloc[i][y];
                    }
                    finish[i] = 1;
                }
            }
        }
    }
    
    // Check if all processes are finished
    int safe = 1;
    for (int i = 0; i < n; i++) {
        if (finish[i] == 0) {
            safe = 0;
            break;
        }
    }
    
    if (safe) {
        printf("\nFollowing is the SAFE Sequence:\n");
        for (int i = 0; i < n; i++) {
            printf(" P%d ", safesequence[i]);
        }
    } else {
        printf("\nThe system is in an UNSAFE state.\n");
    }
    
    return 0;
}
