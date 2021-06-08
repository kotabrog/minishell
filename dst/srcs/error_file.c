/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:43:24 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/07 19:45:39 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	decide_error_number(int error, int exe_flag, char *s)
{
	int			flag;
	struct stat	sb;

	if (error == ENOENT)
	{
		if (exe_flag)
			flag = ERROR_NOT_FOUND;
		else
			flag = ENOENT;
	}
	else
	{
		if (stat(s, &sb) == -1)
			flag = ERROR;
		else if (S_ISDIR(sb.st_mode))
			flag = ERROR_IS_DIR;
		else
			flag = ERROR;
	}
	return (flag);
}

int	error_file(int error, int exe_flag, char *s)
{
	int			flag;

	if (error > 0)
		flag = decide_error_number(error, exe_flag, s);
	else
		flag = error;
	error_put(flag, s);
	if (!exe_flag)
		return (1);
	if (flag == ERROR_NOT_FOUND)
		return (127);
	if (flag == ERROR_IS_DIR)
		return (126);
	return (1);
}

int	file_status_check(char *file)
{
	struct stat	sb;

	if (stat(file, &sb) == -1)
		return (errno);
	if (S_ISDIR(sb.st_mode))
		return (ERROR_IS_DIR);
	return (SUCCESS);
}
