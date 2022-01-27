/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/27 23:41:57 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	redir_s_left(char *file)
{
	int	new_fd;

	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (0);
}

//manque l'expend
static int	redir_d_left(char *file)
{
	int		fd;
	char	*line;

	fd = open(".heredoc", O_CREAT | O_WRONLY, 0666);
	line = NULL;
	while (get_next_line(STDIN_FILENO, &line) > 0 && ft_strcmp(file, line))
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close(fd);
	fd = open(".heredoc", O_RDONLY);
	if (fd == -1)
	{
		perror(".heredoc");
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

static int	redir_s_right(char *file)
{
	int	new_fd;

	new_fd = open(file, O_CREAT | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (0);
}

static int	redir_d_right(char *file)
{
	int		new_fd;

	new_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (0);
}

int	exec_redir(t_redir *redir)
{
	int	ret;

	ret = 0;
	while (redir)
	{
		if (redir->type == S_LEFT)
			ret = redir_s_left(redir->file);
		else if (redir->type == D_LEFT)
			ret = redir_d_left(redir->file);
		else if (redir->type == S_RIGHT)
			ret = redir_s_right(redir->file);
		else if (redir->type == D_RIGHT)
			ret = redir_d_right(redir->file);
		if (ret != 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
