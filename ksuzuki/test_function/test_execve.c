/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:33:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/05/28 21:43:50 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	char *new_argv[] = {"/bin/l", 0};
	char *envp[] = {0};

	execve(new_argv[0], &new_argv[0], envp);

	printf("end\n");
}