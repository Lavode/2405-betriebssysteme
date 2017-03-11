/* gcc -Wall -pthread statistics.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int max;
int min;
float avg;
int len;

/**
 * Basic struct used for communication between main process and his worker
 * threads.
 */
struct WorkerData {
	/* Pointer to first element of integer array which to use as input for
	 * functions. */
	int*   input;
	/* Pointer to where result of minimum function should be stored. */
	int*   min;
	/* Pointer to where result of maximum function should be stored. */
	int*   max;
	/* Pointer to where result of average function should be stored. */
	float* avg;
};

void *average(void *val) {
	/* Cast void pointer back to what we know it to be, for sanity's sake. */
	struct WorkerData *data = (struct WorkerData*) val;

	float sum  = 0;
	for (int i = 0; i < len; i++) {
		sum += data->input[i];
	}
	*(data->avg) = sum / len;

	return NULL;
}

void *minimum(void *val) {
	/* Cast void pointer back to what we know it to be, for sanity's sake. */
	struct WorkerData *data = (struct WorkerData*) val;

	*(data->min) = data->input[0];
	for (int i = 1; i < len; i++) {
		if (data->input[i] < *(data->min)) {
			*(data->min) = data->input[i];
		}
	}

	return NULL;
}

void *maximum(void *val) {
	/* Cast void pointer back to what we know it to be, for sanity's sake. */
	struct WorkerData *data = (struct WorkerData*) val;

	*(data->max) = data->input[0];
	for (int i = 1; i < len; i++) {
		if (data->input[i] > *(data->max)) {
			*(data->max) = data->input[i];
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	// int *array; // use this to store the command line parameters as integers

	/* At most argc - 1 items, if all arguments are valid. */
	int cliArgs[argc - 1];

	pthread_t thread0;
	pthread_t thread1;
	pthread_t thread2;

	if (argc < 3) {
		printf("You have to supply at least 2 integers as arguments!\n");
		return 0;
	}

	int index = 0;
	for (int i = 1; i < argc; i++) {
		char *bin;
		cliArgs[index] = (int)strtol(argv[i], &bin, 10);
		index++;
	}

	len = sizeof(cliArgs) / sizeof(cliArgs[0]);
	printf("Numbers contains %i items\n", len);

	struct WorkerData data;
	data.min = &min;
	data.max = &max;
	data.avg = &avg;
	data.input = &cliArgs[0];

	pthread_create(&thread0, NULL, minimum, &data);
	pthread_create(&thread1, NULL, maximum, &data);
	pthread_create(&thread2, NULL, average, &data);

	pthread_join(thread0, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Average: %f\n" , avg);
	printf("Maximum: %i\n" , max);
	printf("Minimum: %i\n" , min);

	return 0;
}
