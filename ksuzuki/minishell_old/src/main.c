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

int		execute_command(char **command)
{
	pid_t	pid;
	int		status;
	pid_t	wait_pid;

	status = 0;
	if ((pid = make_process()) < 0)
		return (ERROR);
	if (pid == 0)
	{
		put_command(command);
		exit(EXIT_SUCCESS);
	}
	wait_pid = wait(&status);
	if (wait_pid < 0)
		return (ERROR);
	else
		return (SUCCESS);
}

int		loop_shell()
{
	char **command;

	while (True)
	{
		write(1, "minishell$ ", 11);
		command = read_parse_command(0);
		if (command == NULL)
			continue ;
		execute_command(command);
		free_double_pointer(command);
	}
}

int		main()
{
	loop_shell();
}

// commandのパースは、とりあえずスペース' 'だけ対象にしている。
