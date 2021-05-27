/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 21:11:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/25 22:06:44 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_split(char *s, char **split)
{
	ft_putstr_fd(s, 1);
	write(1, "\n", 1);
	while (*split)
	{
		printf("%ld\n", ft_strlen(*split));
		ft_putstr_fd(*split++, 1);
		write(1, "\n", 1);
	}
}

void	debug_command(t_command *command)
{
	char	**temp;
	int		*fd;

	if (command->flag == 0)
		ft_putstr_fd("----command\n", 1);
	else if (command->flag == SEMICOLON)
		ft_putstr_fd("----semi colon\n", 1);
	else if (command->flag == PIPE)
		ft_putstr_fd("----pipe\n", 1);
	if (command->s && *(command->s))
	{
		temp = command->s;
		while (*temp)
		{
			ft_putstr_fd(*temp++, 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
	if (command->file && *(command->file))
	{
		ft_putstr_fd("--file\n", 1);
		temp = command->file;
		fd = command->fd;
		while (*temp)
		{
			ft_putnbr_fd(*fd++, 1);
			write(1, " ", 1);
			ft_putstr_fd(*temp++, 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}

void	debug_tree(t_tree *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left)
		debug_tree(tree->left);
	if (tree->right)
		debug_tree(tree->right);
	if (tree->command)
		debug_command(tree->command);
}
