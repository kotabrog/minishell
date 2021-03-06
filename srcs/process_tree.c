/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 18:16:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/05 18:52:33 by ksuzuki          ###   ########.fr       */
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
	set_signal(1);
	return (set_exit_status(status, flag));
}
