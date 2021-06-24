/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 22:50:22 by tkano             #+#    #+#             */
/*   Updated: 2021/06/23 22:51:45 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_value(t_env *env)
{
	size_t	ret;

	ret = 0;
	while (env && env->next != NULL)
	{
		if (env->value != NULL)
		{
			ret += ft_strlen(env->value);
			ret++;
		}
		env = env->next;
	}
	return (ret);
}

int	tab_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}
