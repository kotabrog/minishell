/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utility1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 16:12:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/29 22:16:34 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_init(t_command **command, int flag)
{
	if (ft_malloc(command, sizeof(t_command), 1))
		return (ERROR);
	(*command)->s = NULL;
	(*command)->file = NULL;
	(*command)->flag = flag;
	(*command)->fd = NULL;
	(*command)->pipefd[0] = -1;
	(*command)->pipefd[1] = -1;
	(*command)->pid[0] = -1;
	(*command)->pid[1] = -1;
	return (SUCCESS);
}

int	command_free(t_command **command)
{
	if (command == NULL || *command == NULL)
		return (SUCCESS);
	if ((*command)->s)
		ft_free_double_char(&((*command)->s));
	if ((*command)->file)
		ft_free_double_char(&((*command)->file));
	free((*command)->fd);
	free(*command);
	*command = NULL;
	return (SUCCESS);
}

int	command_dup(t_command *command)
{
	char	**temp;

	temp = ft_strdup_ex(command->s);
	if (temp == NULL)
		return (ERROR);
	free(command->s);
	command->s = temp;
	temp = ft_strdup_ex(command->file);
	if (temp == NULL)
	{
		ft_free_double_char(&(command->s));
		return (ERROR);
	}
	free(command->file);
	command->file = temp;
	return (SUCCESS);
}
