/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 11:53:33 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/02/20 23:54:29 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define True 1
# define READ_SIZE 1024
# define SUCCESS 0
# define ERROR 1

# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>

void	ft_strcpy(char *p, char const *s, size_t n);
char	**ft_split(char const *s, char c);



#endif
