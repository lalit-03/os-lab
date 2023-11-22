#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<signal.h>

void signal_handler(int signum)
{
	printf("Kill process initiated by signal %d \n", signum);
	printf("Please confirm if you want to kill the process, press 1 \n");
	int input;
	scanf("%d",&input);
	if( input==1) 
	{
	  exit(0);
	}
}


int main(int argc, char* argv[]) {

  signal(SIGTERM,signal_handler);
   if (argc <= 2) {
        printf("Less no of arguments %d.\n", argc);
        return 1;
    }
  int n = atoi(argv[1]);
  if(argc!=n+3)
  {
  printf("Less no of arguments %d.\n", argc);
  exit(0);
  }
  int arr[n];
  //printf("%d",n);
  
  for(int i=0;i<n;i++)
  {
  arr[i] = atoi(argv[i+2]);
  }
  int x = 2+n;
  int m = atoi(argv[x]);

  
  int flag =0;
 for(int i=0;i<n;i++)
  {
 if(arr[i]==m)
  	{
  	printf("NUmber found on %d", i);
  	flag=1;
  	break;
	}
  }
  if(flag==0)
 {
  int alpha = getpid();
  kill(alpha,SIGTERM);
  }

}
