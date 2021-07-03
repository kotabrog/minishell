/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utility3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:32:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/02 01:56:20 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		++i;
		env = env->next;
	}
	return (i);
}

static int	env_init_from_key_value(char *key, char *value, t_env **env)
{
	if (env_init(env))
		return (ERROR);
	(*env)->key = key;
	(*env)->value = value;
	return (SUCCESS);
}

int	env_add(char *key, char *value, t_env **env)
{
	t_env	*temp;
	int		flag;

	if (*env == NULL)
		flag = env_init_from_key_value(key, value, env);
	else
	{
		temp = *env;
		while (temp->next)
			temp = temp->next;
		flag = env_init_from_key_value(key, value, &(temp->next));
	}
	return (flag);
}

void	env_change(char *key, char *value, t_env *env)
{
	free(key);
	free(env->value);
	env->value = value;
}
