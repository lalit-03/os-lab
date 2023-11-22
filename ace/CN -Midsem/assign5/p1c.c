#include <sys/types.h>
#include<stdio.h>
 #include <signal.h>
 #include <sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
 
 void signalhandler(int sig_num){
 	int pid,status;
 	pid = wait(&status);
 	printf("Child process with pid %d terminated.\n",pid);
 }

int main()
{
   int pid =fork();
   signal(SIGCHLD,signalhandler);   
   if(pid == 0){
    	printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
    	signal(SIGCHLD,signalhandler);  
   	int gpid=fork();
   	if(gpid == 0){
   		 printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
   		 //sleep(10);
   		 exit(0);
   	}
   	sleep(10);
   	exit(0);
   }
   sleep(30);
  return 0;   
}
