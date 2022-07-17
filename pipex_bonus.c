/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:09:00 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/17 22:19:17 by lkurdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**ft_parse(char **envp)
{
	char	*s;
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		exit(0);
	s = &envp[i][5];
	paths = ft_splity(s, ':');
	return (paths);
}

void	exe(char *cmd, char **envp)
{
	char	**paths;
	char	**o;
	int		j;
	int		i;
	char	*bin;

	j = 0;
	i = 0;
	o = ft_split(cmd, ' ');
	while (o[i])
		i++;
	paths = ft_parse(envp);
	while (paths[j])
	{
		bin = ft_strjoin(paths[j], o[0]);
		if (!bin)
			break ;
		execve(bin, o, envp);
		free(bin);
		j++;
	}
	ft_free(paths, j);
	ft_free(o, i);
	perror("Error: command not found");
}

pid_t	pipex(int f1, char *argv, char **envp)
{
	pid_t	process;
	int		fd[2];

	pipe(fd);
	process = fork();
	if (process < 0)
		return (perror("Fork :"), process);
	if (process)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(process, NULL, 0);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		if (f1 == STDIN_FILENO)
			exit(1);
		else
			exe(argv, envp);
	}
	return (process);
}

int	here(char *stp)
{
	int		fd;
	char	*buf;

	fd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		return (0);
	while (1)
	{
		write(1, "here_doc> ", 10);
		buf = get_next_line(0);
		if (!buf)
			exit(1);
		if (!ft_strncmp(stp, buf, ft_strlen(stp)))
			break ;
		write(fd, buf, ft_strlen(buf));
		free(buf);
	}
	free(buf);
	close(fd);
	return (open(".tmp", O_RDONLY));
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	int		i;
	pid_t	process;

	i = 3;
	if (argc < 5)
		return (write(2, "Invalid number of arguments\n", 28));
	f2 = file(&f1, argv, argc, &i);
	if (f1 < 0 || f2 < 0)
		return (0);
	dup2(f1, 0);
	dup2(f2, 1);
	process = pipex(f1, argv[i - 1], envp);
	while (i < argc - 2 && process)
	{
		process = pipex(1, argv[i], envp);
		i++;
	}
	if (process)
		exe(argv[i], envp);
	return (0);
}
