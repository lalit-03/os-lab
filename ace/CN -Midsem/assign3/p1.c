#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
int pid = fork();
//pid=0 for child process and child pid for parent process
if (pid == 0) {
    printf("Child: My Process ID is %d \n",getpid());
    printf("Child: My parent process ID is %d\n",getppid());
}
else {
   printf("Parent: My Process ID is %d\n",getpid());
   printf("Parent: My child process ID is %d.\n",pid);
}

return 0;
}
