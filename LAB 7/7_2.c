#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int nthreads;

pthread_mutex_t chopsticks[100];

void thinking(int philosopherNumber) {
    int sleepTime = (rand() % 500) + 1;
    printf("Philosopher %d: starts thinking\n", philosopherNumber);
    usleep(sleepTime * 1000);
}

void pickUpChopsticks(int philosopherNumber) {
    pthread_mutex_lock(&chopsticks[philosopherNumber]);
    pthread_mutex_lock(&chopsticks[(philosopherNumber + 1) % nthreads]);
    printf("Philosopher %d: picks up chopsticks\n", philosopherNumber);
}

void eating(int philosopherNumber) {
    int sleepTime = (rand() % 500) + 1;
    usleep(sleepTime * 1000);
    printf("Philosopher %d: starts eating\n", philosopherNumber);
    usleep(sleepTime * 1000);
    printf("Philosopher %d: ends eating\n", philosopherNumber);
}

void putDownChopsticks(int philosopherNumber) {
    pthread_mutex_unlock(&chopsticks[philosopherNumber]);
    pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % nthreads]);
    printf("Philosopher %d: puts down chopsticks\n", philosopherNumber);
}

void* philosopherThread(void* pVoid) {
    int philosopherNumber = *((int*)pVoid);
    thinking(philosopherNumber);
    pickUpChopsticks(philosopherNumber);
    eating(philosopherNumber);
    putDownChopsticks(philosopherNumber);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_threads>\n", argv[0]);
        return 1;
    }
    nthreads = atoi(argv[1]);
    pthread_t threads[nthreads];
    int indices[nthreads];
    srand(time(NULL));
    for (int i = 0; i < nthreads; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (int i = 0; i < nthreads; i++) {
        indices[i] = i;
        pthread_create(&threads[i], NULL, philosopherThread, &indices[i]);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < nthreads; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}