/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:21:01 by tkano             #+#    #+#             */
/*   Updated: 2021/05/10 00:17:24 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	if (needle[cnt] == '\0')
		return ((char *)(haystack));
	while (haystack[cnt] != '\0' && cnt < len)
	{
		i = 0;
		while (needle[i] == haystack[cnt + i] && cnt + i < len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)(haystack + cnt));
		}
		cnt++;
	}
	return (NULL);
}
