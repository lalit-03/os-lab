#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

int main() {
    // Get the existing shared memory segment
    int shmid = shmget(SHM_KEY, sizeof(int), 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to the shared memory
    int *sharedMemory = (int *)shmat(shmid, NULL, 0);
    if (sharedMemory == (int *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Get the existing semaphore
    int semid = semget(SEM_KEY, 1, 0);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    waitSemaphore(semid);

    // Decrement X 100000 times
    for (int i = 0; i < 100000; ++i) {
        (*sharedMemory)--;
        sleep(0); // Simulate race condition by introducing a delay
    }

    signalSemaphore(semid);

    // Detach from the shared memory
    if (shmdt(sharedMemory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    return 0;
}
