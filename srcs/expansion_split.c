/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 20:11:41 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/06 23:50:05 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_split(char *s)
{
	int	quote;
	int	i;
	int	n;

	quote = FALSE;
	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] == QUOT_FLAG)
			quote = !quote;
		else if (!quote && (i != 0 && !ft_isspace(s[i - 1])) && \
				ft_isspace(s[i]))
			++n;
		++i;
	}
	if (i != 0 && !ft_isspace(s[i - 1]))
		++n;
	return (n);
}

static int	str_to_dst(char *s, char **dst, int i, int *start)
{
	if (ft_strndup_ex(dst, s, i - *start))
		return (ERROR);
	*start = i + 1;
	return (SUCCESS);
}

static int	split_space(char *s, char ***dst)
{
	int	start;
	int	i;
	int	j;
	int	quote;

	start = 0;
	i = 0;
	j = 0;
	quote = FALSE;
	while (s[i])
	{
		if (s[i] == QUOT_FLAG)
			quote = !quote;
		else if (!quote && (i == 0 || ft_isspace(s[i - 1])) && \
				ft_isspace(s[i]))
			++start;
		else if (!quote && ft_isspace(s[i]))
			if (str_to_dst(s + start, &((*dst)[j++]), i, &start))
				return (ERROR);
		++i;
	}
	if (start != i && str_to_dst(s + start, &((*dst)[j]), i, &start))
		return (ERROR);
	return (SUCCESS);
}

int	expansion_split(char *s, char ***dst)
{
	int	n;

	n = count_split(s);
	if (ft_malloc(dst, sizeof(char *), n + 1))
		return (ERROR);
	(*dst)[n] = NULL;
	if (split_space(s, dst))
		return (ERROR);
	return (n);
}
