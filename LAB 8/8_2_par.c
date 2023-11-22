#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>

#define SHM_KEY 1234
#define SEM_KEY 5678

void waitSemaphore(int semid);
void signalSemaphore(int semid);

int main() {
    // Create shared memory segment
    int shmid = shmget(SHM_KEY, sizeof(int), IPC_CREAT | 0666);
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

    // Initialize shared variable
    *sharedMemory = 0;

    // Create semaphores
    int semid = semget(SEM_KEY, 1, IPC_CREAT | 0666);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }

    // Initialize semaphore value to 1
    semctl(semid, 0, SETVAL, 1);

    // Fork child process A
    pid_t pidA = fork();
    if (pidA == 0) {
        execlp("./ChildProcessA", "ChildProcessA", NULL);
    } else if (pidA < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Fork child process B
    pid_t pidB = fork();
    if (pidB == 0) {
        execlp("./ChildProcessB", "ChildProcessB", NULL);
    } else if (pidB < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // Wait for both child processes to finish
    waitpid(pidA, NULL, 0);
    waitpid(pidB, NULL, 0);

    // Print the final value of X
    printf("Final value of X: %d\n", *sharedMemory);

    // Detach and remove the shared memory segment
    if (shmdt(sharedMemory) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    // Remove semaphores
    semctl(semid, 0, IPC_RMID);

    return 0;
}

void waitSemaphore(int semid) {
    struct sembuf p_op;
    p_op.sem_num = 0;
    p_op.sem_op = -1;
    p_op.sem_flg = 0;
    if (semop(semid, &p_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}

void signalSemaphore(int semid) {
    struct sembuf v_op;
    v_op.sem_num = 0;
    v_op.sem_op = 1;
    v_op.sem_flg = 0;
    if (semop(semid, &v_op, 1) == -1) {
        perror("semop");
        exit(EXIT_FAILURE);
    }
}
