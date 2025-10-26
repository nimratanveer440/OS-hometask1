
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 5
// Thread function
void* thread_function(void* arg) {
    int thread_num = *((int*)arg);
    pthread_t tid = pthread_self(); // get thread ID
    // Generate random sleep time (1 to 3 seconds)
    int sleep_time = rand() % 3 + 1;
    printf("Thread %d started | Thread ID: %lu | Sleeping for %d seconds...\n",
           thread_num, tid, sleep_time);
    sleep(sleep_time); // sleep for random time
    printf("Thread %d (ID: %lu) has completed its work.\n", thread_num, tid);
    pthread_exit(NULL);
}
int main() {
    pthread_t threads[NUM_THREADS];
    int thread_nums[NUM_THREADS];
    srand(time(NULL)); // seed random number generator
    printf("Creating %d threads...\n\n", NUM_THREADS);
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_nums[i]) != 0) {
            perror("Error creating thread");
            exit(1);
        }
    }
    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("\nAll threads have completed.\n");
    return 0;
}
