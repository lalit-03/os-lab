// ParentProcess.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
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

    // Initialize X to 0
    (*sharedMemory) = 0;

    pid_t pidA, pidB;
    pidA = fork();

    if (pidA == 0) {
        // Child process A
        execlp("./ProcessA", "ProcessA", NULL);
    } else if (pidA > 0) {
        pidB = fork();

        if (pidB == 0) {
            // Child process B
            execlp("./ProcessB", "ProcessB", NULL);
        } else if (pidB > 0) {
            // Parent process
            wait(NULL); // Wait for child A
            wait(NULL); // Wait for child B

            printf("Final value of X: %d\n", *sharedMemory);

            // Detach and remove the shared memory segment
            if (shmdt(sharedMemory) == -1) {
                perror("shmdt");
                exit(1);
            }

            if (shmctl(shmid, IPC_RMID, NULL) == -1) {
                perror("shmctl");
                exit(1);
            }
        } else {
            perror("fork");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}
