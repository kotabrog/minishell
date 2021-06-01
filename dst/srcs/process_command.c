/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:55:23 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/30 18:29:52 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_execute(t_status *status, t_command *com)
{
	int	pid;
	int	wait_status;

	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
	{
		execve(com->s[0], com->s, status->env);
		exit(errno);
	}
	pid = wait(&wait_status);
	if (WIFEXITED(wait_status) && WEXITSTATUS(wait_status) == ENOENT)
	{
		wait_status = ERROR_NOT_FOUND;
		error_put(wait_status, com->s[0]);
	}
	return (wait_status);
}

static int	choice_command(t_status *status, t_command *com)
{
	if (com->s[0] == NULL)
		return (SUCCESS);
	return (process_execute(status, com));
}

int	process_command(t_status *status, t_tree *tree, int parent[2], \
	int fork_flag)
{
	int	flag;
	int	fd[3];

	flag = SUCCESS;
	redirect_init(fd, fork_flag);
	if (parent[READ] != -1 && dup2(parent[READ], READ) == -1)
		flag = errno;
	if (!flag && parent[WRITE] != -1 && dup2(parent[WRITE], WRITE) == -1)
		flag = errno;
	multi_close(&parent[READ], &parent[WRITE], NULL, NULL);
	if (!flag)
		flag = redirect_set(fd, tree->command->file, \
			tree->command->fd, fork_flag);
	if (!flag)
		flag = choice_command(status, tree->command);
	flag = redirect_close(fd, flag, fork_flag);
	if (fork_flag)
		exit(flag);
	else
		return (flag);
}
