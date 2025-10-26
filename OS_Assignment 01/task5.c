#include <stdio.h>
#include <pthread.h>

typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

int count = 0;
pthread_mutex_t lock;

void* check(void* arg) {
    Student* s = (Student*)arg;

    printf("\nID: %d\nName: %s\nGPA: %.2f\n", s->student_id, s->name, s->gpa);

    if (s->gpa >= 3.5) {
        printf("%s is on Dean’s List!\n", s->name);
        pthread_mutex_lock(&lock);
        count++;
        pthread_mutex_unlock(&lock);
    } else {
        printf("%s is not on Dean’s List.\n", s->name);
    }
    return NULL;
}

int main() {
    pthread_t t[3];
    pthread_mutex_init(&lock, NULL);

    Student s1 = {1, "Ali", 3.8};
    Student s2 = {2, "Sara", 3.2};
    Student s3 = {3, "Bilal", 3.9};

    pthread_create(&t[0], NULL, check, &s1);
    pthread_create(&t[1], NULL, check, &s2);
    pthread_create(&t[2], NULL, check, &s3);

    for (int i = 0; i < 3; i++) pthread_join(t[i], NULL);

    printf("\nTotal Dean’s List Students: %d\n", count);
    pthread_mutex_destroy(&lock);
}
