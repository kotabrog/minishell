/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:56:25 by tkano             #+#    #+#             */
/*   Updated: 2020/11/18 07:13:58 by tkano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*p;

	if (lst == NULL || (*del) == NULL)
		return ;
	p = *lst;
	while (p != NULL)
	{
		tmp = p->next;
		(*del)(p->content);
		free(p);
		p = tmp;
	}
	*lst = NULL;
}
