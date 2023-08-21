#include <stdio.h>

#define NUM_FRAMES 3  // Number of frames in physical memory

int isPagePresent(int frame[], int pageNum, int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (frame[i] == pageNum) {
            return 1;
        }
    }
    return 0;
}

int findOldestPage(int pageHistory[], int numFrames, int startIdx) {
    int oldestIdx = startIdx;
    for (int i = startIdx + 1; i < numFrames; i++) {
        if (pageHistory[i] < pageHistory[oldestIdx]) {
            oldestIdx = i;
        }
    }
    return oldestIdx;
}

int main() {
    int numPages, pageFaults = 0;

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pageSequence[numPages]; // Reference string
    int frames[NUM_FRAMES];
    int pageHistory[NUM_FRAMES] = {0};

    printf("Enter the page sequence: ");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pageSequence[i]);
    }

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        int currentPage = pageSequence[i];

        if (!isPagePresent(frames, currentPage, NUM_FRAMES)) {
            int oldestIdx = findOldestPage(pageHistory, NUM_FRAMES, 0);
            frames[oldestIdx] = currentPage;
            pageHistory[oldestIdx] = i;
            pageFaults++;
        } else {
            for (int j = 0; j < NUM_FRAMES; j++) {
                if (frames[j] == currentPage) {
                    pageHistory[j] = i;
                    break;
                }
            }
        }

        printf("Page %d -> Frames: ", currentPage);
        for (int j = 0; j < NUM_FRAMES; j++) {
            if (frames[j] != -1) {
                printf("%d ", frames[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
