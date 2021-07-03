/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command2tree1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:39:25 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/25 20:46:11 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*parse_command_init(t_tree **root)
{
	if (*root == NULL)
	{
		if (tree_init(root, 0))
			return (NULL);
		return ((*root)->command);
	}
	if ((*root)->command->flag == PIPE)
	{
		if (tree_add(*root, 0, TRUE))
			return (NULL);
		return ((*root)->right->command);
	}
	return (NULL);
}

static int	parse_command(t_tree **root, char **split, int *id)
{
	int			flag;
	t_command	*com;

	if (ft_strcmp(split[*id], "|") == 0)
		return (ERROR_TOKEN_PIPE);
	com = parse_command_init(root);
	if (com == NULL)
		return (ERROR);
	flag = read_command(split, com, id);
	if (flag == 0 && split[*id] && ft_strcmp(split[*id], "|") == 0)
	{
		if (tree_add_parent(root, PIPE, FALSE))
			flag = ERROR;
		if (flag == 0 && split[++*id] == NULL)
			flag = ERROR_MULTILINE;
		if (flag == 0 && ft_strcmp(split[*id], ";") == 0)
			flag = ERROR_TOKEN_COLON;
	}
	return (flag);
}

static int	parse_pipe(t_tree **root, char **split, int *index)
{
	int		flag;
	t_tree	*tree;

	tree = NULL;
	if (ft_strcmp(split[*index], ";") == 0)
		return (ERROR_TOKEN_COLON);
	flag = parse_command(&tree, split, index);
	while (flag == 0 && split[*index] && ft_strcmp(split[*index], ";") != 0)
		flag = parse_command(&tree, split, index);
	if (*root == NULL)
		*root = tree;
	else
		(*root)->right = tree;
	if (flag == 0 && split[*index])
	{
		if (tree_add_parent(root, SEMICOLON, FALSE))
			flag = ERROR;
		++*index;
	}
	return (flag);
}

int	read_command2tree(t_tree **root, char **split)
{
	int		i;
	int		flag;

	i = 0;
	*root = NULL;
	if (*split == NULL)
		return (SUCCESS);
	flag = parse_pipe(root, split, &i);
	while (flag == 0 && split[i])
		flag = parse_pipe(root, split, &i);
	if (flag)
		tree_free(root);
	return (flag);
}
