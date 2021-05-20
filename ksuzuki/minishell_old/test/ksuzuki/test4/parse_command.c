/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:58:48 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:05:28 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**parse_command(char *buf)
{
	char	**command;

	command = ft_split(buf, ' ');
	if (command == NULL)
		process_error(ENOMEM, NULL, False);
	return (command);
}
