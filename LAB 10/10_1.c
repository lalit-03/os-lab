#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to display an array
void displayArray(long long arr[], long long size);

// Function to simulate the FIFO page replacement algorithm
void simulateFIFO(long long pageSeq[], long long frameCount);

// Function to simulate the LRU page replacement algorithm
void simulateLRU(long long pageSeq[], long long frameCount);

int main() {
    // Array to store the page reference sequence
    long long pageSequence[12];
    srand(time(NULL));
    long long i;

    // Generate a random page reference sequence
    for (i = 0; i < 12; i++) {
        pageSequence[i] = rand() % 10;
    }

    // Display the generated page reference sequence
    printf("Page reference sequence is:\n");
    displayArray(pageSequence, 12);

    long long pageFrames;
    // Get user input for the number of page frames
    printf("Please enter the number of page frames: ");
    scanf("%lld", &pageFrames);
    printf("\n");

    // Initialize an array to represent page frames for FIFO algorithm
    long long framesFIFO[pageFrames];
    for (i = 0; i < pageFrames; i++) {
        framesFIFO[i] = -1;
    }

    long long fifoFaults = 0;
    long long fifoOrder = 0;
    long long turn = 0;

    // Simulate the FIFO page replacement algorithm
    for (; turn < 12; turn++) {
        for (i = 0; i < pageFrames; i++) {
            if (pageSequence[turn] == framesFIFO[i]) {
                break;
            }

            if (i == (pageFrames - 1)) {
                fifoFaults++;
                framesFIFO[fifoOrder] = pageSequence[turn];
                fifoOrder = (fifoOrder + 1) % pageFrames;
            }
        }
    }

    // Display the number of FIFO page faults
    printf("\nFIFO page faults = %lld\n\n", fifoFaults);

    // Initialize an array to represent page frames for LRU algorithm
    long long framesLRU[pageFrames];
    for (i = 0; i < pageFrames; i++) {
        framesLRU[i] = -1;
    }

    long long lruFaults = 0;
    long long turnLRU = 0;
    long long writePosition = 0;
    long long k;

    // Simulate the LRU page replacement algorithm
    for (; turnLRU < 12; turnLRU++) {
        for (i = 0; i < pageFrames; i++) {
            if (pageSequence[turnLRU] == framesLRU[i]) {
                writePosition--;
                for (k = i; k < writePosition; k++) {
                    framesLRU[k] = framesLRU[k + 1];
                }
                framesLRU[writePosition] = pageSequence[turnLRU];
                writePosition++;
                break;
            }

            if (i == (pageFrames - 1)) {
                lruFaults++;
                if (writePosition != pageFrames) {
                    framesLRU[writePosition] = pageSequence[turnLRU];
                    writePosition++;
                } else {
                    for (k = 0; k < (pageFrames - 1); k++) {
                        framesLRU[k] = framesLRU[k + 1];
                    }
                    framesLRU[pageFrames - 1] = pageSequence[turnLRU];
                }
            }
        }
    }

    // Display the number of LRU page faults
    printf("\nLRU page faults = %lld\n", lruFaults);

    return 0;
}

// Function to display an array
void displayArray(long long arr[], long long size) {
    long long t;
    for (t = 0; t < size; t++) {
        printf("%lld ", arr[t]);
    }
    printf("\n");
}
