#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void print_current_time(void){
long ms; 
struct timespec spec;
clock_gettime(CLOCK_REALTIME, &spec);
ms = spec.tv_nsec / 1.0e6; 
if (ms > 999)
ms = 0;
time_t t = time(NULL);
struct tm tm = *localtime(&t);
printf("Current time: %d-%02d-%02d %02d:%02d:%02d:%03li\n\n",
tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min,
tm.tm_sec, ms);
}

void *print_info(void* arg){
printf("\n\nIt's a child thread with id = %ld\n", pthread_self());
printf("Parent's process id is %d\n", getpid());
print_current_time();
pthread_exit(0);
}

int main(int argc, char* argv[]){
const int threads_count = 2;
pthread_t tid[threads_count];
for(int i = 0; i < threads_count; i++)
pthread_create(tid + i, NULL, print_info, NULL);
for(int i = 0; i < threads_count; i++)
pthread_join(tid[i], NULL);
printf("\n\nIt's a parent process with id = %d\n", getpid());
print_current_time();
return 0;
}
