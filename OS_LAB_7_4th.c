#include <stdio.h>
#include <stdlib.h>

// Function to simulate FCFS disk scheduling algorithm
void fcfs(int queue[], int n, int head) {
    int totalSeekTime = 0;

    printf("FCFS Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);

    for (int i = 0; i < n; i++) {
        totalSeekTime += abs(head - queue[i]);
        head = queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float) totalSeekTime / n);
}

// Function to simulate SCAN disk scheduling algorithm
void scan(int queue[], int n, int head, int maxCylinder) {
    int totalSeekTime = 0;

    printf("\nSCAN Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);

    // Sort the queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                int temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }

    // Find the position where the head is located in the sorted queue
    int position = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i] >= head) {
            position = i;
            break;
        }
    }

    // Head moves towards the higher cylinders
    for (int i = position; i < n; i++) {
        totalSeekTime += abs(head - queue[i]);
        head = queue[i];
        printf(" -> %d", head);
    }

    // Head moves towards the lower cylinders
    for (int i = position - 1; i >= 0; i--) {
        totalSeekTime += abs(head - queue[i]);
        head = queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float) totalSeekTime / n);
}

// Function to simulate C-SCAN disk scheduling algorithm
void cscan(int queue[], int n, int head, int maxCylinder) {
    int totalSeekTime = 0;

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head movement sequence: %d", head);

    // Sort the queue in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j] > queue[j + 1]) {
                int temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }

    // Find the position where the head is located in the sorted queue
    int position = 0;
    for (int i = 0; i < n; i++) {
        if (queue[i] >= head) {
            position = i;
            break;
        }
    }

    // Head moves towards the higher cylinders
    for (int i = position; i < n; i++) {
        totalSeekTime += abs(head - queue[i]);
        head = queue[i];
        printf(" -> %d", head);
    }

    // Head moves back to the beginning of the disk
    totalSeekTime += abs(head - maxCylinder);
    head = 0;
    printf(" -> 0");

    // Head moves towards the higher cylinders again
    for (int i = 0; i < position; i++) {
        totalSeekTime += abs(head - queue[i]);
        head = queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
    printf("Average Seek Time: %.2f\n", (float) totalSeekTime / n);
}

int main() {
    int n, head, maxCylinder;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int queue[n];
    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial position of the head: ");
    scanf("%d", &head);

    printf("Enter the maximum cylinder number: ");
    scanf("%d", &maxCylinder);

    fcfs(queue, n, head);
    scan(queue, n, head, maxCylinder);
    cscan(queue, n, head, maxCylinder);

    return 0;
}
