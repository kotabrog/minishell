/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:16:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/01 22:14:06 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_semicolon(t_status *status, t_tree *tree)
{
	int	flag;

	flag = SUCCESS;
	if (tree->left)
		flag = process_tree(status, tree->left);
	if (tree->right)
		flag = process_tree(status, tree->right);
	return (flag);
}

int	process_tree(t_status *status, t_tree *tree)
{
	int	flag;
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (tree->command->flag == SEMICOLON)
		flag = process_semicolon(status, tree);
	else if (tree->command->flag == PIPE)
		flag = process_pipe(status, tree, fd);
	else
		flag = process_command(status, tree, fd, FALSE);
	if (g_signal->signal_flag)
	{
		ft_putchar_fd('\n', 1);
		flag = g_signal->signal_flag + SIGNAL_VALUE;
		set_signal(1);
	}
	return (set_exit_status(status, flag));
}
