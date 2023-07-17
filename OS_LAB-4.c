
#include <stdio.h>

#define MAX_TASKS 10

// Task structure
typedef struct {
    int id;
    int period;
    int executionTime;
    int arrivalTime;
} Task;

// Function to schedule tasks using Rate Monotonic Scheduling
void scheduleTasks(Task tasks[], int numTasks) {
    int currentTime = 0;

    printf("Scheduled tasks:\n");

    while (1) {
        int earliestDeadline = -1;
        int selectedTask = -1;

        // Find the earliest deadline task
        for (int i = 0; i < numTasks; i++) {
            if (tasks[i].arrivalTime <= currentTime) {
                if (earliestDeadline == -1 || tasks[i].period < earliestDeadline) {
                    earliestDeadline = tasks[i].period;
                    selectedTask = i;
                }
            }
        }

        // If no task is available, exit the loop
        if (selectedTask == -1)
            break;

        // Execute the selected task
        printf("Task %d at time %d\n", tasks[selectedTask].id, currentTime);

        // Update the current time
        currentTime += tasks[selectedTask].executionTime;

        // Reset the arrival time for the selected task
        tasks[selectedTask].arrivalTime += tasks[selectedTask].period;
    }
}

int main() {
    Task tasks[MAX_TASKS];
    int numTasks;

    printf("Enter the number of tasks (maximum %d): ", MAX_TASKS);
    scanf("%d", &numTasks);

    // Read task details from the user
    for (int i = 0; i < numTasks; i++) {
        printf("Enter details for Task %d:\n", i + 1);

        tasks[i].id = i + 1;

        printf("Period: ");
        scanf("%d", &tasks[i].period);

        printf("Execution time: ");
        scanf("%d", &tasks[i].executionTime);

        printf("Arrival time: ");
        scanf("%d", &tasks[i].arrivalTime);
    }

    // Schedule the tasks
    scheduleTasks(tasks, numTasks);

    return 0;
}
