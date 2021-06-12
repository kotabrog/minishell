/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:11:26 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 21:51:22 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_input(char **s, t_status *status)
{
	int			flag;

	flag = FALSE;
	while (!flag)
	{
		*s = readline("minishell$ ");
		if (*s == NULL)
			builtin_exit(status, NULL, 0);
		else if (ft_strlen(*s) > 0)
		{
			add_history(*s);
			flag = TRUE;
		}
		else
			free(*s);
	}
	error_if(errno, errno, NULL, TRUE);
	return (flag);
}
