/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 19:03:51 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 19:31:37 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dict_extend_allocated(t_dict *dic)
{
	t_item	*temp_items;
	int		i;

	temp_items = (t_item *)malloc(\
		sizeof(t_item) * (dic->allocated_len + DICT_ALLOCATE_SIZE));
	if (temp_items == NULL)
		return (ERROR);
	i = 0;
	while (i < dic->len)
	{
		temp_items[i] = dic->items[i];
		++i;
	}
	dic->allocated_len += DICT_ALLOCATE_SIZE;
	return (SUCCESS);
}

int		dict_add_item(t_dict *dic, char *key, char *value)
{
	if (dic->allocated_len == dic->len)
		if (dict_extend_allocated(dic))
			return (ERROR);
	dic->items[dic->len].key = ft_strdup(key);
	if (dic->items[dic->len].key == NULL)
		return (ERROR);
	dic->items[dic->len].value = ft_strdup(value);
	if (dic->items[dic->len].value == NULL)
	{
		free(dic->items[dic->len].key);
		return (ERROR);
	}
	++(dic->len);
	return (SUCCESS);
}

int		item_update_value(t_item *item, char *value)
{
	char *temp;

	temp = ft_strdup(value);
	if (temp == NULL)
		return (ERROR);
	free(item->value);
	item->value = temp;
	return (SUCCESS);
}

int		dict_search_key(t_dict *dic, char *key)
{
	int i;

	i = 0;
	while (i < dic->len)
	{
		if (!ft_strcmp(key, dic->items[i].key))
			break ;
		++i;
	}
	if (i == dic->len)
		return (-1);
	return (i);
}

int		dict_set(t_dict *dic, char *key, char *value)
{
	int index;

	index = dict_search_key(dic, key);
	if (index == -1)
		return (dict_add_item(dic, key, value));
	return (item_update_value(&(dic->items[index]), value));
}

char	*dict_get(t_dict *dic, char *key)
{
	int index;

	index = dict_search_key(dic, key);
	if (index == -1)
		return (NULL);
	return (dic->items[index].value);
}

void	dict_free(t_dict *dic)
{
	int i;

	i = 0;
	while (i < dic->len)
	{
		free(dic->items[i].key);
		free(dic->items[i].value);
		++i;
	}
	free(dic->items);
	free(dic);
}

int		dict_init(t_dict **dic, int allocate_num)
{
	*dic = (t_dict *)malloc(sizeof(t_dict));
	if (*dic == NULL)
		return (ERROR);
	(*dic)->items = (t_item *)malloc(sizeof(t_item) * allocate_num);
	if ((*dic)->items == NULL)
	{
		free(*dic);
		return (ERROR);
	}
	(*dic)->allocated_len = allocate_num;
	(*dic)->len = 0;
	return (SUCCESS);
}
