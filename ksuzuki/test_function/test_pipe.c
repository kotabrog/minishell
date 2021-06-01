#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2];
	int temp;
	// printf("hello\n");
	write(1, "write\n", 6);
	// abort();
	// sleep(5);
	pipe(fd);
	printf("%d, %d\n", fd[0], fd[1]);
	temp = dup(1);
	dup2(fd[0], 1);
	printf("%d, %d\n", fd[0], fd[1]);
	dup2(temp, 1);
	printf("%d, %d\n", fd[0], fd[1]);
	printf("temp: %d\n", temp);
	close(fd[0]);
	close(fd[1]);
	printf("%d, %d\n", fd[0], fd[1]);
	// if (close(fd[0]))
	// 	return (0);
	// write(1, "ll\n", 3);
	// if (close(fd[0]))
	// 	return (0);
	// write(1, "no\n", 3);
	// if (close(fd[1]))
	// 	return (0);
	// close(1);
	write(1, "ok\n", 3);
}
