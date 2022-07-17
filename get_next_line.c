/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 18:47:13 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/17 22:14:39 by lkurdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*new_line(char *src)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (!src[i])
	{
		free(src);
		return (NULL);
	}
	dest = ft_calloc((ft_strlen(src) - i + 1), sizeof(char));
	if (!dest)
		return (NULL);
	i++;
	while (src[i])
		dest[j++] = src[i++];
	free(src);
	return (dest);
}

static char	*ft_strjoiny(char *s1, char *s2)
{
	char	*c;
	int		i;
	int		y;

	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	c = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!c)
		return (free(s1), NULL);
	i = 0;
	y = 0;
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[y])
		c[i++] = s2[y++];
	c[i] = '\0';
	free(s1);
	return (c);
}

static char	*ft_strdup(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	dest = ft_calloc(i + 2, sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		dest[i++] = '\n';
	return (dest);
}

static char	*remp(int fd, char *buffer, char *line)
{
	int	rd;
	int	size;

	size = 4;
	rd = 1;
	if (!line)
		line = calloc(1, 1);
	while (rd > 0)
	{
		rd = read(fd, buffer, size);
		if (rd < 0)
		{
			free(line);
			return (free(buffer), NULL);
		}
		if (rd == 0 && !ft_strlen(line))
			return (free(line), free(buffer), NULL);
		buffer[rd] = 0;
		line = ft_strjoiny(line, buffer);
		if (ft_strcmp(buffer, '\n'))
			break ;
	}
	return (free(buffer), line);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*line;
	char		*dest;
	int			size;

	size = 4;
	if (fd < 0 || size <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(size + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	line = remp(fd, buffer, line);
	if (!line)
		return (NULL);
	dest = ft_strdup(line);
	line = new_line(line);
	return (dest);
}
/*
#include <fcntl.h>
int main()
{
int i = 0;
int fd ;
char *line;
fd = open("test.txt", O_RDONLY);
while (i < 8)
{
	line = get_next_line(fd);
    printf("%d = %s", i, line);
    i++;
    free(line);
}
return (0);
}*/
