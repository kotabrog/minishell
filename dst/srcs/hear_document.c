/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hear_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 18:30:52 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/14 00:51:53 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	join_documenet(char **dst, char *s)
{
	char	*temp;
	temp = ft_strjoin(*dst, s);
	ft_free(dst);
	if (temp == NULL)
		return (ERROR);
	*dst = temp;
	temp = ft_strjoin(*dst, "\n");
	ft_free(dst);
	if (temp == NULL)
		return (ERROR);
	*dst = temp;
	return (SUCCESS);
}

static void	parse_end(char *end, int *fd)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (end[i])
	{
		if ((flag == SINGLE_QUOT && end[i] == '\'') || \
			(flag == DOUBLE_QUOT && end[i] == '"'))
			flag = 0;
		else if (flag == 0 && end[i] == '"')
			flag = DOUBLE_QUOT;
		else if (flag == 0 && end[i] == '\'')
		{
			flag = SINGLE_QUOT;
			*fd = HEARDOC_NON_EX;
		}
		else
			end[j++] = end[i];
		++i;
	}
	end[j] = 0;
}

static int	read_document(char **end, int flag, int *fd)
{
	int		end_flag;
	char	*s;
	char	*temp;

	end_flag = FALSE;
	temp = ft_strdup("");
	if (temp == NULL)
		return (ERROR);
	parse_end(*end, fd);
	while (!g_signal->signal_flag && !end_flag && !flag)
	{
		s = readline("> ");
		if (s == NULL || ft_strcmp(s, *end) == 0)
			end_flag = TRUE;
		else if (!g_signal->signal_flag)
			flag = join_documenet(&temp, s);
		free(s);
	}
	free(*end);
	*end = temp;
	if (g_signal->signal_flag)
		return (ERROR);
	return (flag);
}

static int	check_command(t_status *status, t_tree *tree, int flag)
{
	int	i;

	i = 0;
	while (!flag && tree->command->file[i])
	{
		if (tree->command->fd[i] == HEARDOC)
			flag = read_document(&(tree->command->file[i]), flag, \
				&(tree->command->fd[i]));
		++i;
	}
	if (flag)
	{
		while (tree->command->file[i])
			ft_free(&(tree->command->file[i++]));
		set_exit_status(status, flag);
	}
	return (flag);
}

int	hear_document(t_status *status, t_tree *tree, int flag)
{
	if (tree == NULL)
		return (flag);
	if (!flag && tree->left)
		flag = hear_document(status, tree->left, flag);
	if (!flag && tree->right)
		flag = hear_document(status, tree->right, flag);
	if (!flag && tree->command && tree->command->file)
		flag = check_command(status, tree, flag);
	return (flag);
}
