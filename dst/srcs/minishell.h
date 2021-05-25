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
# include <string.h>
# include <sys/wait.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1
# define READ 0
# define WRITE 1

# define BUFF_SIZE 1024
# define MAX_FD 256

# define SEMICOLON 1
# define PIPE 2

# define ERROR_NOT_FOUND -2
# define ERROR_AMB_REDIRECT -3
# define ERROR_TOKEN_LEFT -4
# define ERROR_TOKEN_RIGHT -5
# define ERROR_TOKEN_COLON -6
# define ERROR_TOKEN_PIPE -7
# define ERROR_TOKEN_NEWLINE -8
# define ERROR_MULTILINE -9

typedef struct s_command {
	char	**s;
	char	**file;
	int		*fd;
	int		pipefd[2];
	int		flag;
}			t_command;

typedef struct s_tree {
	t_command		*command;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

int		read_input(char **s, char **memo);
int		read_command_split(char ***split, char *s);
int		read_command(char **split, t_command *com, int *id);
int		read_command2tree(t_tree **root, char **split);

int		command_init(t_command **command, int flag);
int		command_free(t_command **command);
int		command_dup(t_command *command);

int		tree_init(t_tree **tree, int flag);
int		tree_free(t_tree **tree);
int		tree_add(t_tree *tree, int flag, int is_right);
int		tree_add_parent(t_tree **tree, int flag, int is_right);

void	error_if(int flag, int err_num, char *command, int exit_flag);
void	error_process(int err_num, char *command, int exit_flag);
int		error_put(int err_num, char *command);
char	*error_make_massage(int n);

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);
int		expand_malloc(char **s, size_t cpy_n, size_t after_n);
int		ft_free_double_char(char ***pointer);

void	ft_strcpy(char *p, const char *s, size_t n);
int		ft_strlen_ex(char **s);
char	**ft_strdup_ex(char **s);
char	*ft_strndup(const char *s, ssize_t n);
int		ft_strndup_ex(char **dest, const char *s, ssize_t n);
int		ft_isspace(const char c);
int		ft_strcmp(const char *s1, const char *s2);

void	debug_print_split(char *s, char **split);
void	debug_command(t_command *command);
void	debug_tree(t_tree *tree);

#endif
