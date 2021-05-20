/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:54:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:27:35 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_test(t_status *status, char **command)
{
	int i;

	i = 0;
	printf("%ld\n", status->env->len);
	dict_set(status->env, command[0], command[1]);
	printf("%ld\n", status->env->len);
	while (i < status->env->len)
	{
		printf("%d: %s: %s\n", i, status->env->items[i].key,\
				status->env->items[i].value);
		++i;
	}
	printf("command %s, %s\n", command[0], dict_get(status->env, command[0]));
}

int		put_command(char **command)
{
	while (*command)
		printf("%s\n", *command++);
}

pid_t	make_process()
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		process_error(errno, NULL, False);
	return (pid);
}

int		execute_command(char **command, t_status *status)
{
	pid_t	pid;
	int		wait_status;
	pid_t	wait_pid;

	wait_status = 0;
	// env_test(status, command);
	if ((pid = make_process()) < 0)
		return (ERROR);
	if (pid == 0)
	{
		put_command(command);
		exit(EXIT_SUCCESS);
	}
	wait_pid = wait(&wait_status);
	if (wait_pid < 0)
	{
		printf("%d\n", ERROR);
		return (ERROR);
	}
	else
		return (SUCCESS);
}

int		loop_shell(t_status *status)
{
	char **command;

	while (True)
	{
		write(1, "minishell$ ", 11);
		command = read_parse_command(0);
		if (command == NULL)
			continue ;
		execute_command(command, status);
		free_double_pointer(command);
	}
}

int		main()
{
	t_status	*status;

	init_status(&status);
	loop_shell(status);
	free_status(status);
}

// commandのパースは、とりあえずスペース' 'だけ対象にしている。
