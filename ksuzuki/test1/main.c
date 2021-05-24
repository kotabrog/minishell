/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:32:54 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 21:51:49 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_parse_command(char **s, char **memo, char ***split, t_tree **tree)
{
	char	*command;
	char	**split_command;
	int		flag;

	if (read_input(&command, memo) == ERROR)
		return (error_put(ERROR, NULL));
	flag = read_command_split(&split_command, command);
	if (flag)
	{
		ft_free(&command);
		return (error_put(flag, NULL));
	}
	flag = read_command2tree(tree, split_command);
	if (flag)
	{
		ft_free(&command);
		ft_free_double_char(&split_command);
		return (error_put(flag, NULL));
	}
	*s = command;
	*split = split_command;
	return (SUCCESS);
}

int	loop_shell(void)
{
	char	*s;
	char	*memo;
	char	**split;
	int		flag;
	t_tree	*tree;

	memo = NULL;
	while (TRUE)
	{
		if (read_parse_command(&s, &memo, &split, &tree))
			continue ;
		// debug_print_split(s, split);
		debug_tree(tree);
		ft_free(&s);
		ft_free_double_char(&split);
		tree_free(&tree);
	}
	free(memo);
}

int	main(void)
{
	loop_shell();
}
