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

void	loop_shell(t_status *status)
{
	char	*s;
	int		flag;

	while (TRUE)
	{
		flag = 0;
		if (read_parse_command(status, &s, &(status->memo), &(status->tree)))
			continue ;
		flag = process_tree(status, status->tree);
		printf("flag: %d\n", flag);
		printf("exit status: %d\n", status->exit);
		debug_tree(status->tree);
		ft_free(&s);
		status_turn_finish(status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_status	*status;
	int			flag;

	error_if(argc != 1 || !**argv, ERROR_ARGMENT, NULL, TRUE);
	flag = status_init(&status, envp);
	error_if(flag, flag, NULL, TRUE);
	loop_shell(status);
	status_finish(status);
}
