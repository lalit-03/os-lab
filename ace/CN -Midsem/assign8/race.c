#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {

    key_t key = ftok("shmfile", 65);
    int shmid, *shm_ptr;
    int pid1, pid2;

//IPC_CREAT -> tells the system to create a new memory segment for the shared memory.
//0666 -> access permission for memory access
    shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);  //creation of shared memory segemnt
    if (shmid == -1) {
        printf("generation of shared memory failed");
        return 0;
    }

    // Attach shared memory segment to the address space of process
    shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (void *)-1) {
        printf("linking of shared memory segment failed");
        return 0;
    }

    // Initialize shared variable
    *shm_ptr = 0;
   
    pid1 = fork();
    if (pid1 == 0) {
        for (int i = 0; i < 100000; i++) {
            (*shm_ptr)++;
            usleep(1);  // Simulate race condition by slowing down process A
        }
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0) {
        for (int i = 0; i < 100000; i++) {
            (*shm_ptr)--;
            usleep(1);  // Simulate race condition by slowing down process B
        }
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    printf("Final value of X: %d\n", *shm_ptr);

    shmdt(shm_ptr); //detach the shared memory segemnet
    shmctl(shmid, IPC_RMID, NULL); //destroy the shared memory segment

    return 0;
}

