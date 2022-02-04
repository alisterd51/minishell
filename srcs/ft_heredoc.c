/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 00:46:40 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/04 19:03:40 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <signal.h>
#include "minishell.h"

static int	read_heredoc(int fd, char const *terminat)
{
	char	*line;

	line = readline(DEFAULT_PS2);
	while (line && ft_strcmp(terminat, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(DEFAULT_PS2);
	}
	return (0);
}

int	fd_heredoc(char *file, int expend)
{
	int		fd;
	char	*heredoc;

	heredoc = new_heredoc();
	(void)expend;
	fd = open(heredoc, O_WRONLY | O_TRUNC);
	if (fd == -1)
	{
		perror(heredoc);
		return (-1);
	}
	signal(SIGINT, handler_int_heredoc);
	read_heredoc(fd, file);
	signal(SIGINT, handler_int);
	close(fd);
	fd = open(heredoc, O_RDONLY);
	if (fd == -1)
	{
		perror(heredoc);
		return (-1);
	}
	return (fd);
}
