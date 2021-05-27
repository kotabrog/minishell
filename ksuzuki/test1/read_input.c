/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:11:26 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 21:51:22 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_strchar(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2, ssize_t n1, ssize_t n2)
{
	char	*p;

	if (n1 == -1)
		n1 = ft_strlen(s1);
	p = (char *)malloc(n1 + n2 + 1);
	if (p == NULL)
		return (NULL);
	ft_strcpy(p, s1, n1);
	ft_strcpy(p + n1, s2, n2);
	p[n1 + n2] = 0;
	return (p);
}

static int	ft_put_line(char **line, char **memo, char *buf)
{
	int		flag;
	size_t	n;
	char	*temp;

	n = ft_strchar(buf, '\n');
	temp = ft_strjoin(*line, buf, -1, n);
	if (temp == NULL)
		return (-1);
	free(*line);
	*line = temp;
	temp = NULL;
	flag = 0;
	if (buf[n] == '\n')
	{
		temp = ft_strdup(buf + n + 1);
		if (temp == NULL)
			return (-1);
		flag = 1;
	}
	free(*memo);
	*memo = temp;
	return (flag);
}

static int	get_next_line(char **line, char **memo)
{
	int		flag;
	char	*buf;
	ssize_t	n;

	flag = 0;
	if (ft_malloc(&buf, sizeof(char), BUFF_SIZE + 1))
		flag = -1;
	while (flag == 0)
	{
		n = read(0, buf, BUFF_SIZE);
		if (n <= 0)
			break ;
		buf[n] = 0;
		flag = ft_put_line(line, memo, buf);
	}
	free(buf);
	if (flag == -1)
	{
		ft_free(memo);
		ft_free(line);
	}
	return (flag);
}

int	read_input(char **s, char **memo)
{
	int			flag;

	if (s == NULL)
		return (-1);
	if (ft_malloc(s, sizeof(char), 1))
		return (-1);
	(*s)[0] = 0;
	flag = 0;
	if (*memo)
		flag = ft_put_line(s, memo, *memo);
	if (flag == ERROR)
		ft_free(s);
	else if (flag == 1)
	{
		write(1, "minishell$ ", 11);
		ft_putstr_fd(*s, 1);
	}
	else if (flag == 0)
	{
		write(1, "minishell$ ", 11);
		flag = get_next_line(s, memo);
	}
	return (flag);
}
