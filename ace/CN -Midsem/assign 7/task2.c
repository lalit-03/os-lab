#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h> 

pthread_mutex_t* chopStick=NULL;
int n;

void thinking(){
	srand(time(0));
	sleep(rand()%3+1);
}

void eating(){
	srand(time(0));
	sleep(rand()%3);
}

void pickUpChopsticks(int threadIndex){
	pthread_mutex_lock(&chopStick[threadIndex]);
	pthread_mutex_lock(&chopStick[(threadIndex+1)%n]);
	printf("Philosopher #%d: starts picking up chopsticks\n",threadIndex);
}

void putDownChopsticks(int threadIndex){
	printf("Philosopher #%d: ends eating\n",threadIndex);
	pthread_mutex_unlock(&chopStick[threadIndex]);
	pthread_mutex_unlock(&chopStick[(threadIndex+1)%n]);
}

void philosopherThread(void *argc){
	int *argument=(int*)argc;
	int id=argument[0];
	printf("Philosopher #%d: starts thinking\n",id);
	thinking();
	pickUpChopsticks(id);
	printf("Philosopher #%d: starts eating\n",id);
	eating();
	putDownChopsticks(id);
	pthread_exit(NULL);
}

void createPhilosophers(int nthreads){
	chopStick = calloc(nthreads,sizeof(pthread_mutex_t));
	pthread_t lines[nthreads];
	for(int i=0;i<nthreads;i++){
		pthread_mutex_init(&chopStick[i],NULL);
	}
	for(int i=0;i<nthreads;i++){
		int *target=(int *) malloc(1*sizeof(int));
		target[0]=i;//index
		if(pthread_create(&lines[i],NULL,philosopherThread,target)!=0){
			printf("Error in thread creation");
			return ;
		}
	}

	for(int i=0;i<nthreads;i++){
		pthread_join(lines[i],NULL);
	}
	for(int i=0;i<nthreads;i++){
		pthread_mutex_destroy(&chopStick[i]);
	}	
}

int main(int argc,char **argv[]){
//number of threads/philosphers
n=atoi(argv[1]);
createPhilosophers(n);
return 0;
}
