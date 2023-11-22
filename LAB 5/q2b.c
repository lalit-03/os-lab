#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
void sig_handler(int signum){
if (signum == SIGCHLD) {
pid_t pid;
while(1){
pid=waitpid(-1, NULL, WNOHANG); 
if(pid == 0){
    break;
}
else if(pid == -1){
printf("All Children have exited. \n");
exit(0);
}
else{
printf("Child %d has exited. \n", pid);
}
}
}
}
int main(int argc, const char **argv) {
if(argc<2){
printf("Please provide n \n");
exit(0);
}
int n = atoi(argv[1]);
signal(SIGCHLD, sig_handler);
for (int i=0; i<n; i++) {
pid_t child_pid = fork();
if(child_pid < 0){
printf("Fork Failed\n");
exit(0);
}
else if (child_pid == 0) {
int seed=getpid();
srand(seed);
int x = rand()%10+3;
printf("Child %d is created and will sleep for %d seconds. \n", getpid(), x);
sleep(x);
exit(0);
}
}
while(1);
}
