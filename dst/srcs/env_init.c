/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:44:13 by tkano             #+#    #+#             */
/*   Updated: 2021/06/30 16:35:47 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_env(t_env *env, char **arg_env)
{
	t_env	*new;
	int		i;

	i = 1;
	while (arg_env && arg_env[0] && arg_env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (ERROR);
		new->value = ft_strdup(arg_env[i]);
		if (!new->value)
			return (ERROR);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}

int	env_init(t_status *status, char **arg_env)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	env->value = ft_strdup(arg_env[0]);
	if (env->value == NULL)
		return (ERROR);
	env->next = NULL;
	status->env_tab = env;
	return (set_env(env, arg_env));
}

int	tmp_env_init(t_status *status, char **arg_env)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	env->value = ft_strdup(arg_env[0]);
	if (env->value == NULL)
		return (ERROR);
	env->next = NULL;
	status->env_tmp = env;
	return (set_env(env, arg_env));
}

int	env_free(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		ft_free(&(tmp->value));
		ft_free(&(tmp));
	}
	ft_free(&(env->value));
	ft_free(&env);
	return (SUCCESS);
}
