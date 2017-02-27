/* gcc -Wall -O2 substr.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void panic(const char *serror)
{
	printf("%s", serror);
	exit(1);
}

static void *xmalloc(size_t size)
{
	void *ptr;
	if (size == 0)
		panic("Size is 0!\n");
	ptr = malloc(size);
	if (!ptr)
		panic("No mem left!\n");
	return ptr;
}

static char *substring(const char *str, off_t pos, size_t len)
{
	char *out;

	/* pos and len are *unsigned*, so there's no need for checks whether
	 * they're negative. In addition, position 0 is a valid input, so we
	 * only check that length is > 0, as well as that we won't exceed the
	 * string's bounds. */
	if (len == 0) {
		panic("Length must be > 0!");
	} else if (pos + len > strlen(str)) {
		panic("Substring exceeds string length!");
	}

	out = xmalloc(len);
	/* `str` is pointer to *beginning* of char array, so we can add `pos`
	 * to offset it by n bytes. */
	strncpy(out, str + pos, len);
	out[len + 1] = '\0';
	return out;
}

int main(int argc, char **argv)
{
	char *foo = "Nicht\n";
	char *bar = substring(foo, 2, 3);
	printf("%s", bar);
	return 0;
}
