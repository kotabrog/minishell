/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 21:11:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/24 23:56:25 by ksuzuki          ###   ########.fr       */
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

	// printf("flag: %d", command->flag);
	// write(1, "\n", 1);
	if (command->s)
	{
		temp = command->s;
		while (*temp)
		{
			// printf("%ld:", ft_strlen(*temp));
			ft_putstr_fd(*temp++, 1);
			write(1, "\n", 1);
		}
	}
	if (command->file)
	{
		temp = command->file;
		fd = command->fd;
		while (*temp)
		{
			// printf("%ld, %d:", ft_strlen(*temp), *(fd++));
			ft_putstr_fd(*temp++, 1);
			write(1, "\n", 1);
		}
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
