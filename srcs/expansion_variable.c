/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 23:43:58 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/06 23:50:13 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expansion_one(char *str, char ***dst, t_status *status, \
	int file_flag)
{
	char	*s;
	int		flag;

	*dst = NULL;
	if (expansion_sentence(str, &s, status))
		return (ERROR);
	flag = expansion_split(s, dst);
	free(s);
	if (flag == ERROR)
	{
		ft_free_double_char(dst);
		return (flag);
	}
	if (file_flag && flag != 1)
	{
		ft_free_double_char(dst);
		error_put(ERROR_AMB_REDIRECT, str);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	multi_to_single_count(char ***dst)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	n = 0;
	while (dst[i])
	{
		j = 0;
		while (dst[i][j])
		{
			if (dst[i][j][0])
				++n;
			++j;
		}
		++i;
	}
	return (n);
}

static int	multi_to_single(char ***target, char ***dst)
{
	int		i;
	int		j;
	char	**temp;
	int		n;
	int		index;

	i = 0;
	index = 0;
	n = multi_to_single_count(dst);
	if (ft_malloc(&temp, sizeof(char *), n + 1))
		return (ERROR);
	temp[n] = NULL;
	while (dst[i])
	{
		j = -1;
		while (dst[i][++j])
			if (dst[i][j][0])
				temp[index++] = dst[i][j];
		free(dst[i++]);
	}
	ft_free_double_char(target);
	*target = temp;
	return (SUCCESS);
}

static int	variable_expansion(char ***target, int file_flag, t_status *status)
{
	char	***dst;
	int		flag;
	int		target_len;
	int		i;

	flag = SUCCESS;
	target_len = ft_strlen_ex(*target);
	if (target_len <= 0)
		return (SUCCESS);
	if (ft_malloc(&dst, sizeof(char **), target_len + 1))
		return (errno);
	dst[target_len] = NULL;
	i = 0;
	while (flag == SUCCESS && i < target_len)
	{
		flag = expansion_one((*target)[i], &(dst[i]), status, file_flag);
		++i;
	}
	if (flag)
		ft_free_triple_char(&dst);
	else
		flag = multi_to_single(target, dst);
	free(dst);
	return (status_value_conversion(flag));
}

int	variable_expansion_all(t_status *status, t_command *com)
{
	int	flag;

	if (heardoc_before_expansion(com->file, com->fd))
		return (ERROR);
	flag = variable_expansion(&(com->file), TRUE, status);
	if (flag)
		return (flag);
	if (heardoc_after_expansion(com->file, com->fd))
		return (ERROR);
	return (variable_expansion(&(com->s), FALSE, status));
}
