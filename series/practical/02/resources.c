/* gcc -Wall -pthread ./resources.c -o resources */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_RESOURCES 5


int available_resources = MAX_RESOURCES;
int times = 100000;
sem_t semaphore;


/* decrease available_resources by count resources
 * return 0 if sufficient resources available,
 * otherwise return -1 */
int decrease_count(int count) {
	if (available_resources < count) {
		return -1;
	} else {
		sem_wait(&semaphore);
		available_resources -= count;
		sem_post(&semaphore);
		printf("Locked %i resources, now available: %i\n" , count , available_resources);
		return 0;
	}
}

/* increase available resources by count */
int increase_count(int count) {
	if (count + available_resources > MAX_RESOURCES) {
		return -1;
	} else {
		sem_wait(&semaphore);
		available_resources += count;
		sem_post(&semaphore);
		printf("Freed %i resources, now available: %i\n" , count , available_resources);
		return 0;
	}
}

void *runTimes(void *null) {
	int i = 0 , result;
	while (i < times) {
		result = -1;
		while (result < 0) {result = decrease_count(1);}
		result = -1;
		while (result < 0) {result = increase_count(1);}
		i += 1;
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	pthread_t thread1 , thread0;

	sem_init(&semaphore, 0, 1);

	decrease_count(2);

	pthread_create(&thread0, NULL, runTimes, NULL);
	pthread_create(&thread1, NULL, runTimes, NULL);

	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);

	printf("Currently available resources (should be 3): %i\n" , available_resources);

	sem_destroy(&semaphore);

	return 0;
}
