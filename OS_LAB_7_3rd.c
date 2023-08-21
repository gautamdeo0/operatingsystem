#include <stdio.h>
#include <stdbool.h>

int findPageIndex(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1;
}

int findOptimalPage(int pages[], int n, int frames[], int frameSize, int startIdx) {
    int idx = -1;
    int farthest = startIdx;

    for (int i = 0; i < frameSize; i++) {
        int j;
        for (j = startIdx; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    idx = i;
                }
                break;
            }
        }
        if (j == n) {
            return i;
        }
    }

    if (idx == -1) {
        return 0;
    }

    return idx;
}

int main() {
    int n, frameSize;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the size of the frame: ");
    scanf("%d", &frameSize);

    int frames[frameSize];
    int frameCount = 0;

    int fifoFaults = 0;
    printf("\nFIFO:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool pageFault = true;

        for (int j = 0; j < frameCount; j++) {
            if (frames[j] == page) {
                pageFault = false;
                break;
            }
        }

        if (pageFault) {
            fifoFaults++;
            if (frameCount < frameSize) {
                frames[frameCount] = page;
                frameCount++;
            } else {
                for (int j = 0; j < frameSize - 1; j++) {
                    frames[j] = frames[j + 1];
                }
                frames[frameSize - 1] = page;
            }
        }

        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Number of page faults (FIFO): %d\n", fifoFaults);

    int lruFaults = 0;
    printf("\nLRU:\n");
    int recent[frameSize];
    int recentCount = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageIndex = findPageIndex(page, frames, frameSize);

        if (pageIndex == -1) {
            lruFaults++;
            if (recentCount < frameSize) {
                frames[recentCount] = page;
                recent[recentCount] = i;
                recentCount++;
            } else {
                int lruIdx = 0;
                for (int j = 1; j < recentCount; j++) {
                    if (recent[j] < recent[lruIdx]) {
                        lruIdx = j;
                    }
                }
                frames[lruIdx] = page;
                recent[lruIdx] = i;
            }
        } else {
            recent[pageIndex] = i;
        }

        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Number of page faults (LRU): %d\n", lruFaults);

    int optimalFaults = 0;
    printf("\nOptimal:\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int pageIndex = findPageIndex(page, frames, frameSize);

        if (pageIndex == -1) {
            optimalFaults++;
            if (frameCount < frameSize) {
                frames[frameCount] = page;
                frameCount++;
            } else {
                int optimalIdx = findOptimalPage(pages, n, frames, frameSize, i + 1);
                frames[optimalIdx] = page;
            }
        }

        for (int j = 0; j < frameCount; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }
    printf("Number of page faults (Optimal): %d\n", optimalFaults);

    return 0;
}
