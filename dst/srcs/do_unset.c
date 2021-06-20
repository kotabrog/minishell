/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:45:34 by tkano             #+#    #+#             */
/*   Updated: 2021/06/17 20:38:11 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_status *st, t_env *new)
{
	if (st->env_tab == new && new->next == NULL)
	{
		ft_free(&(st->env_tab->value));;
		st->env_tab->next = NULL;
		return ;
	}
	ft_free(&(new->value));
	ft_free(&new);
}

int		do_unset(char **command, t_status *st)
{
	t_env	*new;
	t_env	*tmp;

	new = st->env_tab;
	if (!(command[1]))
		return (SUCCESS);
	if (ft_strncmp(command[1], new->value, env_size(new->value)) == 0)
	{
		if (new->next)
			st->env_tab = new->next;
		else
			st->env_tab = st->env_tab;
		free_node(st, new);
		return (SUCCESS);
	}
	while (new && new->next)
	{
		if (ft_strncmp(command[1], new->next->value, env_size(new->next->value)) == 0)
		{
			tmp = new->next->next;
			free_node(st, new->next);
			new->next = tmp;
			return (SUCCESS);
		}
		new = new->next;
	}
	return (SUCCESS);
}
