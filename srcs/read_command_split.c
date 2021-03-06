/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:53:25 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/24 23:54:55 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	switch_point(const char c)
{
	return (ft_isspace(c) || c == ';' || c == '<' || c == '|' || c == '>');
}

static int	switch_timing(char *s, int index, int quart_flag[2])
{
	if (!quart_flag[1] && s[index] == '\'')
		quart_flag[0] = !quart_flag[0];
	else if (!quart_flag[0] && s[index] == '\"')
		quart_flag[1] = !quart_flag[1];
	if (quart_flag[0] && s[index] == '\'' && \
			(index == 0 || switch_point(s[index - 1])))
		return (TRUE);
	else if (quart_flag[1] && s[index] == '\"' && \
			(index == 0 || switch_point(s[index - 1])))
		return (TRUE);
	else if (quart_flag[0] || quart_flag[1])
		return (FALSE);
	else if (s[index] == '\'' || s[index] == '\"')
		return (FALSE);
	else if (s[index] == ';' ||s[index] == '|')
		return (TRUE);
	else if (s[index] == '>' && (index == 0 || s[index - 1] != '>'))
		return (TRUE);
	else if (s[index] == '<' && (index == 0 || s[index - 1] != '<'))
		return (TRUE);
	else if (s[index] != '>' && s[index] != '<' && !ft_isspace(s[index]) && \
			(index == 0 || switch_point(s[index - 1])))
		return (TRUE);
	return (FALSE);
}

static void	count_split(char *s, int *num, int	quart_flag[2])
{
	int	i;

	i = 0;
	quart_flag[0] = 0;
	quart_flag[1] = 0;
	while (s[i])
	{
		*num += switch_timing(s, i, quart_flag);
		++i;
	}
	quart_flag[0] = 0;
	quart_flag[1] = 0;
}

static int	split_command(char **split, char *s, int quart_flag[2], int id)
{
	int	i;
	int	n;
	int	empty;

	i = 0;
	n = 0;
	empty = 0;
	while (s[i])
	{
		if (switch_timing(s, i, quart_flag))
		{
			if (id != 0 && ft_strndup_ex(split + id - 1, s + i - n, n - empty))
				return (ERROR);
			++id;
			n = 0;
			empty = 0;
		}
		if (ft_isspace(s[i++]) && !quart_flag[0] && !quart_flag[1])
			++empty;
		++n;
	}
	if (n == empty)
		return (SUCCESS);
	return (ft_strndup_ex(split + id - 1, s + i - n, n - empty));
}

int	read_command_split(char ***split, char *s)
{
	int	num;
	int	quart[2];

	num = 0;
	count_split(s, &num, quart);
	if (ft_malloc(split, sizeof(char *), num + 1))
		return (ERROR);
	while (num >= 0)
		(*split)[num--] = NULL;
	if (split_command(*split, s, quart, 0) || quart[0] || quart[1])
	{
		ft_free_double_char(split);
		if (quart[0] || quart[1])
			return (ERROR_MULTILINE);
		return (ERROR);
	}
	return (SUCCESS);
}
