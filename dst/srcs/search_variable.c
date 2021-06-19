/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:34:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/06 23:14:39 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_variable_env(char **s, char *str, char **env, t_ex_flag *fl)
{
	*s = NULL;
	str++;
	env++;
	fl->end -= 1;
	return (SUCCESS);
}

int	search_variable(char **buf, char *str, t_ex_flag *fl, t_status *status)
{
	int		flag;
	char	*s;
	char	*temp;

	flag = SUCCESS;
	if (str[fl->start + 1] == '?')
		s = ft_itoa(status->exit);
	else if (!ft_isalpha_underbar(str[fl->start + 1]))
		s = "$";
	else
	{
		flag = search_variable_env(&s, str, status->env, fl);
		if (flag == SUCCESS && s == NULL)
			return (SUCCESS);
	}
	if (flag || s == NULL)
		return (ERROR);
	temp = ft_strjoin(*buf, s);
	ft_free(buf);
	if (str[fl->start + 1] == '?')
		free(s);
	else if (!ft_isalpha_underbar(str[fl->start + 1]))
		fl->end -= 1;
	*buf = temp;
	return (temp == NULL);
}
