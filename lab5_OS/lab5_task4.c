#include <stdio.h>
 #include <pthread.h>
 typedef struct {
 float cgpa;
 char* message;
 } ThreadData;
 void* printData(void* arg) {
 ThreadData* data = (ThreadData*)arg;
 printf("cgps %f is %s\n", data->cgpa, data->message);
 return NULL;
 }
 int main() {
 pthread_t t1, t2;
 ThreadData data1 = {3.2, "My name is Eman"};
 ThreadData data2 = {3, "My name is Nimra"};
 pthread_create(&t1, NULL, printData, &data1);
 pthread_create(&t2, NULL, printData, &data2);
 pthread_join(t1, NULL);
 pthread_join(t2, NULL);
 printf("All threads done.\n");
 return 0;
 }