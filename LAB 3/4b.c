#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char **argv) {
	close(0);
	int fd = open(argv[1], O_RDWR | O_CREAT);
	pid_t pid = fork();
	if(pid<0){
		perror("fork error");
	}
	if (pid == 0){
		char *args[] = {NULL};
		execvp("./mycat", args);
	}
	if(pid>0){
		pid_t child = wait(NULL);
		fprintf(stdout, "The Child has Terminated\n");
	}
	return 0;
}
