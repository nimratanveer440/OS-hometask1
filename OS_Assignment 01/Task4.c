#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to calculate factorial
void* factorial(void* arg) {
    int n = *((int*)arg);  // Get number from argument
    long long* result = malloc(sizeof(long long));  // Allocate memory to store result
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;  // factorial = factorial * i
    }

    pthread_exit((void*)result);  // Return result using pointer
}

int main() {
    pthread_t thread;
    int num;
    long long* fact_result;

    printf("Enter a number: ");
    scanf("%d", &num);

    // Create thread and pass the number
    pthread_create(&thread, NULL, factorial, &num);

    // Wait for thread to finish and get result
    pthread_join(thread, (void**)&fact_result);

    // Print the result
    printf("Factorial of %d is: %lld\n", num, *fact_result);

    // Free allocated memory
    free(fact_result);

    printf("Main thread: Work completed.\n");
    return 0;
}
