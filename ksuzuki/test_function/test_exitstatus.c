#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	get_wait_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (-1);
}

int main()
{
	// exit("a");
	int pid = fork();
	if (pid == 0)
		abort();
	int status;
	pid = wait(&status);
	printf("%d\n", status);
	printf("%d\n", get_wait_status(status));
	// exit(status);
	abort();
}
