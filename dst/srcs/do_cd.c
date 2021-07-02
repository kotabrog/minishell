/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:39:26 by tkano             #+#    #+#             */
/*   Updated: 2021/06/25 19:21:06 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_path(int flag, t_env *env, char **path)
{
	if (flag == 0)
	{
		env_get_value(env, "HOME", path);
		if (*path == NULL)
		{
			error_put(NO_SET_HOME, "cd");
			return (ERROR);
		}
	}
	else if (flag == 1)
	{
		env_get_value(env, "OLDPWD", path);
		if (*path == NULL)
		{
			error_put(NO_SET_OLD, "cd");
			return (ERROR);
		}
	}
	return (SUCCESS);
}

static int	update_oldpwd(t_env **env)
{
	char	cwd[PATH_MAX];
	char	*key;
	char	*value;
	int		flag;
	t_env	*temp;

	flag = SUCCESS;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	value = ft_strdup(cwd);
	key = ft_strdup("OLDPWD");
	if (value == NULL || key == NULL)
		flag = ERROR;
	temp = env_search_key(*env, "OLDPWD");
	if (!flag && temp)
		env_change(key, value, temp);
	else if (!flag)
		flag = env_add(key, value, env);
	if (flag)
	{
		free(key);
		free(value);
	}
	return (flag);
}

int	do_cd(char **command, t_env *env)
{
	int		flag;
	char	*path;

	flag = SUCCESS;
	if (command[1] == NULL)
		flag = get_path(0, env, &path);
	else if (ft_strcmp(command[1], "-") == 0)
		flag = get_path(1, env, &path);
	else
		path = command[1];
	if (flag)
		return (status_value_conversion(flag));
	if (update_oldpwd(&env))
		return (status_value_conversion(ERROR));
	if (chdir(path))
		return (status_value_conversion(error_put(NO_DIR, "cd")));
	return (status_value_conversion(flag));
}
