#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_ITERATIONS 1000000

int count=10;

pthread_mutex_t mutex; // mutex object

// Critical section function
void critical_section(int process) {
    if (process == 0) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count--; // Process 0 decreases count
    } 
    else if (process == 1) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count++; // Process 1 increases count
    } 
    else if (process == 2) {
        for (int i = 0; i < NUM_ITERATIONS; i++)
            count += 2; // Process 2 adds 2 (you can change logic)
    }
}
// Peterson's Algorithm function for process 0
void *process0(void *arg) {
           
        pthread_mutex_lock(&mutex); // lock
        // mutex lock find kr ky next line ma chla jy ga .nhi mily ga tu mangta rhy ga lock
        //lock p1 or p0 ma sy kisi ik ko mily ga .
        // jis ko lock mily ga wo run hujay ga proocess or dosra wait ma phas jay ga
        // jab kam hujay ga process ka tu wo unlock hujay ga or dosra process ko lock mily ga or wo run hujay ga

        // Critical section
        critical_section(0);
        // Exit section
        
        pthread_mutex_unlock(&mutex); // unlock
    
    return NULL;
}

// Peterson's Algorithm function for process 1
void *process1(void *arg) {
    
        
        pthread_mutex_lock(&mutex); // lock

        // Critical section
        critical_section(1);
        // Exit section

        pthread_mutex_unlock(&mutex); // unlock
       
    
    return NULL;
}
void *process2(void *arg) {
    
        
        pthread_mutex_lock(&mutex); // lock

        // Critical section
        critical_section(2);
        // Exit section

        pthread_mutex_unlock(&mutex); // unlock
       
    
    return NULL;
}

int main() {
    pthread_t thread0, thread1, thread2, thread3, thread4 , thread5;

    pthread_mutex_init(&mutex,NULL); // initialize mutex

    // Create threads
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);
    pthread_create(&thread2, NULL, process0, NULL);
    pthread_create(&thread3, NULL, process1, NULL);
    pthread_create(&thread4, NULL, process2, NULL);
    pthread_create(&thread5, NULL, process2, NULL);

    // Wait for threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);
    pthread_join(thread5, NULL);
    
    pthread_mutex_destroy(&mutex); // destroy mutex

    printf("Final count: %d\n", count);

    return 0;
}