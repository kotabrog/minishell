/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utility2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 18:48:49 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/02 02:07:11 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_get_key_str(char **dest, char *str)
{
	int	i;

	i = 1;
	*dest = NULL;
	if (str == NULL)
		return (ERROR);
	if (!ft_isalpha_underbar(str[0]))
		return (IN_VALID_ENV);
	while (ft_isalnum_underbar(str[i]))
		++i;
	if (str[i] != '\0' && str[i] != '=')
		return (IN_VALID_ENV);
	*dest = ft_strndup(str, i);
	if (*dest == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	env_get_value_str(char **dest, char *str, int key_len)
{
	*dest = NULL;
	str += key_len;
	if (str[0] == '\0')
		return (SUCCESS);
	if (str[0] != '=')
		return (ERROR);
	*dest = ft_strdup(str + 1);
	if (*dest == NULL)
		return (ERROR);
	return (SUCCESS);
}

t_env	*env_search_key(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	env_get_value(t_env *env, char *key, char **dest)
{
	*dest = NULL;
	env = env_search_key(env, key);
	if (env == NULL)
		return (FALSE);
	*dest = env->value;
	return (TRUE);
}
