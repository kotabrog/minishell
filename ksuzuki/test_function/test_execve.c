/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 21:33:50 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/06/07 21:55:53 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	size_t	i;

	ret = malloc(ft_strlen(s) + 1);
	if (!ret)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*ret;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

static int	count_str(char *s, char c)
{
	int		i;
	int		flag;
	int		count;

	i = 0;
	flag = 0;
	count = 0;
	while (s[i])
	{
		if (flag == 1 && s[i] == c)
			flag = 0;
		if (flag == 0 && s[i] != c)
		{
			flag = 1;
			count++;
		}
		i++;
	}
	return (count);
}

static char	**mem_free(char **ret, int index)
{
	while (index >= 0)
	{
		free(ret[index]);
		index--;
	}
	free(ret);
	return (NULL);
}

static int	sep_strlen(char *str, int index, char c)
{
	int		len;

	len = 0;
	while (str[index] != c && str[index])
	{
		len++;
		index++;
	}
	return (len);
}

static char	**create_str(char *s, char c, char **ret)
{
	int		len;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			len = sep_strlen((char *)s, i, c);
			ret[k] = malloc(sizeof(char) * (len + 1));
			if (!ret[k])
				return (mem_free(ret, k - 1));
			j = 0;
			while (j < len)
				ret[k][j++] = s[i++];
			ret[k++][j] = '\0';
		}
		else
			i++;
	}
	ret[k] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	if (!s)
		return (NULL);
	ret = malloc(sizeof(char *) * (count_str((char *)s, c) + 1));
	if (!ret)
		return (NULL);
	create_str((char *)s, c, ret);
	return (ret);
}

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
	char **path_list = NULL;
	char *temp_path;
	struct stat sb;
	pid_t pid;
	int status;

	while (*temp)
	{
		if (ft_strncmp("PATH=", *temp, 5) == 0)
			path = &((*temp)[5]);
		temp++;
	}
	if (!path)
		return (0);
	path_list = ft_split(path, ':');
	if (!path_list)
		return (0);
	if (argv[1][0] == '.' || argv[1][0] == '/')
	{
		new_argv[0] = argv[1];
		execve(new_argv[0], &new_argv[0], envp);
	}
	else
	{
		path = ft_strjoin("/", argv[1]);
		if (!path)
			return (1);
		while (*path_list)
		{
			temp_path = ft_strjoin(*path_list, path);
			if (!temp_path)
				return (1);
			++path_list;
			if (stat(temp_path, &sb) == -1)
				continue ;
			new_argv[0] = temp_path;
			execve(new_argv[0], &new_argv[0], envp);
			printf("error: %d, %s\n", errno, new_argv[0]);
		}
	}
	
	printf("error\n");
	// execve(new_argv[0], &new_argv[0], envp);

	printf("end\n");
}