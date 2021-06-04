/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 16:41:22 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/05 00:06:53 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_signal_and_mod(long long int num)
{
	if (WIFEXITED(num))
		return (WEXITSTATUS(num));
	if (WIFSIGNALED(num))
		return (WTERMSIG(num) + SIGNAL_VALUE);
	if (num >= 0)
		return (num % 256);
	else
		return ((256 - (-num % 256)) % 256);
}

int	status_value_conversion(int flag)
{
	if (flag == SUCCESS)
		return (EXIT_SUCCESS);
	if (flag == ERROR || flag == ERROR_AMB_REDIRECT || flag == ERROR_EXIT_MANY)
		return (EXIT_FAILURE);
	if (flag == ERROR_NOT_FOUND)
		return (127);
	if (-8 <= flag && flag <= -4)
		return (258);
	flag = calc_signal_and_mod(flag);
	return (flag);
}

int	set_exit_status(t_status *status, int flag)
{
	flag = status_value_conversion(flag);
	status->exit = flag;
	return (flag);
}
