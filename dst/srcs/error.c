/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:11:14 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/25 21:14:24 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_make_massage(int n)
{
	char	*err_str[25];

	err_str[1] = "unexpected error";
	err_str[2] = "command not found";
	err_str[3] = "ambiguous redirect";
	err_str[4] = "syntax error near unexpected token `<'";
	err_str[5] = "syntax error near unexpected token `>'";
	err_str[6] = "syntax error near unexpected token `;'";
	err_str[7] = "syntax error near unexpected token `|'";
	err_str[8] = "syntax error near unexpected token `newline'";
	err_str[9] = "Multiline is not supported.";
	return (err_str[n]);
}

int	error_put(int err_num, char *command)
{
	char	*error_massage;

	if (err_num < 0)
		error_massage = error_make_massage(-err_num);
	else
		error_massage = strerror(err_num);
	if (command)
		printf("minishell: %s: %s\n", command, error_massage);
	else
		printf("minishell: %s\n", error_massage);
	return (err_num);
}

void	error_process(int err_num, char *command, int exit_flag)
{
	error_put(err_num, command);
	if (exit_flag)
	{
		if (err_num < 0)
			err_num *= -1;
		exit(err_num);
	}
}

void	error_if(int flag, int err_num, char *command, int exit_flag)
{
	if (flag)
		error_process(err_num, command, exit_flag);
}
