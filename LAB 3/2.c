#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork(); 
    if (pid < 0) {
        perror("fork");
    }
    if (pid == 0) {
        printf("Child : My process ID is: %d\n", getpid());
        printf("Child : The parent process ID is: %d\n", getppid());
    }
    if(pid >0){
        wait(NULL);
        printf("Parent : My process ID is: %d\n", getpid());
        printf("Parent : The child process ID is: %d\n", pid);
        printf("Parent : The child with process ID %d has terminated.\n", pid);
    }
    return 0;
}

