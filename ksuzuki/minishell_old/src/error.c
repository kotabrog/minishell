/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:30:54 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:17:10 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_error_massage(int n)
{
	char *err_str[25];

	err_str[1] = "command not found";
	return err_str[n];
}

void	put_error(int err_num, char *command)
{
	char *error_massage;

	if (err_num < 0)
		error_massage = make_error_massage(-err_num);
	else
		error_massage = strerror(err_num);
	if (command)
		printf("minishell: %s: %s\n", command, error_massage);
	else
		printf("minishell: %s\n", error_massage);
}

void	process_error(int err_num, char *command, int exit_flag)
{
	put_error(err_num, command);
	if (exit_flag)
	{
		if (err_num < 0)
			err_num *= -1;
		exit(err_num);
	}
}
