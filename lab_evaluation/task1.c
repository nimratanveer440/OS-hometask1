#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Thread function
void* find_sum(void* arg) {
   int n = *(int*)arg;
    int sum = 0;

    for (int i = 1; i <= n; i++)
        sum += i;

    printf("Thread for n=%d -> Sum = %d\n", n, sum);

// Return sum as pointer 
    static int res[4];
    static int index = 0;

    res[index] = sum;
    pthread_exit(&res[index++]);
}

int main() {
    pthread_t threads[4];
    int numbers[4] = {10, 20, 30, 40};
    int* result;
    int total = 0;

    // Create 4 threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, find_sum, &numbers[i]);
    }

    // Wait for threads and results
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], (void**)&result);
        total += *result;
    }

    printf("Total of all sums = %d\n", total);
    return 0;
}
 // first we pass thread n and sum
// then we create 4 threads to calculate sum of first n natural numbers
// return sum as a pointer
// then we passing a pointer of result in main funcction
//then we create 4 threads and wait for threads to execute
// then we find the results 
// now we print the sum of natural numbers
