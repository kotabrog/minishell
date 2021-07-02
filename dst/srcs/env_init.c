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

static int	is_under_score(char *str)
{
	return (str && str[0] == '_' && str[1] == '=');
}

static int	env_set_loop(t_env *env, char **envp)
{
	while (*envp)
	{
		if (!is_under_score(*envp) && \
				env_init_from_str(&(env->next), *envp))
			return (ERROR);
		env = env->next;
		++envp;
	}
	return (SUCCESS);
}

int	env_set(t_env **env, char **envp)
{
	*env = NULL;
	if (envp == NULL || *envp == NULL)
		return (SUCCESS);
	if (is_under_score(*envp))
	{
		++*envp;
		if (*envp == NULL)
			return (SUCCESS);
	}
	if (env_init_from_str(env, *envp))
		return (ERROR);
	if (env_set_loop(*env, envp))
	{
		env_all_free(env);
		return (ERROR);
	}
	return (SUCCESS);
}
