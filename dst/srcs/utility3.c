/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 10:30:40 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/19 10:32:52 by ksuzuki          ###   ########.fr       */
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
