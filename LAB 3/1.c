#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main() {
    pid_t pid = fork();  
    if (pid < 0) {
        perror("fork");
    }
    if (pid == 0) {
        printf("Child : My process ID is: %d\n", getpid());
        printf("Child : The parent process ID is: %d\n", getppid());
    } 
    if(pid>0){
        printf("Parent : My process ID is: %d\n", getpid());
        printf("Parent : The child process ID is: %d\n", pid);
    }
    return 0;
}
#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/types.h>
int main(){
    pid_t pid= fork();
    if(pid<0){
        perror("Error in forking the process\n");
    }
    if(pid==0){
        printf("child: my process id is : %d\n",getpid());
        printf("child: my parent process id is : %d\n",getppid());
    }
    if(pid>0){
        wait(NULL);
        execl("./mycat","mycat",NULL);
        perror("Error\n");
        printf("parent: my process id is : %d\n",getpid());
        printf("parent: the child process id is: %d\n",pid);
    }
    return 0;
}
