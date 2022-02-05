/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 00:10:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"

static int	redir_s_left(char *file, int *fd_save)
{
	int	new_fd;

	new_fd = open(file, O_RDONLY);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	fd_save[0] = new_fd;
	return (0);
}

static int	redir_d_left(char *file, int *fd_save)
{
	int	fd;

	if (file == NULL)
		return (-1);
	fd = ft_atoi(file);
	to_fd_colector(fd);
	fd_save[0] = fd;
	return (0);
}

static int	redir_s_right(char *file, int *fd_save)
{
	int	new_fd;

	new_fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	fd_save[1] = new_fd;
	return (0);
}

static int	redir_d_right(char *file, int *fd_save)
{
	int		new_fd;

	new_fd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0666);
	if (new_fd == -1)
	{
		perror(file);
		return (-1);
	}
	fd_save[1] = new_fd;
	return (0);
}

int	exec_redir(t_redir *redir, int *fd_save)
{
	int	ret;

	ret = 0;
	while (redir)
	{
		if (redir->type == S_LEFT)
			ret = redir_s_left(redir->file, fd_save);
		else if (redir->type == D_LEFT || redir->type == D_LEFT_EXP)
			ret = redir_d_left(redir->file, fd_save);
		else if (redir->type == S_RIGHT)
			ret = redir_s_right(redir->file, fd_save);
		else if (redir->type == D_RIGHT)
			ret = redir_d_right(redir->file, fd_save);
		if (ret != 0)
			return (-1);
		redir = redir->next;
	}
	return (0);
}
