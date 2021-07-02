/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utility1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:42:36 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/02 02:16:35 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_init(t_env **env)
{
	if (ft_malloc(env, sizeof(t_env), 1))
		return (ERROR);
	(*env)->key = NULL;
	(*env)->value = NULL;
	(*env)->next = NULL;
	return (SUCCESS);
}

int	env_init_from_str(t_env **env, char *str)
{
	int	flag;

	if (env_init(env))
		return (ERROR);
	flag = env_get_key_str(&((*env)->key), str);
	if (flag == SUCCESS)
		flag = env_get_value_str(&((*env)->value), str, \
									ft_strlen((*env)->key));
	if (flag)
		env_free(env);
	return (flag);
}

int	env_free(t_env **env)
{
	if (env == NULL || *env == NULL)
		return (SUCCESS);
	free((*env)->key);
	free((*env)->value);
	ft_free(env);
	return (SUCCESS);
}

int	env_all_free(t_env **env)
{
	t_env	*temp;

	if (env == NULL)
		return (SUCCESS);
	while (*env)
	{
		temp = (*env)->next;
		env_free(env);
		*env = temp;
	}
	return (SUCCESS);
}
