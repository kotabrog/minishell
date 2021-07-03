/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 07:12:39 by tkano             #+#    #+#             */
/*   Updated: 2021/05/10 00:29:49 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		len;
	int		flag;
	char	*ret;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_length(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	flag = 0;
	if (n < 0)
	{
		n *= -1;
		flag = 1;
	}
	while (len--)
	{
		ret[len] = n % 10 + '0';
		n = n / 10;
	}
	if (flag == 1)
		ret[0] = '-';
	return (ret);
}
