/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 20:39:26 by tkano             #+#    #+#             */
/*   Updated: 2021/06/20 11:40:53 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pwd_value(t_env *env, char *oldpwd, size_t len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env->value[i++])
	{
		if (i > (int)len)
			oldpwd[j++] = env->value[i];
	}
	oldpwd[j] = '\0';
}

static char	*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			oldpwd = malloc(sizeof(char) * s_alloc + 1);
			if (!oldpwd)
				return (NULL);
			pwd_value(env, oldpwd, len);
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (ERROR);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd)
		return (ERROR);
	if (is_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_free(&oldpwd);
	return (SUCCESS);
}

static int	go_to_path(int option, t_env *env)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		update_oldpwd(env);
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			return (error_put(NO_SET_HOME, "cd"));
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			return (error_put(NO_SET_OLD, "cd"));
		update_oldpwd(env);
	}
	ret = chdir(env_path);
	ft_free(&env_path);
	return (ret);
}

int	do_cd(char **command, t_env *env)
{
	int		cd_ret;

	if (!command[1])
		return (go_to_path(0, env));
	if (ft_strcmp(command[1], "-") == 0)
		cd_ret = go_to_path(1, env);
	else
	{
		update_oldpwd(env);
		cd_ret = chdir(command[1]);
		if (cd_ret != 0)
			return (error_put(NO_DIR, "cd"));
	}
	return (cd_ret);
}
