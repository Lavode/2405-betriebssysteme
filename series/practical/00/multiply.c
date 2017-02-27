/* gcc -Wall net.c */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	uint8_t num0;
	uint8_t num1;
	uint8_t product;

	char *bin;

	/* 3, as first argument is program name */
	if (argc != 3) {
		printf("Usage: ./cli <arg1> <arg2>\n");
		exit(2);
	}

	/* We'll just discard the rest. Could check if it isn't empty and raise
	   an error if so. */
	num0 = strtol(argv[1], &bin, 10);
	num1 = strtol(argv[2], &bin, 10);

	/* Unsigned ints, so no need to check for < 0. Those will underflow and
	 * - generally - be caught by the > 9 condition.  What we can't catch
	 * here, however, is the user entering e.g. -250, which will end up
	 * as 6. */
	if (num0 > 9 || num1 > 9) {
		printf("Both arguments must be between 0 and 9\n");
		exit(2);
	}
	product = num0 * num1;

	printf("%u * %u = %u\n", num0, num1, product);

	return 0;
}
