/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:08:59 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 19:12:57 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *p, char const *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	if (s == NULL)
		return (0);
	i = 0;
	while (*s++)
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	n;

	n = ft_strlen(s);
	if ((p = (char *)malloc(n + 1)) == NULL)
		return (NULL);
	ft_strcpy(p, s, n);
	p[n] = 0;
	return (p);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*p;

	if (s == NULL)
		n = 0;
	if ((p = (char *)malloc(n + 1)) == NULL)
		return (NULL);
	ft_strcpy(p, s, n);
	p[n] = 0;
	return (p);
}

char	*ft_strjoin_ex(char *s1, char *s2, ssize_t n1, ssize_t n2)
{
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (n1 < 0)
		n1 = ft_strlen(s1);
	if (n2 < 0)
		n2 = ft_strlen(s2);
	if ((p = (char *)malloc(n1 + n2 + 1)) == NULL)
		return (NULL);
	ft_strncpy(p, s1, n1);
	ft_strncpy(p + n1, s2, n2);
	p[n1 + n2] = 0;
	return (p);
}