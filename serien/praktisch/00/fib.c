/* gcc -Wall -O2 fib.c */

#include <stdio.h>
#include <stdint.h>

int fib(int a) {
	if (a == 1 || a == 2) {
		return 1;
	} else {
		return fib(a - 1) + fib(a - 2);
	}
	return a;
}

int main(void) {
	printf("%i", fib(10));

	return 0;
}
