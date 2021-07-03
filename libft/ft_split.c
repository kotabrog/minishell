/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 22:05:41 by tkano             #+#    #+#             */
/*   Updated: 2021/05/17 13:14:48 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_str(char *s, char c)
{
	int		i;
	int		flag;
	int		count;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		if (flag == 1 && s[i] == c)
			flag = 0;
		if (flag == 0 && s[i] != c)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**mem_free(char **ret, int index)
{
	while (index >= 0)
	{
		free(ret[index]);
		index--;
	}
	free(ret);
	return (NULL);
}

static int	sep_strlen(char *str, int index, char c)
{
	int		len;

	len = 0;
	while (str[index] != c && str[index])
	{
		len++;
		index++;
	}
	return (len);
}

static char	**create_str(char *s, char c, char **ret)
{
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = sep_strlen((char *)s, i, c);
			ret[k] = malloc(sizeof(char) * (len + 1));
			if (!ret[k])
				return (mem_free(ret, k - 1));
			j = 0;
			while (j < len)
				ret[k][j++] = s[i++];
			ret[k++][j] = '\0';
		}
		else
			i++;
	}
	ret[k] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_str((char *)s, c) + 1));
	if (!ret)
		return (NULL);
	ret = create_str((char *)s, c, ret);
	return (ret);
}
