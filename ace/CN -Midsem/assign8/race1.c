#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

struct semun {//struct for semaphore
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
//SEN_UNDO -> if process doesnt unlock the semaphore then the system does it automatically 
void semaphore_P(int semid) {//lock
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = -1;//op < 0 means obtain resources
    sem_buf.sem_flg = SEM_UNDO;
    semop(semid, &sem_buf, 1);
}

void semaphore_V(int semid) {//unlock
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = 1;//op > 0 means relaese resources
    sem_buf.sem_flg = SEM_UNDO;
    semop(semid, &sem_buf, 1);
}

int main() {
    key_t key = ftok("shmfile", 65);
    int shmid, *shm_ptr, semid;
    pid_t pid_A, pid_B;

    // Create shared memory segment
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("generation of shared memory failed");
        return 0;
    }

    // Attach shared memory segment
    shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        printf("linking of shared memory segment failed");
        return 0;
    }

    // Initialize shared variable
    *shm_ptr = 0;

    // Create semaphore
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(1);
    }

    // Initialize semaphore value
    struct semun sem_union;
    sem_union.val = 1;
    if (semctl(semid, 0, SETVAL, sem_union.val) == -1) {
        perror("semctl");
        exit(1);
    }

    pid_A = fork();
    if (pid_A == 0) {
        for (int i = 0; i < 100000; i++) {
            semaphore_P(semid);
            (*shm_ptr)++;
            semaphore_V(semid);
            usleep(1);//sleep to have some delay
        }
        exit(0);
    }

    pid_B = fork();
    if (pid_B == 0) {
        for (int i = 0; i < 100000; i++) {
            semaphore_P(semid);
            (*shm_ptr)--;
            semaphore_V(semid);
            usleep(1);
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Final value of X: %d\n", *shm_ptr);

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);

    if (semctl(semid, 0, IPC_RMID, sem_union) == -1) {
        perror("semctl");
        exit(1);
    }

    return 0;
}

