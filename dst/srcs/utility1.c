/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:17:30 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 20:24:08 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *p, const char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
}

int	ft_strlen_ex(char **s)
{
	int	n;

	n = 0;
	while (s[n])
		++n;
	return (n);
}

int	ft_isspace(const char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
