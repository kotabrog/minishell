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

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# include <stdio.h>

# define True 1
# define False 0
# define SUCCESS 0
# define ERROR 1
# define READ_SIZE 1024
# define DICT_ALLOCATE_SIZE 16
# define COMMAND_ALLOCATE_SIZE 16
# define SEMICOLON 0b1
# define SINGLE_QUOTE 0b10
# define DOUBLE_QUOTE 0b100
# define LEFT 0b1000
# define RIGHT 0b10000
# define RRIGHT 0b100000
# define PIPE 0b1000000
# define DOLLAR 0b10000000


typedef struct	s_item {
	char	*key;
	char	*value;
}				t_item;

typedef struct	s_dict {
	t_item	*items;
	size_t	len;
	size_t	allocated_len;
}				t_dict;

typedef struct	s_command {
	char	**command;
	int		*symbol;
	size_t	len;
	size_t	allocated_len;
}				t_command;

typedef struct	s_status {
	t_dict		*env;
	t_command	*command;
}				t_status;

void			ft_strcpy(char *p, char const *s, size_t n);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, size_t n);
char			*ft_strjoin_ex(char *s1, char *s2, ssize_t n1, ssize_t n2);

char			**ft_split(char const *s, char c);

void			process_error(int err_num, char *command, int exit_flag);
void			if_error(int flag, int err_num, char *command, int exit_flag);


int		parse_command(char *buf, t_command *command);

int				read_parse_command(t_status *status, int fd);

void			free_double_pointer(char **s);

int				dict_init(t_dict **dic, int allocate_num);
void			dict_free(t_dict *dic);
char			*dict_get(t_dict *dic, char *key);
int				dict_set(t_dict *dic, char *key, char *value);

int				init_env(t_status *status);

void			init_status(t_status **status);
void			free_status(t_status *status);

#endif
