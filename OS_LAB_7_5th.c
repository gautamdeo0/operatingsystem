#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to simulate SSTF algorithm
void sstf(int queue[], int n, int head) {
    printf("SSTF Algorithm:\n");

    int total_movement = 0;
    int visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int min_distance = INT_MAX;
        int min_index = -1;

        for (int j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(head - queue[j]);
                if (distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        visited[min_index] = 1;
        total_movement += min_distance;
        printf("Move to %d | Head position: %d\n", queue[min_index], queue[min_index]);
        head = queue[min_index];
    }

    printf("SSTF Total Head Movement: %d\n\n", total_movement);
}

// Function to simulate LOOK algorithm
void look(int queue[], int n, int head, int direction) {
    printf("LOOK Algorithm:\n");

    int total_movement = 0;

    while (1) {
        int min_distance = INT_MAX;
        int min_index = -1;

        for (int j = 0; j < n; j++) {
            if (queue[j] >= 0) {
                int distance = abs(head - queue[j]);
                if ((queue[j] - head) * direction >= 0 && distance < min_distance) {
                    min_distance = distance;
                    min_index = j;
                }
            }
        }

        if (min_index == -1) {
            direction = -direction;
            continue;
        }

        total_movement += abs(queue[min_index] - head);
        printf("Move to %d | Head position: %d\n", queue[min_index], queue[min_index]);
        head = queue[min_index];
        queue[min_index] = -1; // Mark as visited

        if (min_index == 0) {
            direction = 1;
        }
    }

    printf("LOOK Total Head Movement: %d\n\n", total_movement);
}

// Function to simulate C-LOOK algorithm
void clook(int queue[], int n, int head) {
    printf("C-LOOK Algorithm:\n");

    int total_movement = 0;
    int direction = 1; // 1 for moving towards higher cylinder numbers

    // Find the index of the smallest element greater than the head
    int min_index = -1;
    for (int i = 0; i < n; i++) {
        if (queue[i] >= head) {
            min_index = i;
            break;
        }
    }

    if (min_index == -1) {
        min_index = 0;
    }

    // Move towards higher cylinder numbers
    for (int i = min_index; i < n; i++) {
        total_movement += abs(head - queue[i]);
        printf("Move to %d | Head position: %d\n", queue[i], queue[i]);
        head = queue[i];
    }

    // Move to the beginning of the queue
    for (int i = 0; i < min_index; i++) {
        total_movement += abs(head - queue[i]);
        printf("Move to %d | Head position: %d\n", queue[i], queue[i]);
        head = queue[i];
    }

    printf("C-LOOK Total Head Movement: %d\n\n", total_movement);
}

int main() {
    int n;
    printf("Enter the number of cylinders: ");
    scanf("%d", &n);

    int queue[n];
    printf("Enter the cylinder queue: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    int head;
    printf("Enter the initial head position: ");
    scanf("%d", &head);

    sstf(queue, n, head);
    look(queue, n, head, 1);
    clook(queue, n, head);

    return 0;
}
