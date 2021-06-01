/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:41:22 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/30 18:32:05 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	status_value_conversion(int flag)
{
	if (flag == SUCCESS)
		return (0);
	if (flag == ERROR || flag == ERROR_AMB_REDIRECT)
		return (1);
	if (flag == ERROR_NOT_FOUND)
		return (127);
	if (-8 <= flag && flag <= -4)
		return (258);
	flag %= 256;
	if (flag <= 127)
		return (1);
	return (flag);
}

int	set_exit_status(t_status *status, int flag)
{
	flag = status_value_conversion(flag);
	status->exit = flag;
	return (flag);
}
