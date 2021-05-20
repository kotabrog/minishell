#include <stdio.h>
#include <stdlib.h>
 
#include <sys/types.h>  // fork
#include <unistd.h>     // fork
 
#include <err.h>
#include <errno.h>
 
int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();

	if (-1 == pid)
	{
			err(EXIT_FAILURE, "can not fork");
	}
	else if (0 == pid)
	{
		// child
		puts("child");
		exit(EXIT_SUCCESS);
	}
	else
	{
		// parent
		puts("parents");
	}

	exit (EXIT_SUCCESS);
}