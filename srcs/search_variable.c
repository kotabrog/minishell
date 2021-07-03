/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:34:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/30 21:15:33 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_variable_env(char **s, char *str, t_env *env, t_ex_flag *fl)
{
	char	*key;
	int		key_len;

	key_len = fl->end - fl->start - 1;
	fl->end -= 1;
	key = ft_strndup(str + fl->start + 1, key_len);
	if (key == NULL)
		return (ERROR);
	env_get_value(env, key, s);
	free(key);
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
