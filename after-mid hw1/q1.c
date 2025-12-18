#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buffer[SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
pthread_mutex_t lock;

// Producer
void* producer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < 3; i++) {

        sem_wait(&empty);      // wait if buffer full
        pthread_mutex_lock(&lock);

        buffer[in] = i;
        printf("Producer %d produced %d\n", id, buffer[in]);
        in = (in + 1) % SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&full);       // item added

        sleep(1);
    }
    return NULL;
}

// Consumer
void* consumer(void* arg) {
    int id = *(int*)arg;

    for(int i = 0; i < 3; i++) {

        sem_wait(&full);       // wait if buffer empty
        pthread_mutex_lock(&lock);

        printf("Consumer %d consumed %d\n", id, buffer[out]);
        out = (out + 1) % SIZE;

        pthread_mutex_unlock(&lock);
        sem_post(&empty);      // slot free

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    int id1 = 1, id2 = 1;

    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&lock, NULL);

    pthread_create(&p, NULL, producer, &id1);
    pthread_create(&c, NULL, consumer, &id2);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&lock);

    return 0;
}
