/* gcc -Wall -O2 linked_list.c */
/* valgrind ./a.out */

#include <stdio.h>
#include <stdlib.h>

struct elem {
	int pos;
	struct elem *next;
};

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

static void xfree(void *ptr)
{
	if (ptr == NULL)
		panic("Got Null-Pointer!\n");
	free(ptr);
}

static struct elem *init_list(size_t len)
{
	struct elem* head;
	struct elem* prev;

	int i;

	if (len < 1) {
		panic("Length must be >=1!\n");
	}
	/* Set up first element */
	head = (struct elem*) xmalloc(sizeof(struct elem));
	head->pos = 0;
	head->next = NULL;

	/* We'll keep `head` around to return, but need a floating reference to
	the previous item, too. */
	prev = head;

	/* Starting at 1, as we already have one (namely head). */
	for (i = 1; i < len; i++) {
		struct elem* cur = xmalloc(sizeof(struct elem));
		cur->pos = i;
		cur->next = NULL;
		prev->next = cur;

		prev = cur;
	}

	/* Link last item back to first */
	(*prev).next = head;

	return head;
}

static void clean_list(struct elem *head, size_t len)
{
	struct elem* cur = head;

	int i;

	for (i = 0; i < len; i++) {
		struct elem* next = cur->next;
		xfree(cur);
		cur = next;
	}
}

static void traverse_list(struct elem *head, int times)
{
	int startIndex = head->pos;

	struct elem* cur = head;
	int iteration = 1;

	while (times > 0) {
		printf("[%i] -> %i\n", iteration, cur->pos);
		cur = cur->next;
		if (startIndex == cur->pos) {
			times--;
		}
		iteration++;
	}
}

int main(void)
{
	struct elem *head = NULL;
	size_t len = 10;

	head = init_list(len);
	traverse_list(head, 2);
	clean_list(head, len);

	return 0;
}

