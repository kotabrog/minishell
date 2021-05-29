/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 16:39:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/29 22:44:58 by ksuzuki          ###   ########.fr       */
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

int	redirect_set(int fd[3], char **file, int *tofd, int fork_flag)
{
	while (*file)
	{
		tofd++;
		file++;
		fork_flag = fd[0];
		fork_flag++;
	}
	return (SUCCESS);
}

int	redirect_close(int fd[3], int flag)
{
	int	i;
	int	temp;

	temp = 0;
	i = 0;
	while (i < 3)
	{
		if (fd[i] != -1 && fd[i] != i)
			if (dup2(fd[i], i) == -1)
				temp = errno;
		if (fd[i] != -1)
			ft_close(&fd[i]);
		++i;
	}
	if (temp)
		return (temp);
	return (flag);
}
