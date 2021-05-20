/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:14:49 by tkano             #+#    #+#             */
/*   Updated: 2020/11/16 23:30:27 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;
	unsigned char		cc;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	cc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		if (s[i] == cc)
		{
			return (&d[i + 1]);
		}
		i++;
	}
	return (NULL);
}
