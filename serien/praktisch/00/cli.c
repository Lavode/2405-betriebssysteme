#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// 3, as first argument is program name
	if (argc != 3) {
		printf("Usage: ./cli <arg1> <arg2>");
		exit(2);
	}

	char *ptr;

	int arg1 = strtol(argv[1], ptr, 10);
	int arg2 = strtol(argv[2], ptr, 10);

	printf("%i * %i = %i\n", arg1, arg2, arg1 * arg2);
}
