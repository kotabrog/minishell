/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:54:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/29 12:14:32 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	status_init(t_status **status, char **envp)
{
	if (ft_malloc(status, sizeof(t_status), 1))
		return (errno);
	(*status)->tree = NULL;
	(*status)->memo = NULL;
	(*status)->env = envp;
	return (SUCCESS);
}

int	status_turn_finish(t_status *status)
{
	tree_free(&(status->tree));
	return (SUCCESS);
}

int	status_finish(t_status *status)
{
	free(status->memo);
	free(status);
	return (SUCCESS);
}
