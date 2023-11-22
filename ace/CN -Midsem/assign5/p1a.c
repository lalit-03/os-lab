
#include <stdio.h>
#include <signal.h>
#include<stdlib.h>
 

void sigintHandler(int sig_num)
{
    printf("\n Recieved %d:\n",sig_num); 
    printf("\n Are you sure you want to exit? type y to exit and n to resume \n");
    char c;
    scanf("%c",&c);
    if(c=='y'){
    	exit(0);
    }
}
 
int main ()
{

    signal(SIGINT, sigintHandler);
    signal(SIGTERM, sigintHandler);
    while(1){}
    return 0;
}
