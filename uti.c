/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkurdy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 00:25:46 by lkurdy            #+#    #+#             */
/*   Updated: 2022/07/18 00:25:47 by lkurdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	file(int *f1, char **argv, int argc, int *i)
{
	int	f2;

	if (!ft_strncmp(argv[1], "here_doc", 100))
	{
		if (argc > 6)
			return (write(2, "Invalid number of arguments\n", 28));
		*f1 = here(argv[2]);
		if (f1 < 0)
		{
			unlink(".tmp");
			perror("here_doc ");
		}
		f2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
		*i = *i + 1;
	}
	else
	{
		*f1 = open(argv[1], O_RDONLY);
		f2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	}
	return (f2);
}
