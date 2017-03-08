/* gcc -Wall -pthread statistics.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int max;
int min;
float avg;
int len;

void *average(void *val) {
	/* TODO */
	return NULL;
}

void *minimum(void *val) {
	/* TODO */
	return NULL;
}

void *maximum(void *val) {
	/* TODO */
	return NULL;
}

int main(int argc, char *argv[])
{
	int *array; // use this to store the command line parameters as integers
	pthread_t thread0;
	pthread_t thread1;
	pthread_t thread2;

	if (argc < 3) {
		printf("You have to supply at least 2 integers as arguments!\n");
		return 0;
	}

	/* TODO */

	printf("Average: %f\n" , avg);
	printf("Maximum: %i\n" , max);
	printf("Minimum: %i\n" , min);

	return 0;
}
