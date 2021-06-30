/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sorted_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 21:47:57 by tkano             #+#    #+#             */
/*   Updated: 2021/06/30 16:25:20 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_in_list(t_env *env, char *ret)
{
	int	i;
	int	j;

	i = 0;
	while (env && env->value != NULL)
	{
		j = 0;
		while (env->value[j])
		{
			ret[i] = env->value[j];
			i++;
			j++;
		}
		if (env->next != NULL)
			ret[i++] = '\n';
		env = env->next;
	}
	ret[i] = '\0';
}

char	*lst_to_env(t_env *env)
{
	char	*ret;

	ret = malloc(sizeof(char) * size_value(env) + 1);
	if (!ret)
		return (NULL);
	set_in_list(env, ret);
	return (ret);
}

void	sort_tab(char **tab, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tab && i == 0)
	{
		i = 1;
		j = 0;
		while (j < len - 1)
		{
			if (ft_strncmp(tab[j], tab[j + 1], ft_strlen(tab[j])) > 0)
			{
				tmp = tab [j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
				i = 0;
			}
			j++;
		}
		len--;
	}
}

int	put_env(char *tmp)
{
	char	env_key[BUFF_SIZE];
	char	*env_value;

	env_value = malloc(sizeof(char) * (env_value_len(tmp) + 1));
	if (!*env_value)
		return (ERROR);
	if (!env_value)
		return (ERROR);
	if (get_env_key(env_key, tmp) == NULL)
		return (ERROR);
	if (get_env_value(tmp, &env_value) == ERROR)
		return (ERROR);
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(env_key, 1);
	if (env_value[0] != '\0')
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env_value, 1);
		ft_putendl_fd("\"", 1);
	}
	else
		write(1, "\n", 1);
	ft_free(&env_value);
	return (SUCCESS);
}

int	put_sorted_env(t_env *env)
{
	int		i;
	char	**tmp;
	char	*str_env;

	str_env = lst_to_env(env);
	if (!str_env)
		return (ERROR);
	tmp = ft_split(str_env, '\n');
	ft_free(&str_env);
	if (!tmp)
		return (ERROR);
	sort_tab(tmp, tab_len(tmp));
	i = 0;
	while (tmp[i])
	{
		if (put_env(tmp[i]) == ERROR)
			return (ERROR);
		i++;
	}
	ft_free_double_char(&tmp);
	return (SUCCESS);
}
