/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hear_doc_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 23:05:16 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/13 23:34:59 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heardoc_set(char **file, int *fd, char *quot)
{
	char	*temp;
	int		flag;
	int		i;

	flag = QUOT_DUMMY_DOUBLE;
	if (*quot == '\'')
		flag = QUOT_DUMMY_SINGLE;
	i = -1;
	while ((*file)[++i])
		if ((*file)[i] == *quot)
			(*file)[i] = flag;
	temp = ft_strjoin(quot, *file);
	if (temp == NULL)
		return (ERROR);
	free(*file);
	*file = temp;
	temp = ft_strjoin(*file, quot);
	if (temp == NULL)
		return (ERROR);
	free(*file);
	*file = temp;
	*fd = HEARDOC;
	return (SUCCESS);
}

int	heardoc_before_expansion(char **file, int *fd)
{
	int	i;
	int	flag = 0;

	i = 0;
	flag = 0;
	while (!flag && file[i])
	{
		if (fd[i] == HEARDOC)
			flag = heardoc_set(&(file[i]), &(fd[i]), "\"");
		else if (fd[i] == HEARDOC_NON_EX)
			flag = heardoc_set(&(file[i]), &(fd[i]), "'");
		++i;
	}
	return (flag);
}

static int	heardoc_reset(char **file)
{
	char	*temp;
	int		i;

	i = ft_strlen(*file);
	temp = ft_strndup(&((*file)[1]), i - 2);
	if (temp == NULL)
		return (ERROR);
	free(*file);
	*file = temp;
	i = 0;
	while ((*file)[i])
	{
		if ((*file)[i] == QUOT_DUMMY_DOUBLE)
			(*file)[i] = '"';
		if ((*file)[i] == QUOT_DUMMY_SINGLE)
			(*file)[i] = '\'';
		++i;
	}
	return (SUCCESS);
}

int	heardoc_after_expansion(char **file, int *fd)
{
	int	i;
	int	flag = 0;

	i = 0;
	flag = 0;
	while (!flag && file[i])
	{
		if (fd[i] == HEARDOC)
			flag = heardoc_reset(&(file[i]));
		++i;
	}
	return (flag);
}