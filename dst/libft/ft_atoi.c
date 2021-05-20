/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:18:51 by tkano             #+#    #+#             */
/*   Updated: 2021/05/10 00:39:09 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(long long num)
{
	if (num > 2147483647 && num < 9223372036854775807L)
		return (0);
	else if (num < -2147483648 && num >= -9223372036854775807L)
		return (-1);
	if (num >= 9223372036854775807L)
		return (-1);
	else if (num < -9223372036854775807L)
		return (0);
	else
		return (num);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	num;
	int			flag;

	i = 0;
	num = 0;
	flag = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		flag *= -1;
		i++;
	}
	while ((str[i] <= '9' && str[i] >= '0'))
	{
		num *= 10;
		num += (str[i] - '0');
		i++;
	}
	num = ft_check(num * flag);
	return (num);
}
