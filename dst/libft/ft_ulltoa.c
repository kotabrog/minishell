/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:06:50 by tkano             #+#    #+#             */
/*   Updated: 2021/05/10 00:18:28 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(unsigned long long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (0 < n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_ulltoa(unsigned long long n)
{
	char	*ret;
	int		len;

	len = ft_length(n);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	if (n == 0)
		ret[--len] = '0';
	while (0 < n)
	{
		ret[--len] = n % 10 + '0';
		n /= 10;
	}
	return (ret);
}
