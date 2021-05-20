/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 23:32:21 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:09:51 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	n;

	if (s == NULL)
		return (NULL);
	n = ft_strlen(s);
	if (n < start)
		len = 0;
	else
		len = (n < start + len ? n - start : len);
	if ((p = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	ft_strcpy(p, s + start, len);
	p[len] = 0;
	return (p);
}

static void	ft_free_pointer(char **p, int n)
{
	while (0 <= n)
		free(p[n--]);
	return ;
}

static int	ft_strchar_set(char const *str, char c, char **p)
{
	size_t i;
	size_t j;
	size_t start_point;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		start_point = i;
		while (str[i] != c && str[i])
			i++;
		if (str[i - 1] != c)
		{
			if ((p[j] = ft_substr(str, start_point, i - start_point)) == NULL)
			{
				ft_free_pointer(p, j - 1);
				return (ERROR);
			}
		}
		j++;
	}
	return (SUCCESS);
}

static int	ft_count_split(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	if (*s != c && *s)
		count++;
	if (*s == 0)
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

char		**ft_split(char const *s, char c)
{
	size_t	count;
	char	**p;

	count = 0;
	if (s != NULL)
		count = ft_count_split(s, c);
	if ((p = (char **)malloc(sizeof(char *) * (count + 1))) == NULL)
		return (NULL);
	if (s != NULL && count != 0)
	{
		if (ft_strchar_set(s, c, p))
		{
			free(p);
			return (NULL);
		}
	}
	p[count] = NULL;
	return (p);
}
