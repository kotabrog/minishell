/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 11:55:44 by tkano             #+#    #+#             */
/*   Updated: 2021/05/10 00:31:41 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	sublen;
	unsigned int	i;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s) || len <= 0)
		return (ft_strdup(""));
	sublen = ft_strlen(&s[start]);
	if (sublen >= len)
		sublen = len;
	ret = malloc(sizeof(char) * (sublen + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (sublen > i && s[start + i])
	{
		ret[i] = s[i + start];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
