#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

int a;

void handler(int signum)
{
	write(1, "\b\b", 2);
	a = signum;
}

static void	input_handler(int signum)
{
	char	eof[1];

	// int fd = dup(0);
	// close(0);
	// dup2(fd, 0);
	write(0, "\b\b  \n", 5);
	// eof[0] = '\n';
	// write(0, eof, 1);
	a = signum;
}

int main()
{
	a = 0;
	int pid;
	int status;
	int n;
	char buf[1000];

	if (signal(SIGQUIT, input_handler) == SIG_ERR)
		return (errno);

	if (signal(SIGINT, input_handler) == SIG_ERR)
		return (errno);

	printf("start\n");
	printf("%d\n", -5 % 3);

		// while (!a);
	// pid = fork();
	// if (pid == -1)
	// 	return (errno);
	// if (pid == 0)
	// {
	// 	while (!a);
	// 	exit(a);
	// }
	// pid = wait(&status);
	sleep(3);
	n = read(0, buf, 100);
	// dup2(a, 0);
	// n = read(0, buf, 2);
	if (n > 0)
	{
		// if (a)
		// 	write(1, "ok\n", 3);
		buf[n] = 0;
		printf("%d, %s\n", n, buf);
	}
	printf("end\n");
	// n = read(0, buf, 1);
	// printf("end\n");
	// printf("%d\n", a);
	// printf("%d\n", status);
	// if (WIFEXITED(status))
	// 	printf("exit: %d\n", WEXITSTATUS(status));
	// if (WIFSIGNALED(status))
	// 	printf("signal: %d\n", WTERMSIG(status));

	return (0);
}
