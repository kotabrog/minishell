/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:16:03 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/25 21:16:31 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strdup_ex(char **s)
{
	char	**p;
	int		n;
	int		i;

	n = ft_strlen_ex(s);
	if (ft_malloc(&p, sizeof(char *), n + 1))
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = ft_strdup(s[i]);
		if (p[i] == NULL)
			break ;
		++i;
	}
	if (i != n)
	{
		while (i--)
			free(p[i]);
		free(p);
		return (NULL);
	}
	p[n] = NULL;
	return (p);
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
