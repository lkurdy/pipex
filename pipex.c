/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:15:24 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/17 22:15:26 by lkurdy           ###   ########.fr       */
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
	ft_free(o, i);
	ft_free(paths, j);
	perror("Error: command not found");
}

pid_t	pipex(int f1, char **argv, char **envp)
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
			exe(argv[2], envp);
	}
	return (process);
}

int	main(int argc, char **argv, char **envp)
{
	int		f1;
	int		f2;
	pid_t	process;

	if (argc != 5)
		return (write(2, "Invalid number of arguments\n", 28));
	f1 = open(argv[1], O_RDONLY);
	f2 = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (f1 < 0 || f2 < 0)
		return (0);
	dup2(f1, STDIN_FILENO);
	dup2(f2, STDOUT_FILENO);
	process = pipex(f1, argv, envp);
	if (process)
		exe(argv[3], envp);
	return (0);
}
