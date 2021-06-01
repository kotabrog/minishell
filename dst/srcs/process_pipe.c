/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:53:33 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/29 22:34:38 by ksuzuki          ###   ########.fr       */
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
		multi_close(&tree->command->pipefd[0], &tree->command->pipefd[1], NULL, NULL);
		return (TRUE);
	}
	while (tree->left->command->flag == PIPE && \
			tree->left->command->pid[1] != pid)
		tree = tree->left;
	multi_close(&tree->command->pipefd[0], \
		&tree->command->pipefd[1], NULL, NULL);
	if (tree->left->command->flag == PIPE)
		multi_close(&tree->left->command->pipefd[0], \
			&tree->left->command->pipefd[1], NULL, NULL);
	return (FALSE);
}

int	process_pipe(t_status *status, t_tree *tree, int parentfd[2])
{
	int		flag;
	int		wait_status;
	int		pid;

	flag = pipe_recursive(status, tree, parentfd);
	while (TRUE)
	{
		pid = wait(&wait_status);
		if (pid == -1)
			break ;
		if (pid_search_close(tree, pid) && !flag)
			flag = get_wait_status(wait_status);
	}
	return (flag);
}
