/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:11:14 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/15 21:47:31 by tkano            ###   ########.fr       */
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
	err_str[9] = "Multiline is not supported";
	err_str[10] = "No arguments are accepted";
	err_str[11] = "numeric argument required";
	err_str[12] = "too many arguments";
	err_str[13] = "Permission denied";
	err_str[14] = "is a directory";
	err_str[15] = "not a valid identifier";
	return (err_str[n]);
}

int	error_put2(int err_num, char *com1, char *com2)
{
	char	*error_massage;

	if (err_num < 0)
		error_massage = error_make_massage(-err_num);
	else
		error_massage = strerror(err_num);
	ft_putstr_fd("minishell: ", STDERR);
	if (com1)
	{
		ft_putstr_fd(com1, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	if (com2)
	{
		ft_putstr_fd(com2, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(error_massage, STDERR);
	ft_putstr_fd("\n", STDERR);
	return (err_num);
}

int	error_put(int err_num, char *command)
{
	char	*error_massage;

	if (err_num < 0)
		error_massage = error_make_massage(-err_num);
	else
		error_massage = strerror(err_num);
	ft_putstr_fd("minishell: ", STDERR);
	if (command)
	{
		ft_putstr_fd(command, STDERR);
		ft_putstr_fd(": ", STDERR);
	}
	ft_putstr_fd(error_massage, STDERR);
	ft_putstr_fd("\n", STDERR);
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
