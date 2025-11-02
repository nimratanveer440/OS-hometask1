#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        // Child process: create a new session and execute 'top'
        if (setsid() == -1) {
            perror("setsid failed");
            exit(1);
        }

        execl("/usr/bin/top", "top", NULL);

        // If execl fails, this line will execute
        perror("execl failed");
        exit(1);
    } 
    else {
        // Parent process
        printf("Child PID: %d\n", pid);
    }

    return 0;
}
