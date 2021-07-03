/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:53:33 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/05 17:43:04 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_fork(t_tree *tree, int pid[2])
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

static int	pipe_recursive(t_status *status, t_tree *tree, int parentfd[2])
{
	int	*pid;
	int	*pipefd;
	int	flag;

	pipefd = tree->command->pipefd;
	pid = tree->command->pid;
	if (pipe(pipefd) == -1)
		return (errno);
	flag = process_fork(tree, pid);
	if (pid[0] == 0)
	{
		multi_close(&pipefd[READ], NULL, &parentfd[READ], &parentfd[WRITE]);
		process_command(status, tree->left, pipefd, TRUE);
	}
	if (pid[1] == 0)
	{
		multi_close(NULL, &pipefd[WRITE], &parentfd[READ], NULL);
		pipefd[WRITE] = parentfd[WRITE];
		process_command(status, tree->right, pipefd, TRUE);
	}
	if (flag == SUCCESS && pid[0] == -1)
		flag = pipe_recursive(status, tree->left, pipefd);
	return (flag);
}

static int	pid_search_close(t_tree *tree, int pid)
{
	if (tree->command->pid[1] == pid)
	{
		tree->command->pid[1] = -1;
		multi_close(&tree->command->pipefd[0], &tree->command->pipefd[1], \
			NULL, NULL);
		return (TRUE);
	}
	while (tree->left->command->flag == PIPE && \
			tree->left->command->pid[1] != pid)
		tree = tree->left;
	multi_close(&tree->command->pipefd[0], \
		&tree->command->pipefd[1], NULL, NULL);
	if (tree->left->command->flag == PIPE)
	{
		multi_close(&tree->left->command->pipefd[0], \
			&tree->left->command->pipefd[1], NULL, NULL);
		tree->left->command->pid[1] = -1;
	}
	else
		tree->left->command->pid[0] = -1;
	return (FALSE);
}

void	all_command_close(t_tree *tree)
{
	if (tree == NULL || tree->command == NULL)
		return ;
	if (tree->command->flag == 0)
	{
		if (tree->command->pid[0] > 0)
			kill(tree->command->pid[0], SIGTERM);
		return ;
	}
	while (tree->left->command->flag == PIPE)
	{
		multi_close(&tree->command->pipefd[0], \
			&tree->command->pipefd[1], NULL, NULL);
		if (tree->command->pid[1] > 0)
			kill(tree->command->pid[1], SIGTERM);
		if (tree->left->command->flag == PIPE)
			tree = tree->left;
		else
			break ;
	}
	if (tree->command->pid[0] != -1)
		kill(tree->command->pid[0], SIGTERM);
}

int	process_pipe(t_status *status, t_tree *tree, int parentfd[2])
{
	int		flag;
	int		wait_status;
	int		pid;

	g_signal->tree = tree;
	flag = pipe_recursive(status, tree, parentfd);
	while (!g_signal->signal_flag)
	{
		pid = wait(&wait_status);
		if (pid == -1)
			break ;
		if (pid_search_close(tree, pid) && !flag)
			flag = wait_conversion(wait_status);
	}
	if (g_signal->signal_flag)
	{
		ft_putchar_fd('\n', 1);
		flag = g_signal->signal_flag + SIGNAL_VALUE;
	}
	return (flag);
}
