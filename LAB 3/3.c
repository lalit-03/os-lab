#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    pid_t pid = fork();  
    if(pid<0) {
        perror("fork");
        return 1;
    }
    if(pid == 0) {
        execl("./mycat", "mycat", NULL); // Execute the mycat binary
        perror("execl"); // This line will be reached only if execl fails
        return 1;
    }
    if(pid>0){
        wait(NULL);
        printf("Parent: Child process has completed.\n");
    }
    return 0;
}

