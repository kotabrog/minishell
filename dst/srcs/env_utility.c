/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 18:33:43 by tkano             #+#    #+#             */
/*   Updated: 2021/06/25 18:33:56 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	size_value(t_env *env)
{
	size_t	ret;

	ret = 0;
	while (env && env->next != NULL)
	{
		if (env->value != NULL)
		{
			ret += ft_strlen(env->value);
			ret++;
		}
		env = env->next;
	}
	return (ret);
}

int	tab_len(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	check_ex_arg(const char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[i]) == FALSE)
		return (IN_VALID_ENV);
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
			return (IN_VALID_ENV);
		i++;
	}
	if (arg[i] != '=')
		return (2);
	return (1);
}

char	*get_env_key(char *dest, const char *src)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(src);
	if (len >= BUFF_SIZE)
		return (NULL);
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
