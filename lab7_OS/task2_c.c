#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource_semaphore;

// FIRST THREAD FUNCTION
void* thread_function1(void* arg) {
    int thread_id = *(int*)arg;

    printf("Thread %d (F1): Waiting for resource...\n", thread_id);
    sem_wait(&resource_semaphore);

    printf("Thread %d (F1): Acquired resource!\n", thread_id);
    sleep(2);

    printf("Thread %d (F1): Releasing resource...\n", thread_id);
    sem_post(&resource_semaphore);

    return NULL;
}

// SECOND THREAD FUNCTION (same style)
void* thread_function2(void* arg) {
    int thread_id = *(int*)arg;

    printf("Thread %d (F2): Waiting for resource...\n", thread_id);
    sem_wait(&resource_semaphore);

    printf("Thread %d (F2): Acquired resource!\n", thread_id);
    sleep(2);

    printf("Thread %d (F2): Releasing resource...\n", thread_id);
    sem_post(&resource_semaphore);

    return NULL;
}

int main() {
    sem_init(&resource_semaphore, 0, 3);

    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    // FIRST function thread
    pthread_create(&t1, NULL, thread_function1, &id1);

    // SECOND function thread
    pthread_create(&t2, NULL, thread_function2, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&resource_semaphore);

    return 0;
}
