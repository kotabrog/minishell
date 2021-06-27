/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utility.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 22:10:16 by tkano             #+#    #+#             */
/*   Updated: 2021/06/27 22:11:38 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(char *key)
{
	size_t	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	return (i);
}

void	free_node(t_env *dst, t_env *new)
{
	if (dst == new && new->next == NULL)
	{
		ft_free(&(dst->value));
		dst->next = NULL;
		return ;
	}
	ft_free(&(new->value));
	ft_free(&new);
}

int	loop_unset(char *command, t_env *st, t_env *new)
{
	t_env	*tmp;

	while (new && new->next)
	{
		if (ft_strncmp(command, new->next->value, \
			env_size(new->next->value)) == 0)
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
