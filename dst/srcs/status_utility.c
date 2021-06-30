/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:54:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/30 17:58:08 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_init(t_status **status, char **envp)
{
	if (ft_malloc(status, sizeof(t_status), 1))
		return (errno);
	(*status)->tree = NULL;
	(*status)->env = envp;
	if (env_init((*status), envp) || tmp_env_init((*status), envp))
	{
		free(status);
		return (ERROR);
	}
	(*status)->exit = 0;
	return (SUCCESS);
}

int	status_turn_finish(t_status *status)
{
	tree_free(&(status->tree));
	return (SUCCESS);
}

int	status_finish(t_status *status)
{
	env_free(status->env_tab);
	env_free(status->env_tmp);
	free(status);
	return (SUCCESS);
}
