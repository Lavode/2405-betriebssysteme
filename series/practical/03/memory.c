/* gcc -Wall ./memory.c -o memory */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* 
 * System used: Arch Linux, 64bit, x86
 * Linux loisoh 4.10.6-1-ARCH #1 SMP PREEMPT Mon Mar 27 08:28:22 CEST 2017 x86_64 GNU/Linux
 */

#define PAGE_SIZE 4096;

/*
 * Calculate virtual page of virtual address.
 */
int calculate_page (int32_t address) {
	return address / PAGE_SIZE;
}

/*
 * Calculate page offset of virtual address.
 */
int calculate_offset (int32_t address) {
	return address % PAGE_SIZE;
}

int main(int argc, char *argv[])
{
	long long_input;
	int32_t address;
	int offset, page;

	if (argc != 2) {
		printf("You must provide a parameter as input!\n");
		return -1;
	} else {
		long_input = atol(argv[1]);
		/* sizeof returns size in bytes, hence *8. */
		long supremum = pow(2 , 8 * sizeof(int32_t));
		if (long_input < 0 || long_input >= supremum) {
			printf("You must enter a valid 32bit address as parameter!\n");
			return -1;
		} else {
			address = (int32_t) long_input;
		}
	}

	page = calculate_page(address);
	offset = calculate_offset(address);

	printf("The address %i contains:\n", address);
	printf("Page number: %i\n", page);
	printf("Offset: %i\n", offset);

	return 0;
}
