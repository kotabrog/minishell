/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkano <tkano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 23:33:23 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/30 16:30:56 by tkano            ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>
# include <limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>

# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1
# define READ 0
# define WRITE 1
# define STDERR 2
# define HEARDOC 1147483647
# define HEARDOC_NON_EX 1147483648

# define BUFF_SIZE 2048
# define MAX_FD 256

# define SEMICOLON 1
# define PIPE 2

# define SINGLE_QUOT 1
# define DOUBLE_QUOT 2
# define QUOT_FLAG 1
# define QUOT_DUMMY_DOUBLE 2
# define QUOT_DUMMY_SINGLE 3

# define ERROR_NOT_FOUND -2
# define ERROR_AMB_REDIRECT -3
# define ERROR_TOKEN_LEFT -4
# define ERROR_TOKEN_RIGHT -5
# define ERROR_TOKEN_COLON -6
# define ERROR_TOKEN_PIPE -7
# define ERROR_TOKEN_NEWLINE -8
# define ERROR_MULTILINE -9
# define ERROR_ARGMENT -10
# define ERROR_EXIT_NUM -11
# define ERROR_EXIT_MANY -12
# define ERROR_PERMISSION -13
# define ERROR_IS_DIR -14
# define IN_VALID_ENV -15
# define NO_SET_HOME -16
# define NO_SET_OLD -17
# define NO_DIR -18
# define ERROR_IS_FILE -19

# define SIGNAL_VALUE 128

typedef struct s_command {
	char	**s;
	char	**file;
	int		*fd;
	int		flag;
	int		pipefd[2];
	int		pid[2];
}			t_command;

typedef struct s_tree {
	t_command		*command;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_env {
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_status {
	t_tree		*tree;
	t_env		*env;
	int			exit;
}				t_status;

typedef struct s_global {
	int		signal_flag;
	t_tree	*tree;
	int		exit_pid;
}				t_global;

typedef struct s_ex_flag {
	int	start;
	int	end;
	int	quote;
	int	var;
}				t_ex_flag;

extern t_global		*g_signal;

int			read_parse_command(t_status *status, t_tree **tree);
int			read_input(char **s, t_status *status);
int			read_command_split(char ***split, char *s);
int			read_command(char **split, t_command *com, int *id);
int			read_command2tree(t_tree **root, char **split);

int			process_tree(t_status *status, t_tree *tree);
int			process_pipe(t_status *status, t_tree *tree, \
		int parentfd[2]);
int			process_command(t_status *status, t_tree *tree, int parent[2], \
		int fork_flag);
void		all_command_close(t_tree *tree);
int			search_execve(char **com, t_env *env);
int			make_env_array(t_env *env, char ***env_array);

void		redirect_init(int fd[3], int fork_flag);
int			redirect_set(int fd[3], char **file, int *tofd, int fork_flag);
int			redirect_close(int fd[3], int flag, int fork_flag);

int			hear_document(t_status *status, t_tree *tree, int flag);
int			heardoc_before_expansion(char **file, int *fd);
int			heardoc_after_expansion(char **file, int *fd);
int			heardoc_redirect(char *file);
void		heardoc_handler(int signum);
int			heardoc_event_hook(void);

int			set_signal(int mode);
t_global	*signal_init(void);
void		signal_reset(void);

int			set_exit_status(t_status *status, int flag);
int			status_value_conversion(int flag);
int			wait_conversion(int flag);

int			variable_expansion_all(t_status *status, t_command *com);
int			expansion_sentence(char *str, char **dst, t_status *status);
int			expansion_split(char *s, char ***dst);
int			search_variable(char **buf, char *str, t_ex_flag *fl, \
	t_status *status);

int			builtin_exit(t_status *status, t_command *com, int fork_flag);
int			builtin_echo(t_command *com);

int			command_init(t_command **command, int flag);
int			command_free(t_command **command);
int			command_dup(t_command *command);

int			tree_init(t_tree **tree, int flag);
int			tree_free(t_tree **tree);
int			tree_add(t_tree *tree, int flag, int is_right);
int			tree_add_parent(t_tree **tree, int flag, int is_right);

int			status_init(t_status **status, char **envp);
int			status_turn_finish(t_status *status);
int			status_finish(t_status *status);

void		error_if(int flag, int err_num, char *command, int exit_flag);
void		error_process(int err_num, char *command, int exit_flag);
int			error_put(int err_num, char *command);
int			error_put2(int err_num, char *com1, char *com2);
char		*error_make_massage(int n);
int			error_file(int error, int exe_flag, char *s);
int			error_file2(int error, char *com, char *arg);
int			file_status_check(char *file);

int			ft_malloc(void *pointer, size_t type_size, size_t n);
int			ft_free(void *pointer);
int			expand_malloc(char **s, size_t cpy_n, size_t after_n);
int			ft_free_double_char(char ***pointer);
int			ft_free_triple_char(char ****pointer);

int			ft_close(int *fd);
int			multi_close(int *fd1, int *fd2, int *fd3, int *fd4);

int			get_wait_status(int status);

void		ft_strcpy(char *p, const char *s, size_t n);
int			ft_strlen_ex(char **s);
int			ft_isspace(const char c);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_strdup_ex(char **s);
char		*ft_strndup(const char *s, ssize_t n);
int			ft_strndup_ex(char **dest, const char *s, ssize_t n);
int			ft_isalpha_underbar(int c);
int			ft_isalnum_underbar(int c);

int			env_init(t_env **env);
int			env_init_from_str(t_env **env, char *str);
int			env_free(t_env **env);
int			env_all_free(t_env **env);
int			env_get_key_str(char **dest, char *str);
int			env_get_value_str(char **dest, char *str, int key_len);
t_env		*env_search_key(t_env *env, char *key);
int			env_get_value(t_env *env, char *key, char **dest);
int			env_len(t_env *env);
int			env_add(char *key, char *value, t_env **env);
void		env_change(char *key, char *value, t_env *env);

int			env_set(t_env **env, char **envp);
int			do_env(t_env *env);
int			do_export(char **command, t_env **env);
int			put_sorted_env(t_env *env);
int			do_unset(char **command, t_env **env);
int			do_pwd(void);
int			do_cd(char **command, t_env *env);

#endif
