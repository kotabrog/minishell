/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heardoc_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 23:44:16 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/14 00:59:14 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heardoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_done = 1;
		ft_putstr_fd("\n", 0);
		g_signal->signal_flag = signum;
	}
}

int	heardoc_redirect(char *file)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (ERROR);
	if (dup2(fd[READ], READ))
	{
		close(fd[WRITE]);
		close(fd[READ]);
		return (ERROR);
	}
	ft_putstr_fd(file, fd[WRITE]);
	close(fd[WRITE]);
	return (SUCCESS);
}
