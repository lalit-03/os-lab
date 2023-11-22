#include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

int main() {
int pid = fork();
//pid=0 for child process and child pid for parent process
if (pid == 0) {
    printf("Child Process\n");
    char *args[]={"./mycat1",NULL};
    execv(args[0],args);
    
}
else {
   printf("This is parent\n");
   wait(NULL);
}

return 0;
}
