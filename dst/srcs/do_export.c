/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:36:56 by tkano             #+#    #+#             */
/*   Updated: 2021/06/25 18:32:20 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(t_env *env, char *args)
{
	char	arg_key[BUFF_SIZE];
	char	env_key[BUFF_SIZE];
	char	*tmp;

	if (!get_env_key(arg_key, args))
		return (ERROR);
	while (env)
	{
		get_env_key(env_key, env->value);
		if (ft_strcmp(arg_key, env_key) == 0)
		{
			tmp = ft_strdup(args);
			if (tmp == NULL)
				return (ERROR);
			ft_free(&(env->value));
			env->value = ft_strdup(args);
			env->value = tmp;
			return (SUCCESS);
		}
		env = env->next;
	}
	return (1);
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		if (env->value == NULL)
			return (ERROR);
		return (SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (ERROR);
	new->value = ft_strdup(value);
	if (new->value == NULL)
	{
		ft_free(&new);
		return (ERROR);
	}
	while (env && env->next)
		env = env->next;
	env->next = new;
	new->next = NULL;
	return (SUCCESS);
}

int	export_env(char **command, t_env *env, t_env *tmp)
{
	int	error_num;
	int	new_env;

	error_num = check_ex_arg(command[1]);
	if (command[1][0] == '=')
		error_num = IN_VALID_ENV;
	if (error_num < 0)
		return (error_put2(error_num, "export", command[1]));
	new_env = 1;
	if (error_num == 1)
		new_env = is_env(env, command[1]);
	if (new_env == 1)
	{
		if (error_num == 1)
			error_num = env_add(command[1], env);
		return (env_add(command[1], tmp));
	}
	else
		return (new_env);
}

int	do_export(char **command, t_env *env, t_env *tmp)
{
	int	error_num;

	if (!command[1])
	{
		error_num = put_sorted_env(tmp);
		return (status_value_conversion(error_num));
	}
	else
		error_num = export_env(command, env, tmp);
	return (status_value_conversion(error_num));
}
