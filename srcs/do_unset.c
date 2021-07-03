/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 20:45:34 by tkano             #+#    #+#             */
/*   Updated: 2021/06/27 22:18:01 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_delete(t_env *env)
{
	t_env	*temp;

	temp = env->next;
	env->next = temp->next;
	env_free(&temp);
	return (SUCCESS);
}

static int	is_key(char *key)
{
	if (!ft_isalpha_underbar(*key))
		return (FALSE);
	++key;
	while (*key)
	{
		if (!ft_isalnum_underbar(*key))
			return (FALSE);
		++key;
	}
	return (TRUE);
}

static int	unset_one(char *command, t_env **env)
{
	t_env	*temp;

	if (!is_key(command))
		return (status_value_conversion(error_put2(IN_VALID_ENV, \
				"unset", command)));
	temp = *env;
	if (ft_strcmp(temp->key, command) == 0)
	{
		*env = (*env)->next;
		env_free(&temp);
		return (SUCCESS);
	}
	while (temp->next)
	{
		if (ft_strcmp(temp->next->key, command) == 0)
			return (env_delete(temp));
		temp = temp->next;
	}
	return (SUCCESS);
}

int	do_unset(char **command, t_env **env)
{
	int	flag;

	flag = SUCCESS;
	++command;
	while (*command)
	{
		flag |= unset_one(*command, env);
		++command;
	}
	return (flag);
}
