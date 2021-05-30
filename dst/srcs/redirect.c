/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:39:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/30 14:32:45 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_init(int fd[3], int fork_flag)
{
	if (!fork_flag)
	{
		fd[0] = -1;
		fd[1] = -1;
		fd[2] = -1;
	}
	else
	{
		fd[0] = READ;
		fd[1] = WRITE;
		fd[2] = STDERR;
	}
}

static int	redirect_copy(int fd[3])
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	while (i < 3)
	{
		fd[i] = dup(i);
		if (fd[i] == -1)
			flag = errno;
		++i;
	}
	return (flag);
}

static int	set_file(char *file, int tofd)
{
	int	fd;
	int	flag;

	flag = SUCCESS;
	if (tofd == 0)
		fd = open(file, O_RDONLY);
	else if (tofd == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (errno);
	if (dup2(fd, !!tofd) == -1)
		flag = errno;
	close(fd);
	return (flag);
}

int	redirect_set(int fd[3], char **file, int *tofd, int fork_flag)
{
	int	flag;

	flag = 0;
	if (!fork_flag)
		flag = redirect_copy(fd);
	while (flag == SUCCESS && *file)
	{
		flag = set_file(*file, *tofd);
		error_if(flag, flag, *file, FALSE);
		tofd++;
		file++;
	}
	return (flag);
}

int	redirect_close(int fd[3], int flag, int fork_flag)
{
	int	i;
	int	temp;

	temp = 0;
	i = 0;
	if (fork_flag)
	{
		multi_close(&fd[0], &fd[1], &fd[2], NULL);
		return (flag);
	}
	while (i < 3)
	{
		if (fd[i] != -1)
		{
			if (dup2(fd[i], i) == -1)
				temp = errno;
			ft_close(&fd[i]);
		}
		++i;
	}
	if (temp)
		return (temp);
	return (flag);
}
