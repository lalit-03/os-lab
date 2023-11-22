#include <windows.h>
#include <stdio.h>

#define MAX_CATALAN_NUMBERS 100

// Structure to hold shared data
typedef struct {
    unsigned long long catalanNumbers[MAX_CATALAN_NUMBERS];
    int count;
} SharedData;

// Function to calculate the nth Catalan number
unsigned long long calculateCatalan(long long n) {
    unsigned long long result = 1;
    for (long long i = 1; i <= n; i++) {
        result = result * (2 * n - i + 1) / i;
    }
    return result / (n + 1);
}

// Function to produce Catalan numbers and store them in shared memory
void produceCatalanNumbers(SharedData* sharedData, long long numberOfCatalanNumbers) {
    // Set the count of Catalan numbers
    sharedData->count = numberOfCatalanNumbers;

    // Calculate and store each Catalan number in the shared structure
    for (long long i = 0; i < numberOfCatalanNumbers; i++) {
        sharedData->catalanNumbers[i] = calculateCatalan(i);
    }
}

// Function to consume and output Catalan numbers from shared memory
void consumeAndOutputCatalanNumbers(SharedData* sharedData) {
    // Output the Catalan numbers
    printf("Catalan Numbers:\n");
    for (long long i = 0; i < sharedData->count; i++) {
        printf("%llu ", sharedData->catalanNumbers[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        printf("Usage: %s <number_of_catalan_numbers>\n", argv[0]);
        return 1;
    }

    // Parse the number of Catalan numbers from the command line argument
    long long numberOfCatalanNumbers = atoll(argv[1]);

    // Create a file mapping object for shared memory
    HANDLE hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SharedData), "SharedMemory");
    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    // Map a view of the file into the address space of the calling process
    SharedData* sharedData = (SharedData*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData));
    if (sharedData == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Produce Catalan numbers and store them in shared memory
    produceCatalanNumbers(sharedData, numberOfCatalanNumbers);

    // Uncomment the following line to simulate a delay or additional processing time by the producer
    // Sleep(5000);

    // Consume and output Catalan numbers from shared memory
    consumeAndOutputCatalanNumbers(sharedData);

    // Clean up resources
    UnmapViewOfFile(sharedData);
    CloseHandle(hMapFile);

    return 0;
}
