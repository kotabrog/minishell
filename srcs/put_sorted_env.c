/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sorted_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:47:57 by tkano             #+#    #+#             */
/*   Updated: 2021/06/30 21:21:40 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_put(t_env **env)
{
	while (*env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd((*env)->key, 1);
		if ((*env)->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd((*env)->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		++env;
	}
}

static void	env_sort(t_env **env)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[j]->key, env[i]->key) < 0)
			{
				tmp = env[j];
				env[j] = env[i];
				env[i] = tmp;
			}
			++j;
		}
		++i;
	}
}

static int	env_to_array(t_env *env, t_env ***env_array)
{
	int	i;

	i = 0;
	if (ft_malloc(env_array, sizeof(t_env *), env_len(env) + 1))
		return (ERROR);
	while (env)
	{
		(*env_array)[i++] = env;
		env = env->next;
	}
	(*env_array)[i] = NULL;
	return (SUCCESS);
}

int	put_sorted_env(t_env *env)
{
	t_env	**env_array;

	if (env == NULL)
		return (SUCCESS);
	if (env_to_array(env, &env_array))
		return (status_value_conversion(ERROR));
	env_sort(env_array);
	env_put(env_array);
	free(env_array);
	return (SUCCESS);
}
