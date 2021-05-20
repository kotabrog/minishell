/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:54:43 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/21 00:20:20 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *p, char const *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		p[i] = s[i];
		i++;
	}
}

int		ft_isspace(int c)
{
	return (c == ' ' || c == '\f' || c == '\n' \
		|| c == '\r' || c == '\t' || c == '\v');
}

int		extension_array(char **array, int before_size, int extension_size)
{
	char *temp_array;

	temp_array = (char *)malloc(sizeof(char) * (before_size + extension_size));
	if (temp_array == NULL)
		return (ERROR);
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
		return (ERROR);
	buf_end_pointer = *buf;
	while ((n = read(fd, buf_end_pointer, READ_SIZE)) == READ_SIZE)
	{
		if (extension_array(buf, buf_size, READ_SIZE) == -1)
			return (ERROR);
		buf_end_pointer = *buf + buf_size - 1;
		buf_size += READ_SIZE;
	}
	if (n < 0)
		return (ERROR);
	(*buf)[buf_size - READ_SIZE + n - 2] = '\0';
	return (SUCCESS);
}

char	**parse_command(char *buf)
{
	return (ft_split(buf, ' '));
}

int		put_buf(char *str)
{
	printf("%s\n", str);
}

int		put_command(char **command)
{
	while (*command)
		printf("%s\n", *command++);
}

void	put_error(int point)
{
	printf("%d\n", point);
	exit(1);
}

void	free_double_pointer(char **s)
{
	char **p;

	p = s;
	while (*s)
		free(*s++);
	free(p);
}

int		loop_shell()
{
	char *buf;
	char **command;

	while (True)
	{
		if (read_single_line(0, &buf))
		{
			free(buf);
			put_error(1);
		}
		if ((command = parse_command(buf)) == NULL)
		{
			free(buf);
			put_error(2);
		}
		put_command(command);
		free(buf);
		free_double_pointer(command);
	}
}

int		main()
{
	loop_shell();
}

// readで読み込んだ最後には改行がいる
// commandのパースは、とりあえずスペース' 'だけ対象にしている。
