/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:51:19 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/28 20:51:38 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close(int *fd)
{
	close(*fd);
	*fd = -1;
	return (SUCCESS);
}

int	multi_close(int *fd1, int *fd2, int *fd3, int *fd4)
{
	if (fd1 != NULL && *fd1 != -1)
		ft_close(fd1);
	if (fd2 != NULL && *fd2 != -1)
		ft_close(fd2);
	if (fd3 != NULL && *fd3 != -1)
		ft_close(fd3);
	if (fd4 != NULL && *fd4 != -1)
		ft_close(fd4);
	return (SUCCESS);
}
