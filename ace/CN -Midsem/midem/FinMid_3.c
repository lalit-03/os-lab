#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

long long sum = 0; 
long long curr = 0;
int num1 = 1;
pthread_mutex_t mutex;

int MAX_NUMBER = 100000;

void* add(void* arg){

    pthread_mutex_lock(&mutex);

    long long n = *((long long*)arg);
    long long alpha = n / 2;
    
    if(n&1 && num1&1){
        alpha = n/2 + 1;
    }

    for (long long i = 1; i <= alpha; i++) {
        sum += curr + i;
    }
    
    printf("Thread %d ended with sum: %lld \n",num1, sum);    
    pthread_mutex_unlock(&mutex);
    
    curr += alpha;
    num1 += 1;
    
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Less no of arguments %s.\n", argv[0]);
        return 1;
    }

    long long num = atoll(argv[1]); 

    if (num <= 0 || num>MAX_NUMBER) {
        printf("N is not in range!\n");
        return 1;
    }

    pthread_mutex_init(&mutex, NULL);

    pthread_t t1, t2; 

    if (pthread_create(&t1, NULL, add, &num) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    if (pthread_create(&t2, NULL, add, &num) != 0) {
        perror("Thread creation failed");
        return 1;
    }

    if (pthread_join(t1, NULL) != 0) {
        perror("Thread join failed");
        return 1;
    }

    if (pthread_join(t2, NULL) != 0) {
        perror("Thread join failed");
        return 1;
    }

    pthread_mutex_destroy(&mutex); 

    printf("Sum of the first %lld natural numbers: %lld\n", num, sum);

    return 0;
}
