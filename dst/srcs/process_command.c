/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:55:23 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/24 10:20:34 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_execute(t_status *status, t_command *com, int fork_flag)
{
	int	pid;
	int	wait_status;

	pid = -1;
	if (!g_signal->signal_flag)
		pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
		exit(error_file(search_execve(com->s, status->env), TRUE, com->s[0]));
	if (fork_flag)
		g_signal->exit_pid = pid;
	pid = waitpid(pid, &wait_status, 0);
	if (!fork_flag && g_signal->signal_flag)
		ft_putchar_fd('\n', 1);
	return (wait_conversion(wait_status));
}

static int	choice_command(t_status *status, t_command *com, int fork_flag)
{
	if (com->s[0] == NULL)
		return (SUCCESS);
	if (ft_strcmp(com->s[0], "exit") == 0)
		return (builtin_exit(status, com, fork_flag));
	if (ft_strcmp(com->s[0], "echo") == 0)
		return (builtin_echo(com));
	if (ft_strcmp(com->s[0], "env") == 0)
		return (do_env(status->env_tab));
	if (ft_strcmp(com->s[0], "export") == 0)
		return (do_export(&(com->s[0]), status->env_tab, status->env_tmp));
	if (ft_strcmp(com->s[0], "unset") == 0)
		return (do_unset(&(com->s[0]), status));
	if (ft_strcmp(com->s[0], "pwd") == 0)
		return (do_pwd());
	if (ft_strcmp(com->s[0], "cd") == 0)
		return (do_cd(&(com->s[0]), status->env_tab));
	return (process_execute(status, com, fork_flag));
}

int	process_command(t_status *status, t_tree *tree, int parent[2], \
	int fork_flag)
{
	int	flag;
	int	fd[3];

	flag = SUCCESS;
	if (fork_flag)
		g_signal->tree = NULL;
	flag = variable_expansion_all(status, tree->command);
	redirect_init(fd, fork_flag);
	if (!flag && parent[READ] != -1 && dup2(parent[READ], READ) == -1)
		flag = errno;
	if (!flag && parent[WRITE] != -1 && dup2(parent[WRITE], WRITE) == -1)
		flag = errno;
	multi_close(&parent[READ], &parent[WRITE], NULL, NULL);
	if (!flag)
		flag = redirect_set(fd, tree->command->file, \
			tree->command->fd, fork_flag);
	if (!flag && !g_signal->signal_flag)
		flag = choice_command(status, tree->command, fork_flag);
	flag = redirect_close(fd, flag, fork_flag);
	if (fork_flag)
		exit(flag);
	else
		return (flag);
}
