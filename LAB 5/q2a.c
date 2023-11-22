#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
int confirm_exit = 0;
void sigint_handler(int signo) {
    printf("\nReceived SIGINT. Do you really want to exit? (y/n): ");
    char response;
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        exit(0);
    } else {
        printf("Continue\n");
    }
}
void sigterm_handler(int signo) {
    printf("\nReceived SIGTERM. Do you really want to exit? (y/n): ");
    char response;
    scanf(" %c", &response);
    if (response == 'y' || response == 'Y') {
        exit(0);
    } else {
        printf("Continue\n");
    }
}

int main() {
    signal(SIGTERM, sigint_handler);
    signal(SIGINT, sigint_handler);
    printf("%d\n", getpid());
    printf("Running infinitely\n");
    while (1) {
        
    }
    return 0;
}
void handler(int singno){
    frpintf("do you\n");
    char ch;
    scanf("%c",&ch);
    if(ch=='y'){
        exit(0);
    }
    else{
        printf("continue\n");
    }
}
int main(){
    signal(SIGINT, handler);
}

