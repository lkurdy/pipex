/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 22:12:30 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/27 14:42:11 by lkurdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len);
char	**ft_split(const char *s, char c);
char	**ft_free(char **dest);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_splity(const char *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(char *s);
char	*get_next_line(int fd);
int		file(int *f1, char **argv, int argc, int *i);
int		here(char *stp);
int		op(int f2, char **argv);
void	op2(pid_t process, int i, char **envp, char **argv);
void	exe(char *cmd, char **envp);

#endif
