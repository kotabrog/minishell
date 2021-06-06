// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   variable_expansion.c                               :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2021/06/05 16:08:07 by ksuzuki           #+#    #+#             */
// /*   Updated: 2021/06/05 17:06:16 by ksuzuki          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "minishell.h"

// static int	expansion_one(char *target, char ***dst, int status, char **env)
// {
	
// }

// static int	multi_to_single(char ***target, char ***dst, int file_flag)
// {
	
// }

// static int	expansion_all(char ***target, int file_flag, int status, char **env)
// {
// 	char	***dst;
// 	int		flag;
// 	int		target_len;
// 	int		i;

// 	flag = SUCCESS;
// 	target_len = ft_strlen_ex(*target);
// 	if (target_len == 0)
// 		return (SUCCESS);
// 	if (ft_malloc(&dst, sizeof(char **), target_len))
// 		return (errno);
// 	i = 0;
// 	while (flag == SUCCESS && (*target)[i])
// 	{
// 		flag = expansion_one((*target)[i], &(dst[i]), status, env);
// 		++i;
// 	}
// 	if (flag)
// 		ft_free_triple_char(&dst);
// 	if (flag == SUCCESS)
// 		flag = multi_to_single(target, dst, file_flag);
// 	return (flag);
// }

// int	variable_expansion(t_status *status, t_command *com)
// {
// 	int	flag;

// 	flag = expansion_all(&(com->file), TRUE, status->exit, status->env);
// 	if (flag)
// 		return (status_value_conversion(flag));
// 	flag = expansion_all(&(com->s), FALSE, status->exit, status->env);
// 	return (status_value_conversion(flag));
// }
