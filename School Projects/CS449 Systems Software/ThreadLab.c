#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_t t1, t2;
void *threadFuncOne(void *arg);
void *threadFuncTwo(void *arg);

void *threadFuncOne(void *arg) {
	while (1) {
		printf("Hello from thread 1 - A\n");
		pthread_yield();
		printf("Hello from thread 1 - B\n");
	}
}

void *threadFuncTwo(void *arg) {
	while (1) {
		printf("Hello from thread 2 - A\n");
		pthread_yield();
		printf("Hello from thread 2 - B\n");
	}
}

int main(void) {

	pthread_create(&t1, NULL, threadFuncOne, NULL);
	pthread_create(&t2, NULL , threadFuncTwo, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;

}
