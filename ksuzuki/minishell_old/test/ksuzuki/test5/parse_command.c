/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:58:48 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:05:28 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_command(t_command *command)
{
	command->command = (char **)malloc(sizeof(char *) * COMMAND_ALLOCATE_SIZE);
	if (command->command == NULL)
		return (ERROR);
	command->symbol = (int *)malloc(sizeof(int) * COMMAND_ALLOCATE_SIZE);
	if (command->symbol == NULL)
	{
		free(command->command);
		return (ERROR);
	}
	command->len = 0;
	command->allocated_len = COMMAND_ALLOCATE_SIZE;
	return (SUCCESS);
}

int		advance_character(char **buf)
{
	char *start;

	start = *buf;
	while (**buf)
	{
		if ()
	}
}

int		parse_command(char *buf, t_command *command)
{
	if (init_command(command))
		return (ENOMEM);
	while (buf)
	{
		if ()
	}





	command = ft_split(buf, ' ');
	if (command == NULL)
		process_error(ENOMEM, NULL, False);
	return (command);
}
