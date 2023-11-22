#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<math.h>

pthread_mutex_t mutex;
int MAX_NUMBER = 100000;
int fin_arr[2000];
int alpha = 100;

void* cuberoot(void* arg){

    pthread_mutex_lock(&mutex);
    
    long long n = *((long long*)arg);
    
    fin_arr[n] = n*n;
    alpha--;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {

  pthread_mutex_init(&mutex, NULL);
  pthread_t ti[5000];
  int num[1000];
  for(int i=0;i<100;i++)
  {
      num[i]=i;
      if (pthread_create(&ti[i], NULL, cuberoot, &num[i]) != 0) {
        perror("Thread creation failed");
        return 1;
    }
     if (pthread_join(ti[i], NULL) != 0) {
        perror("Thread join failed");
        return 1;
    }

  
  }

    pthread_mutex_destroy(&mutex); 

    while(alpha!=0);
    printf("Arr Becomes \n");
    
    
    for(int i=0;i<=1000;i++)
    printf("%d ",fin_arr[i]);
    printf("\n");

    return 0;
}
