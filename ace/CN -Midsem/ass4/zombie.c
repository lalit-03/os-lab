#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
 
    int pid = fork();

    if (pid == 0) {
        printf("Child: My process ID is: %d\n", getpid());
        printf("Child: The parent process ID is: %d\n", getppid());

        // Wait for user input before exiting
        printf("Child: Press any character key to exit.\n");
        // ps statements after get char will give S+
        getchar();
	// ps statements after get char will give Z+
        sleep(1);//sleep to get time for ps statements
        exit(0);
    } else {
        printf("Parent: My process ID is: %d\n", getpid());
        printf("Parent: The child process ID is: %d\n", pid);

        // Sleep for 1 minute
        sleep(60);

        wait(NULL);
        printf("Parent: Child process has exited.\n");
    }

    return 0;
}
//ps -o pid,stat --pid <child’s PID>.