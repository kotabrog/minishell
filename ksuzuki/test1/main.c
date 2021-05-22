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

int	read_parse_command(char **s, char **memo, char ***split)
{
	char	*command;
	char	**split_command;
	int		flag;

	flag = read_input(&command, memo);
	if (flag == ERROR)
		return (ERROR);
	flag = read_command_split(&split_command, command);
	if (flag == ERROR)
	{
		ft_free(&command);
		return (ERROR);
	}
	*s = command;
	*split = split_command;
	return (SUCCESS);
}

void	debug_print(char *s, char **split)
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

int	loop_shell(void)
{
	char	*s;
	char	*memo;
	char	**split;

	memo = NULL;
	while (TRUE)
	{
		if (read_parse_command(&s, &memo, &split))
			continue ;
		debug_print(s, split);
		ft_free(&s);
		ft_free(&split);
	}
	free(memo);
}

int	main(void)
{
	loop_shell();
}
