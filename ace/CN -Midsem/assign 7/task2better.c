/* You will simulate the behaviors of the philosophers in this section, where each
philosopher goes through a cycle of "thinking," "picking up chopsticks," "eating,"
and "putting down chopsticks," as depicted below. To implement these four
matching stages, you must create four distinct functions, each of which has the
following deterministic prototypes:
 void thinking();
 void pickUpChopsticks(int threadIndex);
 void eating();
 void putDownChopsticks(int threadIndex);
The main function of this assignment is pickUpChopsticks(), which mimics the
action of the "pick up chopsticks" stage. Keep in mind that each chopstick is
shared by two nearby philosophers, making them a shared resource. We cannot
let a philosopher to pick up a chopstick that is already in their neighbor's hand 
since it would be a race condition. We may use each chopstick as a mutex lock
to solve this issue. Prior to eating, each philosopher must lock both their right
and left chopsticks.
Only after the acquisitions of both locks (representing the two chopsticks) are
successful, may this philosopher begin to eat. After finishing eating by calling the
function eating(), the philosopher will invoke the function putDownChopsticks()
to release both locks (i.e., chopsticks), and exit the program (that is, for Part 2,
each philosopher only goes through the above cycle once).
Both functions eating() and thinking() can be easily simulated by invoking a sleep
function, such as usleep(), placed between two output statements "Philosopher
#X: starts eating/thinking", and "Philosopher #X: ends eating/thinking",
respectively. However, we should not use a fixed value for every invocation of
the sleep function to emulate the different length of activites of the
philosophers. Instead, we need to utilize a random number between 1 to 500.
You can use function random() to obtain a random value, which could be
initilized using the srandom() function using a proper seed value for the random
value generator. 
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

int NUM_PHILOSOPHERS = 5;
pthread_mutex_t chopsticks[5];




void thinking() {
    int sleep_time = (rand() % 500) + 1;
    usleep(sleep_time * 1000); 
}


void eating() {
    int sleep_time = (rand() % 500) + 1;
    usleep(sleep_time * 1000); 
}


void pickUpChopsticks(int threadIndex) {
    int left = threadIndex;
    int right = (threadIndex + 1) % NUM_PHILOSOPHERS;


    pthread_mutex_lock(&chopsticks[left]);
    pthread_mutex_lock(&chopsticks[right]);

    printf("Philosopher #%d: starts eating\n", threadIndex);
    eating();


    pthread_mutex_unlock(&chopsticks[left]);
    pthread_mutex_unlock(&chopsticks[right]);

    putDownChopsticks(threadIndex);
}


void putDownChopsticks(int threadIndex) {
    printf("Philosopher #%d: ends eating\n", threadIndex);
}

void *philosopherThread(void *pVoid) {
    int *philosopherNumber = (int *)pVoid;

    printf("Philosopher #%d: starts thinking\n", *philosopherNumber);
    thinking();

    pickUpChopsticks(*philosopherNumber);
    
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number of threads>\n", argv[0]);
        return 1;
    }

    int nthreads = atoi(argv[1]);

    if (nthreads <= 0) {
        fprintf(stderr, "Invalid number of threads. Please provide a positive integer.\n");
        return 1;
    }

    printf("Sahil Agrawal: Assignment 7: # of threads = %d\n", nthreads);
    
    NUM_PHILOSOPHERS = nthreads;
    
    srand(time(NULL));

    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopherNumbers[NUM_PHILOSOPHERS];


    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopherNumbers[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopherThread, &philosopherNumbers[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }


    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}

