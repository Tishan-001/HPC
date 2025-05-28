#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork(); //creates a new process that is a copy of the calling process (the parent process)

    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        // Execute different code in the child process
        exit(0); 
    } else {
        // Parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
        wait(&status); // Wait for the child process to terminate
    }

    return 0;
}