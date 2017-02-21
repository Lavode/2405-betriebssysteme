/* gcc -Wall net.c */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// 3, as first argument is program name
	if (argc != 3) {
		printf("Usage: ./cli <arg1> <arg2>");
		exit(2);
	}

	uint8_t num0;
	uint8_t num1;
	uint8_t sum;

	char *bin;
	// We'll just discard the rest. Could check if it isn't empty and raise
	// an error if so.
	num0 = strtol(argv[1], &bin, 10);
	num1 = strtol(argv[2], &bin, 10);
	sum = num0 + num1;

	printf("%u * %u = %u\n", num0, num1, sum);

	return 0;
}
