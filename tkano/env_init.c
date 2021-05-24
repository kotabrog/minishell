/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 18:44:13 by tkano             #+#    #+#             */
/*   Updated: 2021/05/23 20:58:10 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_init(t_status *status, char **arg_env)
{
	t_env	*env;
	t_env	*new;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (ERROR);
	env->value = ft_strdup(arg_env[0]);
	env->next = NULL;
	status->env = env;
	i = 1;
	while (arg_env && arg_env[0] && arg_env[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (ERROR);
		new->value = ft_strdup(arg_env[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (SUCCESS);
}
