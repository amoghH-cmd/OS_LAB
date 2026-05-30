#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], req[n][m], avail[m];
    int finish[n], safeSeq[n];

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("\nEnter Request Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &req[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {

            if(finish[i] == 0) {

                for(j = 0; j < m; j++) {
                    if(req[i][j] > avail[j]) {
                        break;
                    }
                }

                if(j == m) {

                    for(k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            break;
        }
    }

    if(count == n) {

        printf("\nNo Deadlock Detected\n");
        printf("Safe Sequence: ");

        for(i = 0; i < n; i++) {
            printf("P%d ", safeSeq[i]);
        }
    }
    else {

        printf("\nDeadlock Detected!\n");
        printf("Processes in Deadlock: ");

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {
                printf("P%d ", i);
            }
        }
    }

    return 0;
}