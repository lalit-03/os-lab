#include <stdio.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <unistd.h>

int main(int argc, char* file_name[]){

int pid = fork();
 FILE* fptr;
 fptr = fopen(file_name[1], "w");
//pid=0 for child process and child pid for parent process
if (pid == 0) {
    fprintf(fptr,"%s", "hello world ! I am the child\n");
}
else {
   wait(NULL);
  fprintf(fptr,"%s", "hello world ! I am the parent\n");
   printf("Parent: My child with Process ID %d has terminated\n",pid);
}

return 0;
}
