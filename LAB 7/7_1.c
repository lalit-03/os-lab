#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void creatPhilosophers(int nthreads);
void* philosopherThread(void * pVoid);  
 
 
int main(int argc, char* argv[]){
    int nthreads;
    if(argc < 2){
        printf("Command line parameter not given\n");
        return 0;
    }     
    nthreads = atoi(argv[1]);
    printf("# of threads = %d\n", nthreads);
    creatPhilosophers(nthreads);
    return 0;
}
                                  
void creatPhilosophers(int nthreads){
    pthread_t pthr[100];
    int id[100];
    int i;
      /* create the threads */
    for(i = 0; i < nthreads; i++){
        id[i] = i;
        pthread_create(&pthr[i], NULL, &philosopherThread, (void*)&id[i]);
    }                                                            
    /* wait for threads to complete */    
    for(i = 0; i < nthreads; i++){
        pthread_join(pthr[i], NULL);    
    }
/* All threads have joined (completed) */                                                                             
    printf("%d threads have been completed/joined successfully!\n", nthreads);
}
                                                                                     
                                                                                     
void* philosopherThread(void *pVoid){
    int id = *((int*)pVoid);
    printf("This is philosopher %d\n",id);
    return NULL;
}