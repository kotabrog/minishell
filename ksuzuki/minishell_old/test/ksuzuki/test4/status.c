/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 22:17:37 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/24 22:18:57 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_status(t_status **status)
{
	*status = (t_status *)malloc(sizeof(t_status));
	if_error(*status == NULL, ENOMEM, NULL, True);
	if_error(init_env(*status), ENOMEM, NULL, True);
}

void	free_status(t_status *status)
{
	dict_free(status->env);
	free(status);
}
