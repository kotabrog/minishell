/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 19:21:44 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/12 22:48:33 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_window_size(void)
{
	struct winsize	ws;

	if (ioctl(1, TIOCGWINSZ, &ws) == -1)
		return (ERROR);
	return (ws.ws_col);
}

static void	get_cursol_point(int *col, int *row, int *flag)
{
	int	return_col;

	*row = (11 + rl_end) / *col;
	return_col = (11 + rl_end) % *col;
	if (return_col + 1 == *col)
		*flag = 1;
	else
		*flag = 0;
	*col = return_col;
}

static int	join_and_free(char **dst, char *s1, char *s2, char *free_s)
{
	*dst = ft_strjoin(s1, s2);
	free(free_s);
	if (*dst == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	make_delete_sentence(int col, int row, char *s)
{
	char	*num;
	char	*temp;

	num = ft_itoa(row);
	if (num == NULL)
		return (ERROR);
	if (join_and_free(&s, "\033[", num, num))
		return (ERROR);
	if (join_and_free(&temp, s, "E\033[", s))
		return (ERROR);
	s = temp;
	num = ft_itoa(col);
	if (num == NULL)
	{
		free(s);
		return (ERROR);
	}
	if (join_and_free(&temp, s, num, num))
		return (ERROR);
	free(s);
	if (join_and_free(&s, temp, "C\033[0K", temp))
		return (ERROR);
	ft_putstr_fd(s, 1);
	free(s);
	return (SUCCESS);
}

void	delete_signal(void)
{
	int		col;
	int		row;
	int		flag;
	char	*s;

	s = NULL;
	col = get_window_size();
	if (col == -1)
		return ;
	get_cursol_point(&col, &row, &flag);
	if (flag == 1)
	{
		make_delete_sentence(0, row + 1, s);
		make_delete_sentence(col, row, s);
	}
	else
		make_delete_sentence(col, row, s);
	// ft_putstr_fd("\033[", 1);
	// ft_putnbr_fd(row, 1);
	// ft_putstr_fd("E\033[", 1);
	// ft_putnbr_fd(col, 1);
	// ft_putstr_fd("C\033[0K", 1);
	// printf("\033[%dE\033[%dC\033[0K", row, col);
}
