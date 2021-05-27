/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:36:56 by tkano             #+#    #+#             */
/*   Updated: 2021/05/27 21:59:37 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ex_arg(const char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == '=')
	{
		return (1);
	}
	return (0);
}

char	*get_env_key(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_env(t_env *env, char *args)
{
	char	arg_key[BUFF_SIZE];
	char	env_key[BUFF_SIZE];

	get_env_key(env_key, args);
	while (env && env->next)
	{
		get_env_key(env_key, env->value);
		if (ft_strcmp(arg_key, env_key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (SUCCESS);
}

int			env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

int	do_export(char **command, t_env *env)
{
	int i;
	int	args_check;

	i = 0;
	if (!command[1])
	{
		put_sorted_env(env);
		return (SUCCESS);
	}
	else
	{
		args_check = check_ex_arg(args[1]);
		if (args_check)
			is_env(env, arg[1]);
		else
			env_add(args[1], env);
	}
	return (SUCCESS);
}
