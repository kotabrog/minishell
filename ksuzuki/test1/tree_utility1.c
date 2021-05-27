/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utility1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:01:08 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/24 21:32:14 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tree_init(t_tree **tree, int flag)
{
	int	i;

	if (ft_malloc(tree, sizeof(t_tree), 1))
		return(ERROR);
	if (command_init(&((*tree)->command), flag))
	{
		ft_free(tree);
		return (ERROR);
	}
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	return (SUCCESS);
}

int	tree_free(t_tree **tree)
{
	if (tree == NULL || *tree == NULL)
		return (SUCCESS);
	if ((*tree)->left)
		tree_free(&((*tree)->left));
	if ((*tree)->right)
		tree_free(&((*tree)->right));
	// write(1, "no\n", 3);
	command_free(&((*tree)->command));
	// write(1, "ok\n", 3);
	ft_free(tree);
	return (SUCCESS);
}

int	tree_add(t_tree *tree, int flag, int is_right)
{
	t_tree	*new_tree;

	if (tree_init(&new_tree, flag))
		return (ERROR);
	if (is_right)
		tree->right = new_tree;
	else
		tree->left = new_tree;
	return (SUCCESS);
}

int	tree_add_parent(t_tree **tree, int flag, int is_right)
{
	t_tree	*new_tree;

	if (tree_init(&new_tree, flag))
		return (ERROR);
	if (is_right)
		new_tree->right = *tree;
	else
		new_tree->left = *tree;
	*tree = new_tree;
	return (SUCCESS);
}
