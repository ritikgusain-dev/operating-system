
#include <stdio.h>  // For input and output functions

int main() {
    int n, m;  // n = number of processes, m = number of resource types

    printf("Enter number of processes: ");
    scanf("%d", &n);  // Read number of processes

    printf("Enter number of resource types: ");
    scanf("%d", &m);  // Read number of resource types

    int alloc[n][m], max[n][m], need[n][m];
    // alloc = resources currently allocated to each process
    // max = maximum resources each process may require
    // need = additional resources required to finish

    int avail[m], finish[n], safeSeq[n];
    // avail = currently available resources
    // finish = indicates whether a process has completed
    // safeSeq = stores the safe execution sequence

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
            // Read allocated resources for process i
        }
    }

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            // Read maximum resource requirement
        }
    }

    printf("Enter Available resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
        // Read available instances of each resource type
    }

    for (int i = 0; i < n; i++) {
        finish[i] = 0;
        // Initially, no process has completed

        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
            // Calculate remaining resource requirement
        }
    }

    int count = 0;
    // Counts how many processes have completed

    while (count < n) {
        int found = 0;
        // Indicates whether a process can safely finish in this pass

        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) {
                // Check only processes that have not finished

                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        break;
                        // If any resource is insufficient, stop checking
                    }
                }

                if (j == m) {
                    // All required resources are available

                    for (int k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                        // Process finishes and releases its allocated resources
                    }

                    safeSeq[count] = i;
                    // Store this process in the safe sequence

                    count++;
                    // One more process has completed

                    finish[i] = 1;
                    // Mark this process as finished

                    found = 1;
                    // A process was successfully completed
                }
            }
        }

        if (found == 0) {
            // No unfinished process could complete

            printf("\nSystem is NOT in a safe state.\n");
            return 0;
            // Stop because no safe sequence was found
        }
    }

    printf("\nSystem is in a SAFE state.\n");
    printf("Safe sequence: ");

    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        // Print each process in the safe sequence

        if (i != n - 1) {
            printf(" -> ");
            // Separate processes with an arrow
        }
    }

    printf("\n");
    return 0;  // End the program successfully
}