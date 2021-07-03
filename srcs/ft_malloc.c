/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 18:30:46 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 20:29:32 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_malloc(void *pointer, size_t type_size, size_t n)
{
	*(void **)pointer = malloc(type_size * n);
	return (!*(void **)pointer);
}

int	ft_free(void *pointer)
{
	if ((void **)pointer == NULL)
		return (SUCCESS);
	free(*(void **)pointer);
	*(void **)pointer = NULL;
	return (SUCCESS);
}

int	ft_free_double_char(char ***pointer)
{
	char	**temp;

	if (pointer == NULL)
		return (SUCCESS);
	temp = *pointer;
	while (*temp)
		free(*(temp++));
	ft_free(pointer);
	return (SUCCESS);
}

int	ft_free_triple_char(char ****pointer)
{
	char	***temp;

	if (pointer == NULL)
		return (SUCCESS);
	temp = *pointer;
	while (*temp)
		ft_free_double_char(temp++);
	ft_free(pointer);
	return (SUCCESS);
}

int	expand_malloc(char **s, size_t cpy_n, size_t after_n)
{
	char	*temp;

	if (ft_malloc(&temp, sizeof(char), after_n))
		return (ERROR);
	ft_strcpy(temp, *s, cpy_n);
	ft_free(s);
	*s = temp;
	return (SUCCESS);
}
