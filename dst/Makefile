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

SRCS	= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I./libft
NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(OBJS)
			$(MAKE) -C ./libft
			$(CC) $(CFLAGS) $(OBJS) -L./libft/ -lft -o $(NAME)

sani	:	$(OBJS)
		$(MAKE) -C ./libft
		$(CC) $(CFLAGS) -fsanitize=address $(OBJS) -L./libft/ -lft -o $(NAME)

clean	:
			$(MAKE) clean -C ./libft
			$(RM) $(OBJS)

fclean	:
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME) $(OBJS)

re		: fclean all

.PHONY	: all clean fclean re
