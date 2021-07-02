/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_execve2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:40:30 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/02 01:52:26 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_env_array(t_env *env, char ***env_array, int i)
{
	char	*temp;

	(*env_array)[i] = ft_strjoin(env->key, "=");
	if ((*env_array)[i] == NULL)
	{
		ft_free_double_char(env_array);
		return (ERROR);
	}
	temp = ft_strjoin((*env_array)[i], env->value);
	ft_free(&((*env_array)[i]));
	if (temp == NULL)
	{
		ft_free_double_char(env_array);
		return (ERROR);
	}
	(*env_array)[i] = temp;
	return (SUCCESS);
}

int	make_env_array(t_env *env, char ***env_array)
{
	int		i;

	i = 0;
	if (ft_malloc(env_array, sizeof(char *), env_len(env) + 1))
		return (ERROR);
	while (env)
	{
		if (env->value)
			if (add_env_array(env, env_array, i++))
				return (ERROR);
		env = env->next;
	}
	(*env_array)[i] = NULL;
	return (SUCCESS);
}
