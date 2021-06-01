/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:04:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/30 18:34:43 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_put_free_return(t_status *status, int flag, char **com, \
	char ***split)
{
	if (com)
		ft_free(com);
	if (split)
		ft_free_double_char(split);
	error_if(flag, flag, NULL, FALSE);
	if (flag)
		set_exit_status(status, flag);
	return (flag);
}

int	read_parse_command(t_status *status, char **s, char **memo, t_tree **tree)
{
	char	*command;
	char	**split_command;
	int		flag;

	if (read_input(&command, memo) == ERROR)
		return (set_put_free_return(status, ERROR, NULL, NULL));
	flag = read_command_split(&split_command, command);
	if (flag)
		return (set_put_free_return(status, flag, &command, NULL));
	flag = read_command2tree(tree, split_command);
	if (flag)
		return (set_put_free_return(status, flag, &command, &split_command));
	if (*tree == NULL)
	{
		set_put_free_return(status, SUCCESS, &command, &split_command);
		return (ERROR);
	}
	*s = command;
	ft_free_double_char(&split_command);
	return (SUCCESS);
}
