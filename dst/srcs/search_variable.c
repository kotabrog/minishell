/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:34:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/29 23:51:25 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_value_len(const char *env)
{
	int	i;
	int	len_value;

	len_value = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		len_value++;
	}
	return (len_value);
}

int	get_env_value(char *env, char **env_value)
{
	int		i;
	int		j;
	int		len_value;

	len_value = env_value_len(env);
	*env_value = malloc(sizeof(char*) * (len_value + 1));
	if (!*env_value)
		return (ERROR);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		*(env_value[j++]) = env[i++];
	*(env_value[j]) = '\0';
	return (SUCCESS);
}

static int	get_variable_value(char **s, char *var_key, t_env *env)
{
	char	env_key[BUFF_SIZE];

	while (env && env->value)
	{
		if (!get_env_key(env_key, env->value))
			return (ERROR);
		if (strcmp(var_key, env_key) == 0)
		{
			if (get_env_value(env->value, s) == ERROR)
				return (ERROR);
		}
		env = env->next;
	}
	return (SUCCESS);
}

static int	search_variable_env(char **s, char *str, t_env *env, t_ex_flag *fl)
{
	char	var_key[BUFF_SIZE];
	int		i;

	if (fl->end > BUFF_SIZE)
		return (ERROR);
	*s = ft_strdup("");
	if (*s == NULL)
		return (ERROR);
	i = 0;
	while (i < fl->end - 1 && ft_isalnum_underbar(str[fl->start + 1 + 1]))
	{
		var_key[i] = str[fl->start + 1 + i];
		i++;
	}
	var_key[i] = '\0';
	if (get_variable_value(s, var_key, env) == ERROR)
		return (ERROR);
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
		flag = search_variable_env(&s, str, status->env_tab, fl);
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
