/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 12:50:04 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 13:06:29 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		extension_array(char **array, int before_size, int extension_size)
{
	char *temp_array;

	temp_array = (char *)malloc(sizeof(char) * (before_size + extension_size));
	if (temp_array == NULL)
		return (errno);
	ft_strcpy(temp_array, *array, before_size);
	free(*array);
	*array = temp_array;
	return (SUCCESS);
}

int		read_single_line(int fd, char **buf)
{
	ssize_t	n;
	ssize_t	buf_size;
	char	*buf_end_pointer;

	buf_size = READ_SIZE + 1;
	*buf = (char *)malloc(sizeof(char) * buf_size);
	if (*buf == NULL)
		return (errno);
	buf_end_pointer = *buf;
	while ((n = read(fd, buf_end_pointer, READ_SIZE)) == READ_SIZE)
	{
		if (extension_array(buf, buf_size, READ_SIZE))
			return (errno);
		buf_end_pointer = *buf + buf_size - 1;
		buf_size += READ_SIZE;
	}
	if (n < 0)
		return (errno);
	(*buf)[buf_size - READ_SIZE + n - 2] = '\0';
	return (SUCCESS);
}

char	**read_parse_command(int fd)
{
	char	*buf;
	char	**command;
	int		err_num;

	if (err_num = read_single_line(0, &buf))
		process_error(err_num, NULL, False);
	if (!err_num)
		command = parse_command(buf);
	free(buf);
	return (command);
}
