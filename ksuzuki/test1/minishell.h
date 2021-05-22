/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:33:23 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/21 21:35:27 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/wait.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1

# define BUFF_SIZE 1024

int		read_input(char **s, char **memo);
int		read_command_split(char ***split, char *s);

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);
int		expand_malloc(char **s, size_t cpy_n, size_t after_n);
int		ft_free_double_char(char ***pointer);

void	ft_strcpy(char *p, const char *s, size_t n);
char	*ft_strndup(const char *s, ssize_t n);
int		ft_strndup_ex(char **dest, const char *s, ssize_t n);
int		ft_isspace(const char c);

size_t	ft_strlen(const char *c);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
