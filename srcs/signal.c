/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 12:50:35 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/05 13:52:49 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal->signal_flag = signum;
	}
}

static void	execution_handler(int signam)
{
	g_signal->signal_flag = signam;
	if (g_signal->exit_pid > 0)
	{
		kill(g_signal->exit_pid, SIGTERM);
		g_signal->exit_pid = 0;
	}
	all_command_close(g_signal->tree);
}

void	signal_reset(void)
{
	g_signal->signal_flag = 0;
	g_signal->tree = NULL;
	g_signal->exit_pid = 0;
}

t_global	*signal_init(void)
{
	t_global	*sig;

	sig = malloc(sizeof(t_global));
	if (sig == NULL)
		return (NULL);
	sig->signal_flag = 0;
	sig->tree = NULL;
	sig->exit_pid = 0;
	return (sig);
}

int	set_signal(int mode)
{
	if (mode == 0)
	{
		signal_reset();
		if (signal(SIGINT, input_handler) == SIG_ERR || \
				signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (errno);
	}
	else if (mode == 1)
	{
		signal_reset();
		if (signal(SIGINT, execution_handler) == SIG_ERR || \
				signal(SIGQUIT, execution_handler) == SIG_ERR)
			return (errno);
	}
	else if (mode == 2)
	{
		if (signal(SIGINT, heardoc_handler) == SIG_ERR || \
				signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			return (errno);
	}
	return (SUCCESS);
}
