/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:50:35 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/01 23:47:34 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input_handler(int signum)
{
	ft_putstr_fd("\b\b  \b\b\nminishell$ ", 1);
	g_signal->signal_flag = signum;
}

static void	execution_handler(int signam)
{
	g_signal->signal_flag = signam;
	all_command_close(g_signal->tree);
}

void	signal_reset(void)
{
	g_signal->signal_flag = 0;
	g_signal->tree = NULL;
}

t_global	*signal_init(void)
{
	t_global	*sig;

	sig = malloc(sizeof(t_global));
	if (sig == NULL)
		return (NULL);
	sig->signal_flag = 0;
	sig->tree = NULL;
	return (sig);
}

int	set_signal(int mode)
{
	if (mode == 0)
	{
		signal_reset();
		if (signal(SIGINT, input_handler) == SIG_ERR)
			return (errno);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (errno);
	}
	else if (mode == 1)
	{
		signal_reset();
		if (signal(SIGINT, execution_handler) == SIG_ERR)
			return (errno);
		if (signal(SIGQUIT, execution_handler) == SIG_ERR)
			return (errno);
	}
	else
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR)
			return (errno);
		if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (errno);
	}
	return (SUCCESS);
}
