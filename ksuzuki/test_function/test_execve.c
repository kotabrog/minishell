/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:33:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/07 18:15:13 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	cs1 = (const unsigned char *)s1;
	cs2 = (const unsigned char *)s2;
	i = 0;
	while (i < n && cs1[i] != '\0' && cs2[i] != '\0')
	{
		if (cs1[i] != cs2[i])
			return (cs1[i] - cs2[i]);
		i++;
	}
	if (i != n && cs1[i] && !cs2[i])
		return (cs1[i]);
	if (i != n && !cs1[i] && cs2[i])
		return (-cs2[i]);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char *new_argv[] = {"/bin/ls", 0};
	char **temp = envp;
	char *path = NULL;

	while (*temp)
	{
		if (ft_strncmp("PATH", *temp, 4) == 0)
			path = &((*temp)[5]);
		temp++;
	}
	if (!path)
		return (0);

	printf("%s\n", path);
	execve(new_argv[0], &new_argv[0], envp);

	printf("end\n");
}