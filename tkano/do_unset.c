/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:45:34 by tkano             #+#    #+#             */
/*   Updated: 2021/06/11 21:23:05 by tkano            ###   ########.fr       */
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

static void	free_node(t_env *env, t_env *new)
{
	if (env == new && env->next == NULL)
	{
		ft_free(&(env->value));
		//env->value = NULL;
		env->next = NULL;
		return ;
	}
	ft_free(&(new->value));
	ft_free(&new);
}

int		do_unset(char **command, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = env;
	if (!(command[1]))
		return (SUCCESS);
	if (ft_strncmp(command[1], new->value, env_size(new->value)) == 0)
	{
		if (new->next)
			env = new->next;
		else
			env = env;
		free_node(env, new);
		return (SUCCESS);
	}
	while (new && new->next)
	{
		if (ft_strncmp(command[1], new->next->value, env_size(new->next->value)) == 0)
		{
			tmp = new->next->next;
			free_node(env, new->next);
			new->next = tmp;
			return (SUCCESS);
		}
		new = new->next;
	}
	return (SUCCESS);
}
