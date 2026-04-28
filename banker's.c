#include <stdio.h>

#define MAX 10

int main() {
    int n, m; // n = number of processes, m = number of resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX], finish[MAX] = {0}, safeSeq[MAX];

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");
    for(int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;

    while(count < n) {
        int found = 0;

        for(int i = 0; i < n; i++) {
            if(finish[i] == 0) {

                int canExecute = 1;

                for(int j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        canExecute = 0;
                        break;
                    }
                }

                if(canExecute) {
                    // Add allocated resources back to available
                    for(int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT in a safe state (Deadlock possible)\n");
            return 0;
        }
    }

    // Print Safe Sequence
    printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
    for(int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if(i != n - 1)
            printf(" -> ");
    }
    printf("\n");

    return 0;
}
