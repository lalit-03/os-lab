#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("provide filename");
        return 1;
    }
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        char str1[] = "hello world! I am the child\n";
        fputs(str1, file);
    } 
    if(pid>0) {
    	wait(NULL);
        char str2[] = "hello world! I am the parent\n";
        fputs(str2, file);
        printf("Parent: The child process has completed.\n");
    }
    fclose(file);
    return 0;
}

