SRCDIR	= ./srcs/
SRCNAME	=	command_utility1.c\
			debug.c\
			error.c\
			ft_malloc.c\
			main.c\
			read_command2tree1.c\
			read_command2tree2.c\
			read_command_split.c\
			read_input.c\
			tree_utility1.c\
			utility1.c\
			utility2.c\
			status_utility.c\
			process_tree.c\
			process_pipe.c\
			process_command.c\
			ft_close.c\
			signal.c\
			redirect.c\
			read_parse_command.c\
			exit_status.c\
			exit.c\
			echo.c\
			expansion_sentence.c\
			expansion_split.c\
			expansion_variable.c\
			search_variable.c\
			error_file.c\
			search_execve.c\
			signal_delete.c

SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I./libft -I$(shell brew --prefix readline)/include
LDFLAGS = -L./libft/ -lft -L$(shell brew --prefix readline)/lib -lreadline -lhistory
NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(OBJS)
			$(MAKE) -C ./libft
			$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

sani	:	$(OBJS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -fsanitize=address $(OBJS) $(LDFLAGS) -o $(NAME)

clean	:
			$(MAKE) clean -C ./libft
			$(RM) $(OBJS)

fclean	:
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME) $(OBJS)

re		: fclean all

.PHONY	: all clean fclean re
