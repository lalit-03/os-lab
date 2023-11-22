#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

    int child_pid = fork();

    if (child_pid == 0) {
        printf("Child: I am a child process and my ID is %d\n", getpid());
        printf("Child: I have been created by my parent process whose id is %d\n", getppid());

        // Sleep for 30 seconds
        sleep(30);

        printf("Child: I am a child process and my id is %d\n", getpid());
        printf("Child: My current parent id is %d\n", getppid());//prints different parent id
    } else {
        printf("Parent: I am the parent process and my ID is %d\n", getpid());
        printf("Parent: I have created a child process whose id is %d\n", child_pid);

        sleep(1); // to give child time to go to sleep
        printf("Parent process has exited\n");
    }

    return 0;
}
