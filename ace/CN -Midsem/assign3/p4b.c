#include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

int main(int argc, char* file_name[]){

int pid = fork();
//pid=0 for child process and child pid for parent process
if (pid == 0) {
close(0);
 int fptr;
 fptr = fopen(file_name[1], "r");
 dup(fptr);
 close(fptr);
    char *args[]={"./mycat1",NULL};
    execv(args[0],args);
}
else {
   wait(NULL);
   printf("Parent: My child with Process ID %d has terminated\n",pid);
  //fprintf(fptr,"%s\n", "hello world ! I am the parent");
}

return 0;
}
