#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } 
    else if (pid == 0) {
        // Child process executes "date" command
        execlp("date", "date", NULL);

        // If exec fails
        perror("execlp failed");
        return 1;
    } 
    else {
        // Parent process waits for child to complete
        wait(NULL);
        printf("Child finished.\n");
    }

    return 0;
}
