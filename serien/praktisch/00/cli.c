#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// 3, as first argument is program name
	if (argc != 3) {
		printf("Usage: ./cli <arg1> <arg2>");
		exit(2);
	}

	char *bin;
	// We'll just discard the rest. Could check if it isn't empty and raise
	// an error if so.
	int arg1 = strtol(argv[1], bin, 10);
	int arg2 = strtol(argv[2], bin, 10);

	printf("%i * %i = %i\n", arg1, arg2, arg1 * arg2);
}
