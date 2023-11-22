#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


//No of the threads we create
#define M 2

long long result = 0;
pthread_mutex_t alpha;


//This function is used 2 times to calculate the left and right sum of n(n+1)/2
void* add(void* argument);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Enter 2 arguments!");
        return 0;
    }

    int N = atoi(argv[1]);

    if (N <= 0) {
        printf("Please provide a positive integer as N.\n");
        return 0;
    }

    pthread_t lines[M];   // no of thread lines
    pthread_mutex_init(&alpha, NULL);

    for (int i = 0; i < M; i++) {
        int* targets = (int*)malloc(2 * sizeof(int));
        targets[0] = i;
        targets[1] = N;
//THE ADD IS USED WHILE CREATE ONLY
        if (pthread_create(&lines[i], NULL, add, targets) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }

    for (int i = 0; i < M; i++) {
        pthread_join(lines[i], NULL);
    }

    pthread_mutex_destroy(&alpha);

    printf("Sum of first %d natural numbers = %lld\n", N, result);

}

void* add(void* argument) {
    int* targets = (int*)argument;
    int thread_id = targets[0];
    int N = targets[1];

    long long partial_sum = 0;
    //Check by thread id whether it is using left or right
    int start = (thread_id == 0) ? 1 : (N / 2) + 1;
    int end = (thread_id == 0) ? (N / 2) : N;

    for (int i = start; i <= end; i++) {
        partial_sum += i;
    }

    pthread_mutex_lock(&alpha);
    result += partial_sum;
    pthread_mutex_unlock(&alpha);

    free(argument); 

    pthread_exit(NULL);

    //EXITING THE FUNCTION
}

