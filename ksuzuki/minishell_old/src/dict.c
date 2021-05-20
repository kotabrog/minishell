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

int		dict_add_item(t_dict *dic, char *kye, char *value)
{
	
}



int		dict_init(t_dict *dic)
{
	dic = (t_dict *)malloc(sizeof(t_dict));
	if (dic == NULL)
		return (ERROR);
	dic->items = (t_item *)malloc(sizeof(t_item) * DICT_ALLOCATE_SIZE);
	if (dic->items == NULL)
	{
		free(dic);
		return (ERROR);
	}
	dic->allocated_len = DICT_ALLOCATE_SIZE;
	dic->len = 0;
	return (SUCCESS);
}
