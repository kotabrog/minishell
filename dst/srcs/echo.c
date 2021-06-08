/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 15:34:26 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/06 23:03:13 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_command *com)
{
	int		flag;
	char	**texts;

	texts = &(com->s[1]);
	flag = FALSE;
	if (*texts && ft_strcmp(*texts, "-n") == 0)
	{
		++texts;
		flag = TRUE;
	}
	while (*texts)
	{
		ft_putstr_fd(*(texts++), 1);
		if (*texts)
			ft_putchar_fd(' ', 1);
	}
	if (!flag)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
