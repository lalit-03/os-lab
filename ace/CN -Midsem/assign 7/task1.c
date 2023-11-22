#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>

void philosopherThread(void *argc){
	int *argument=(int*)argc;
	int id=argument[0];
	printf("This is philosopher %d\n",id);
	pthread_exit(NULL);
}

void createPhilosophers(int nthreads){
	pthread_t lines[nthreads];
	for(int i=0;i<nthreads;i++){
		int *target=(int *) malloc(1*sizeof(int));
		target[0]=i;//index
		if(pthread_create(&lines[i],NULL,philosopherThread,target)!=0){
			printf("Error in thread creation");
			return 0;
		}
	}

	for(int i=0;i<nthreads;i++){
		pthread_join(lines[i],NULL);
	}	
	printf("%d threads have been completed/joined successfully!\n",n);
}

int main(int argc,char *argv[]){
//number of threads/philosphers
int n=atoi(argv[1]);
printf("Atul Assignment 7: # of threads = %d\n",n);
createPhilosophers(n);
return 0;
}
