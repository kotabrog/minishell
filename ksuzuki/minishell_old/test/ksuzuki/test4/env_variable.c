/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 21:13:31 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/25 18:21:40 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_env(t_status *status)
{
	if_error(dict_init(&(status->env), DICT_ALLOCATE_SIZE), ENOMEM, NULL, True);
	return (SUCCESS);
}
