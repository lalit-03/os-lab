
#include <stdio.h>
#include <signal.h>
 

void sigintHandler(int sig_num)//signal handler
	if(sig_num == SIGINT){
		printf("\n Recieved SIGINT :\n"); 
	}
	else if(sig_num == SIGTERM){
		printf("\n Recieved SIGTERM :\n");
	}
	//asking for the confirmation
    printf("\n Are you sure you want to exit? type y to exit and n to resume \n");
    char c;
    scanf("%c",&c);
    if(c=='y'){//if y exit from the process
    	exit(0);
    }
}
 
int main ()
{
    signal(SIGINT, sigintHandler);
    while(1){}//infinte loop to have ctrl+c and SIGTERM 
    return 0;
}
