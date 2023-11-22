// ProcessA.c

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234

int main() {
    // Create or get the shared memory segment
    int shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach to the shared memory
    int* sharedMemory = (int*)shmat(shmid, NULL, 0);
    if (sharedMemory == (int*)-1) {
        perror("shmat");
        exit(1);
    }

    // Increment X 100000 times
    for (int i = 0; i < 100000; ++i) {
        (*sharedMemory)++;
        sleep(0);  // Simulate race condition by introducing a delay
    }

    // Detach from the shared memory
    if (shmdt(sharedMemory) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
