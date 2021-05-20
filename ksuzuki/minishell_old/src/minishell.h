/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:53:33 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/23 21:27:40 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define True 1
# define False 0
# define SUCCESS 0
# define ERROR 1
# define READ_SIZE 1024
# define DICT_ALLOCATE_SIZE 16

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# include <stdio.h>

typedef struct	s_item {
	char	*key;
	char	*value;
}				t_item;

typedef struct	s_dict {
	t_item	*items;
	size_t	len;
	size_t	allocated_len;
}				t_dict;



void			ft_strcpy(char *p, char const *s, size_t n);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);

char			**ft_split(char const *s, char c);

void			process_error(int err_num, char *command, int exit_flag);

char			**parse_command(char *buf);

char			**read_parse_command(int fd);

void			free_double_pointer(char **s);




#endif
