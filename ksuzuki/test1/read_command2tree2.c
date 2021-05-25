/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command2tree2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 18:51:30 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/24 23:41:29 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(char *s)
{
	if (ft_strcmp(s, "<") == 0)
		return (READ);
	if (ft_strcmp(s, ">") == 0)
		return (WRITE);
	if (ft_strcmp(s, ">>") == 0)
		return (-WRITE);
	return (MAX_FD);
}

static int	command_count(char *s, int *file_num, int *file_flag)
{
	int	flag;

	flag = is_redirect(s);
	if (*file_flag && flag != MAX_FD)
	{
		if (flag == WRITE)
			return (ERROR_TOKEN_LEFT);
		return (ERROR_TOKEN_RIGHT);
	}
	if (flag != MAX_FD)
		*file_flag = 1;
	else if (s[0] == '>')
		return (ERROR_TOKEN_RIGHT);
	else if (*file_flag)
	{
		++*file_num;
		*file_flag = 0;
	}
	return (SUCCESS);
}

static int command_malloc(t_command *com, int com_num, int file_num)
{
	if (ft_malloc(&(com->s), sizeof(char *), com_num + 1))
		return (ERROR);
	if (ft_malloc(&(com->file), sizeof(char *), file_num + 1))
	{
		ft_free(&(com->s));
		return (ERROR);
	}
	if (ft_malloc(&(com->fd), sizeof(int), file_num + 1))
	{
		ft_free(&(com->s));
		ft_free(&(com->file));
		return (ERROR);
	}
	return (SUCCESS);
}

static int command_set(char **split, t_command *com, int start, int end)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (start < end)
	{
		if (flag)
		{
			com->file[j] = split[start];
			com->fd[j++] = is_redirect(split[start - 1]);
			flag = 0;
		}
		else if (is_redirect(split[start]) != MAX_FD)
			flag = 1;
		else
			com->s[i++] = split[start];
		++start;
	}
	com->s[i] = NULL;
	com->file[j] = NULL;
	return (command_dup(com));
}

int	read_command(char **split, t_command *com, int *id)
{
	int	flag;
	int	start;
	int	file_num;
	int	file_flag;

	flag = 0;
	start = *id;
	file_num = 0;
	file_flag = 0;
	while (flag == 0 && split[*id] && ft_strcmp(split[*id], "|") != 0 && \
			ft_strcmp(split[*id], ";") != 0)
		flag = command_count(split[(*id)++], &file_num, &file_flag);
	if (flag == 0 && file_flag == 1)
		return (ERROR_TOKEN_NEWLINE);
	if (flag == 0)
		flag = command_malloc(com, *id - start - file_num * 2, file_num);
	if (flag == 0)
		flag = command_set(split, com, start, *id);
	return (flag);
}
