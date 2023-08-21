#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int work[MAX_RESOURCES];
int finish[MAX_PROCESSES];

int num_processes, num_resources;

void initialize() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the maximum demand matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int safety_check() {
    int i, j, k = 0;

    for (i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < num_processes; i++) {
        finish[i] = 0;
    }

    int safe_sequence[MAX_PROCESSES];
    int sequence_index = 0;

    for (i = 0; i < num_processes; i++) {
        for (j = 0; j < num_resources; j++) {
            if (finish[i] == 0 && need[i][j] <= work[j]) {
                work[j] += allocation[i][j];
                finish[i] = 1;
                safe_sequence[sequence_index++] = i;
                break;
            }
        }
    }

    for (i = 0; i < num_processes; i++) {
        if (finish[i] == 0) {
            return 0; // Unsafe state
        }
    }

    printf("Safe sequence: ");
    for (i = 0; i < num_processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return 1; // Safe state
}

int main() {
    initialize();

    if (safety_check()) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is in an unsafe state.\n");
    }

    return 0;
}
