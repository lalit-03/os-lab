#include <sys/types.h>
#include<stdio.h>
 #include <signal.h>
 #include <sys/types.h>
#include<sys/wait.h>
#include <time.h>
#include<stdlib.h>
 
 void signalhandler(int sig_num){
 	
 	if( sig_num == SIGCHLD){
 	while(1){
 		int pid=waitpid(-1,NULL,WNOHANG);
 		
 		if(pid == 0){
 			break;
 		}
 		else if(pid == -1) exit(0);
 		else{
 		  printf("Child process with pid %d terminated.\n",pid);
 		}
	}
    }
 }

int main(int argc, char* argv[])
{
   srand(time(NULL));
    int n=atoi(argv[1]);
    for(int i=0;i<n;i++) // loop will run n times (n=5)
    {
       signal(SIGCHLD , signalhandler);
        if(fork() == 0)
        {
            srand(getpid());
            printf("[son] pid %d from [parent] pid %d\n",getpid(),getppid());
            sleep((rand()%8)+2);
            exit(0);
        } 
    }
    while(1){}
 
   return 0; 
}
