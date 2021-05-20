#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <sys/types.h>  // fork/wait
#include <unistd.h>     // fork/sleep
#include <sys/wait.h>   // fork/wait

#include <err.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	int status = 0;
	pid_t wait_pid;
	pid_t pid;

	pid = fork ();

	if (-1 == pid)
	{
		err (EXIT_FAILURE, "can not fork");
	}
	else if (0 == pid)
	{
		// child
		puts ("child start");
		sleep (5);      // 子プロセスの長い処理
		puts ("child end");
		exit (EXIT_SUCCESS);
		/* NOTREACHED */
	}

	// parent
	printf ("parents, child is %d\n", pid);
	wait_pid = wait (& status);

	if (wait_pid == -1)
	{
		// wait が失敗した
		err (EXIT_FAILURE, "wait error");
	}

	printf ("child = %d, status=%d\n", wait_pid, status);

	exit (EXIT_SUCCESS);
}