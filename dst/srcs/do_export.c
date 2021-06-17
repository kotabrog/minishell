/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:36:56 by tkano             #+#    #+#             */
/*   Updated: 2021/06/15 21:51:19 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_ex_arg(const char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]) == 1)
		return (IN_VALID_ENV);
	while (arg[i] && arg[i] == '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (IN_VALID_ENV);
		i++;
	}
	if (arg[i] != '=')
		return (2);
	return (1);
}

char	*get_env_key(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
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

	get_env_key(arg_key, args);
	while (env && env->next)
	{
		get_env_key(env_key, env->value);
		if (ft_strcmp(arg_key, env_key) == 0)
		{
			ft_free(&(env->value));
			env->value = ft_strdup(args);
			if (env->value == NULL)
				return (ERROR);
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
		if (env->value == NULL)
			return (ERROR);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	if (new->value == NULL)
		return (ERROR);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (SUCCESS);
}

int	do_export(char **command, t_env *env)
{
	int new_env;
	int	error_num;

	new_env = 0;
	if (!command[1])
	{
		put_sorted_env(env);
		return (SUCCESS);
	}
	else
	{
		error_num = check_ex_arg(command[1]);
		if (command[1][0] == '=')
			error_num = IN_VALID_ENV;
		if (error_num < 0)
			error_put2(error_num, "export", command[1]);
		if (error_num == 2)
			new_env = is_env(env, command[1]);
		if (new_env == 0)
			env_add(command[1], env);
	}
	return (SUCCESS);
}
