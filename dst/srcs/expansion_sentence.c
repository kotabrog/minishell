/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_sentence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:49:19 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/06 23:44:30 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expansion_delete_quote2(char temp[3], int flag[2], \
	char *str, t_ex_flag *fl)
{
	flag[0] = ((fl->quote == SINGLE_QUOT && str[fl->start] == '\'') || \
		(fl->quote == DOUBLE_QUOT && str[fl->start] == '"'));
	flag[1] = ((fl->quote == SINGLE_QUOT && str[fl->end] == '\'') || \
		(fl->quote == DOUBLE_QUOT && str[fl->end] == '"'));
	if (flag[0])
	{
		temp[0] = str[fl->start];
		str[fl->start] = QUOT_FLAG;
	}
	temp[1] = str[fl->end + flag[1]];
	str[fl->end + flag[1]] = 0;
	if (flag[1])
	{
		temp[2] = str[fl->end];
		str[fl->end] = QUOT_FLAG;
	}
}

static int	expansion_delete_quote(char **buf, char *str, t_ex_flag *fl)
{
	char	temp[3];
	char	*s;
	int		flag[2];

	expansion_delete_quote2(temp, flag, str, fl);
	s = ft_strjoin(*buf, &(str[fl->start]));
	ft_free(buf);
	if (s == NULL)
		return (ERROR);
	*buf = s;
	if (flag[0])
		str[fl->start] = temp[0];
	str[fl->end + flag[1]] = temp[1];
	if (flag[1])
	{
		str[fl->end] = temp[2];
		fl->quote = FALSE;
	}
	else
		fl->end -= 1;
	return (SUCCESS);
}

static int	expansion_word(char **buf, char *str, t_ex_flag *fl, \
	t_status *status)
{
	int	flag;

	if (fl->var)
	{
		flag = search_variable(buf, str, fl, status);
		fl->var = FALSE;
	}
	else
		flag = expansion_delete_quote(buf, str, fl);
	fl->start = fl->end + 1;
	return (flag);
}

static int	expansion_loop(char *str, char **dst, t_status *status, \
	t_ex_flag *fl)
{
	int	flag;

	flag = SUCCESS;
	while (flag == SUCCESS && str[++(fl->end)])
	{
		if ((fl->var && ((fl->start + 1 == fl->end && \
					!ft_isalpha_underbar(str[fl->end])) || \
					!ft_isalnum_underbar(str[fl->end]))) || \
				(fl->quote == SINGLE_QUOT && str[fl->end] == '\'') || \
				(fl->quote == DOUBLE_QUOT && str[fl->end] == '\"') || \
				(fl->start != fl->end && !fl->quote && !fl->var && \
					(str[fl->end] == '\'' || str[fl->end] == '\"')) || \
				(fl->start != fl->end && fl->quote != SINGLE_QUOT && \
					str[fl->end] == '$'))
			flag = expansion_word(dst, str, fl, status);
		else if (!fl->quote && str[fl->end] == '"')
			fl->quote = DOUBLE_QUOT;
		else if (!fl->quote && str[fl->end] == '\'')
			fl->quote = SINGLE_QUOT;
		else if (fl->quote != SINGLE_QUOT && str[fl->end] == '$')
			fl->var = TRUE;
	}
	if (flag == SUCCESS && fl->end != fl->start)
		flag = expansion_word(dst, str, fl, status);
	return (flag);
}

int	expansion_sentence(char *str, char **dst, t_status *status)
{
	t_ex_flag	*fl;
	int			flag;

	if (ft_malloc(&fl, sizeof(t_ex_flag), 1))
		return (ERROR);
	fl->start = 0;
	fl->end = -1;
	fl->quote = FALSE;
	fl->var = FALSE;
	if (ft_malloc(dst, sizeof(char), 1))
	{
		free(fl);
		return (ERROR);
	}
	(*dst)[0] = 0;
	flag = expansion_loop(str, dst, status, fl);
	free(fl);
	return (flag);
}
