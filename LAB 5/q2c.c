#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
void sigchld_handler(int signo) {
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0){
        if (WIFEXITED(status)) {
            printf("process with PID %d exited\n", pid);
        }
    }
}
int main() {
    signal(SIGCHLD, sigchld_handler);
    pid_t child_pid, grandchild_pid;
    child_pid = fork();
    if (child_pid < 0) {
        perror("Fork failed");
        exit(1);
    }
    if (child_pid == 0) {
        grandchild_pid = fork();
        if (grandchild_pid < 0) {
            perror("Fork failed");
            exit(1);
        }
        if (grandchild_pid == 0) {
        sleep(3);
            printf("Grandchild process (PID %d) is terminating. Parent - %d\n", getpid(), getppid());
            exit(0);
        } 
        else{
            sleep(1); 
            printf("Child process (PID %d) is terminating.Parent - %d\n", getpid(), getppid());
            exit(0);
        }
    } else {
        printf("Parent process (PID %d) is waiting...\n", getpid());
        sleep(5); 
        printf("Parent process (PID %d) is terminating.\n", getpid());
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
typedef struct {
    int first;
    int second;
} pair;
int n;
int final_sum = 0;
pthread_mutex_t final_sum_mutex = PTHREAD_MUTEX_INITIALIZER;
void *add(void *arg) {
    pair *id = (pair *)arg;
    int start = id->first;
    int end = id->second;
    int temp_sum = 0;
    for (int i = start; i <= end; i++) {
        temp_sum += i;
    }
    pthread_mutex_lock(&final_sum_mutex);
    final_sum += temp_sum;
    pthread_mutex_unlock(&final_sum_mutex);
    free(id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Incorrect Input");
        return 1;
    }
    n = atoi(argv[1]);
    pthread_t t1, t2;
    pair *pre= (pair *)malloc(sizeof(pair));
    pre->first = 1;
    pre->second = n / 2;
    pair *post = (pair *)malloc(sizeof(pair));
    post->first = (n / 2) + 1;
    post->second = n;
    pthread_create(&t1, NULL, sum, pre);
    pthread_create(&t2, NULL, sum, post);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&final_sum_mutex);
    printf("Sum of the first %d natural numbers: %d\n", n, final_sum);

    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct{
    int first;
    int second;
}pair;
int n;
int final_sum;
pthread_mutex_t final_sum_mutex= PTHREAD_MUTEX_INITIALIZER;
void *add(void * arg){
    pair *id = (pair *)(arg);
    id->first= start;
    id->second=end;
    int temp=0;
    for(int i=start; i<=end; i++){
        temp+=i;
    }
    pthread_mutex_lock(&final_sum_mutex);
    final_sum+=temp;
    pthread_mutex_unlock(&final_sum_mutex);
    free(id);
    pthread_exit(NULL);
}
int main(int argc, char* argv){
    if(argc!=2){
        perror("incorrect input");
        return 1;
    }
    n= atoi(argv[1]);
    pthread_t t1,t2;
    pair* pre= (pair *)(malloc(sizeof(pair)));
    pair* pre= (pair *)(malloc(sizeof(pair)));
    pre->first=1;
    pre->second=n/2;
    post->first=n/2+1;
    post->second=n;
    pthread_create(&t1, NULL, add, pre);
    pthread_create(&t2, NULL, add, post);
    pthread_join(t1, null);
    pthread_join(t2,null);
    pthread_mutex_destroy(final_sum_mutex);
}
