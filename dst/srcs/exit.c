/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 23:28:46 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/04 23:50:53 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_minus_and_zero(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		++(*str);
	}
	if (**str == '-')
		return (0);
	while (**str == '0')
		++(*str);
	return (sign);
}

static int	check_int(char *str, long long int *num)
{
	int	sign;

	*num = 0;
	sign = check_minus_and_zero(&str);
	if (sign == 0)
		return (ERROR_EXIT_NUM);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (ERROR_EXIT_NUM);
		*num = *num * 10 + (*str - '0');
		if (*num * sign < INT_MIN || INT_MAX < *num * sign)
			return (ERROR_EXIT_NUM);
		++str;
	}
	*num %= 256;
	if (sign == -1)
		*num = (256 - *num) % 256;
	return (SUCCESS);
}

int	builtin_exit(t_status *status, t_command *com, int fork_flag)
{
	long long int	arg;
	int				flag;

	flag = 0;
	if (com == NULL || com->s[1] == NULL)
		arg = status->exit;
	else
		flag = check_int(com->s[1], &arg);
	if (flag)
	{
		if (!fork_flag)
			printf("exit\n");
		error_put2(flag, "exit", com->s[1]);
		exit(255);
	}
	if (com != NULL && com->s[1] != NULL && com->s[2] != NULL)
		return (error_put(ERROR_EXIT_MANY, "exit"));
	if (!fork_flag)
		printf("exit\n");
	exit(arg);
}
