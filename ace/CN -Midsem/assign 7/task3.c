#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h> 

pthread_mutex_t chopStick;
pthread_cond_t cond;
int n;
int nextIndex=0;

void thinking(){
	srand(time(0));
	sleep(rand()%3);
}

void eating(){
	srand(time(0));
	sleep(rand()%3);
}

void pickUpChopsticks(int threadIndex){
	pthread_mutex_lock(&chopStick);
	while(nextIndex!=threadIndex){
		pthread_cond_wait(&cond,&chopStick);
	}
	pthread_cond_broadcast(&cond);
	printf("Philosopher #%d: starts picking up chopsticks\n",threadIndex);
}

void putDownChopsticks(int threadIndex){
	printf("Philosopher #%d: ends eating\n",threadIndex);
	nextIndex++;
	pthread_mutex_unlock(&chopStick);
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
	pthread_t lines[nthreads];
	pthread_mutex_init(&chopStick,NULL);
	pthread_cond_init(&cond, NULL);
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
	pthread_mutex_destroy(&chopStick);	
}

int main(int argc,char **argv[]){
//number of threads/philosphers
n=atoi(argv[1]);
createPhilosophers(n);
return 0;
}
