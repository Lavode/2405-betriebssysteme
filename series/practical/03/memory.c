/* gcc -Wall ./memory.c -o memory */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* TODO: Insert System Type here
 * System used: e.g. Linux MyDistro 32bit x86
 */

int calculate_page (/* TODO: Insert correct data type */ address) {
	/* TODO: Implement */
}

int calculate_offset (/* TODO: Insert correct data type */ address , int page) {
	/* TODO: Implement */
}

int main(int argc, char *argv[])
{
	long long_input;
	/* TODO: Insert correct data type */ address;
	int offset , page;

	if (argc != 2) {
		printf("You must provide a parameter as input!\n");
		return -1;
	} else {
		long_input = atol(argv[1]);
		long supremum = pow(2 , 8*sizeof(/* TODO: Insert correct data type */));
		if (long_input < 0 || long_input >= supremum) {
			printf("You must enter a valid 32bit address as parameter!\n");
			return -1;
		} else {
			address = (/* TODO: Insert correct data type */) long_input;
		}
	}

	/* TODO: calculate values and generate correct output */

	return 0;
}
