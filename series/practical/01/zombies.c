/* gcc -Wall -std=gnu99 zombies.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void create_zombie() {
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		/* Child process 
		 * We will execute immediately, which leaves the child process
		 * in a state where its execution is over, but it has not been
		 * reaped by the parent yet - a so-called zombie. */
		exit(0);
	} else if (pid > 0) {
		/* Parent process */
	} else {
		/* Forking failed */
		printf("Forking failed with status %i", pid);
		exit(1);
	}
	return;
}

int main(void)
{
	int wait = 15;

	create_zombie();
	sleep(wait);

	/* We don't care about the return code in this trivial example, so
	 * won't reap the process. Instead, init will do that once we exit. */
	return 0;
}
