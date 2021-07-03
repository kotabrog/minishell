/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:36:56 by tkano             #+#    #+#             */
/*   Updated: 2021/06/30 16:54:26 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_one(char *command, t_env **env)
{
	char	*key;
	char	*value;
	int		flag;
	t_env	*temp;

	key = NULL;
	value = NULL;
	flag = env_get_key_str(&key, command);
	if (flag == IN_VALID_ENV)
		return (status_value_conversion(error_put2(flag, \
				"export", command)));
	if (!flag)
		flag = env_get_value_str(&value, command, ft_strlen(key));
	if (!flag)
		temp = env_search_key(*env, key);
	if (!flag && temp)
		env_change(key, value, temp);
	else if (!flag)
		flag = env_add(key, value, env);
	if (flag)
	{
		free(key);
		free(value);
	}
	return (status_value_conversion(flag));
}

int	do_export(char **command, t_env **env)
{
	int	flag;

	flag = SUCCESS;
	if (command[1] == NULL)
		return (put_sorted_env(*env));
	++command;
	while (*command)
	{
		flag |= export_one(*command, env);
		++command;
	}
	return (flag);
}
