/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:45:34 by tkano             #+#    #+#             */
/*   Updated: 2021/06/27 22:18:01 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_unset_tab(t_status *st, t_env *src)
{
	if (src->next)
		st->env_tab = src->next;
	else
		st->env_tab = st->env_tab;
	free_node(st->env_tab, src);
}

void	first_unset_tmp(t_status *st, t_env *src)
{
	if (src->next)
		st->env_tmp = src->next;
	else
		st->env_tmp = st->env_tmp;
	free_node(st->env_tmp, src);
}

int	check_unset(const char *command)
{
	if (check_ex_arg(command) < 0)
		return (IN_VALID_ENV);
	if (ft_ischr(command, '=') == TRUE)
		return (IN_VALID_ENV);
	return (SUCCESS);
}

int	ret_unset(char **command)
{
	int	i;

	i = 1;
	while (command[i])
	{
		if (check_unset(command[i]) != SUCCESS)
			return (error_put2(IN_VALID_ENV, "unset", command[i]));
		i++;
	}
	return (SUCCESS);
}

int	do_unset(char **command, t_status *st)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	new = st->env_tab;
	tmp = st->env_tmp;
	if (!(command[1]))
		return (SUCCESS);
	i = 1;
	while (command[i])
	{
		if (check_unset(command[i]) == SUCCESS)
		{
			if (ft_strncmp(command[i], new->value, env_size(new->value)) == 0)
				first_unset_tab(st, new);
			if (ft_strncmp(command[i], tmp->value, env_size(tmp->value)) == 0)
				first_unset_tmp(st, tmp);
			loop_unset(command[i], st->env_tab, new);
			loop_unset(command[i], st->env_tmp, tmp);
		}
		i++;
	}
	return (ret_unset(command));
}
