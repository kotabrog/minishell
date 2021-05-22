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

char	*ft_strndup(const char *s, ssize_t n)
{
	char	*p;

	if (s == NULL)
		n = 0;
	else if (n < 0)
		n = ft_strlen(s);
	p = (char *)malloc(n + 1);
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, s, n);
	p[n] = '\0';
	return (p);
}

int	ft_strndup_ex(char **dest, const char *s, ssize_t n)
{
	if (s == NULL)
		n = 0;
	else if (n < 0)
		n = ft_strlen(s);
	*dest = (char *)malloc(n + 1);
	if (*dest == NULL)
		return (ERROR);
	ft_strcpy(*dest, s, n);
	(*dest)[n] = '\0';
	return (SUCCESS);
}

int	ft_isspace(const char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || \
			c == '\r' || c == '\t' || c == '\v');
}
