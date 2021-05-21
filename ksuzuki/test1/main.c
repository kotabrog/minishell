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

int	read_parse_command(char **s, char **memo)
{
	char	*command;
	int		flag;

	flag = read_input(&command, memo);
	if (flag == ERROR)
		return (ERROR);
	*s = command;
	return (SUCCESS);
}

int	loop_shell()
{
	char	*s;
	char	*memo;

	memo = NULL;
	while (True)
	{
		if (read_parse_command(&s, &memo))
			continue ;
		sleep(2);
		ft_putstr_fd(s, 1);
		write(1, "\n", 1);
		ft_free(&s);
	}
	free(memo);
}

int	main()
{
	loop_shell();
}
