/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 09:50:57 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/22 10:04:09 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	pid_t pid;
	int status;
	int *a = malloc(sizeof(int));

	*a = 1;
	printf("before fork: %d, %p\n", *a, a);
	pid = fork();

	if (-1 == pid)
	{
			err(EXIT_FAILURE, "can not fork");
	}
	else if (0 == pid)
	{
		*a = 0;
		printf("child: %d, %p\n", *a, a);
		exit(EXIT_SUCCESS);
	}
	else
	{
		wait(&status);
		printf("parents: %d, %p\n", *a, a);
	}
	exit (EXIT_SUCCESS);
}

//子プロセスの変更は受け取ることができない（pipeを通して受け取るしかない？）
//子プロセスもheapメモリは共有
