/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:16:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/27 23:00:09 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_fork(t_tree *tree, int pid[2])
{
	pid[1] = -1;
	if (tree->left->command->flag == PIPE)
		pid[0] = -1;
	else
	{
		pid[0] = fork();
		if (pid[0] == -1)
			return (errno);
	}
	if (pid[0] != 0)
	{
		pid[1] = fork();
		if (pid[1] == -1)
			return (errno);
	}
	return (SUCCESS);
}

int	process_execute(t_status *status, t_command *com)
{
	status->tree = status->tree;
	debug_command(com);
	return (SUCCESS);
}

int	ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
	return (SUCCESS);
}

int	pipe_close(int *fd1, int *fd2, int *fd3, int *fd4)
{
	if (fd1 != NULL && *fd1 != -1)
		ft_close(fd1);
	if (fd2 != NULL && *fd2 != -1)
		ft_close(fd2);
	if (fd3 != NULL && *fd3 != -1)
		ft_close(fd3);
	if (fd4 != NULL && *fd4 != -1)
		ft_close(fd4);
	return (SUCCESS);
}

int	process_command(t_status *status, t_tree *tree, int fd[2], int fork_flag)
{
	int	flag;

	flag = SUCCESS;
	if (fd[READ] != -1 && dup2(fd[READ], READ) == -1)
		flag = errno;
	if (!flag && fd[WRITE] != -1 && dup2(fd[WRITE], WRITE) == -1)
		flag = errno;
	pipe_close(&fd[READ], &fd[WRITE], NULL, NULL);
	if (fork_flag)
		exit(process_execute(status, tree->command));
	else
		return (process_execute(status, tree->command));
}

int	process_pipe(t_status *status, t_tree *tree, int parent_fd[2])
{
	int	pid[2];
	int	pipefd[2];
	int	flag;
	int	wait_status[2];

	if (pipe(pipefd) == -1)
		return (errno);
	flag = process_fork(tree, pid);
	if (pid[0] == 0)
	{
		pipe_close(&pipefd[READ], NULL, &parent_fd[READ], &parent_fd[WRITE]);
		process_command(status, tree->left, pipefd, TRUE);
	}
	if (flag == SUCCESS && pid[0] == -1)
		flag = process_pipe(status, tree->left, pipefd);
	if (pid[1] == 0)
	{
		pipe_close(NULL, &pipefd[WRITE], &parent_fd[READ], NULL);
		pipefd[WRITE] = parent_fd[WRITE];
		process_command(status, tree->right, pipefd, TRUE);
	}
	if (pid[0] != -1)
		waitpid(pid[0], &(wait_status[0]), 0);
	if (flag == SUCCESS)
		waitpid(pid[1], &(wait_status[1]), 0);
	pipe_close(&pipefd[READ], &pipefd[WRITE], NULL, NULL);
	return (flag);
}

int	process_semicolon(t_status *status, t_tree *tree)
{
	int	flag;

	flag = SUCCESS;
	if (tree->left)
		flag = process_tree(status, tree->left);
	if (flag == SUCCESS && tree->right)
		flag = process_tree(status, tree->right);
	return (flag);
}

int	process_tree(t_status *status, t_tree *tree)
{
	int	flag;
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (tree->command->flag == SEMICOLON)
		flag = process_semicolon(status, tree);
	else if (tree->command->flag == PIPE)
		flag = process_pipe(status, tree, fd);
	else
		flag = process_command(status, tree, fd, FALSE);
	return (flag);
}
