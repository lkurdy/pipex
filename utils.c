/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:15:57 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/27 14:41:12 by lkurdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (little[j] == big[i + j] && big[i + j]
			&& little[j] && i + j < len)
			j++;
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*c;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[y])
		y++;
	c = malloc(sizeof(char) * (i + y + 1));
	if (!c)
		return (NULL);
	i = 0;
	y = 0;
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[y])
		c[i++] = s2[y++];
	return (c[i] = '\0', c);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	op(int f2, char **argv)
{
	f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (f2 < 0)
		return (-1);
	dup2(f2, STDOUT_FILENO);
	return (f2);
}

void	op2(pid_t process, int i, char **envp, char **argv)
{
	if (process)
	{
		process = fork();
		if (!process)
			exe(argv[i], envp);
	}
}
