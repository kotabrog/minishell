/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 10:30:40 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/27 21:01:02 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha_underbar(int c)
{
	return (ft_isalpha(c) || c == '_');
}

int	ft_isalnum_underbar(int c)
{
	return (ft_isalnum(c) || c == '_');
}

int ft_ischr(const char *s1, const char c)
{
	while (*s1)
	{
		if (*s1 == c)
			return (1);
		++s1;
	}
	return (0);
}
