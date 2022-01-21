/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/21 18:17:26 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"

static void	redir_s_left(char *file)
{
	(void)file;
}

static void	redir_d_left(char *file)
{
	(void)file;
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

static void	redir_d_right(char *file)
{
	(void)file;
}

void	exec_redir(t_redir *redir)
{
	while (redir)
	{
		if (redir->type == S_LEFT)
			redir_s_left(redir->file);
		else if (redir->type == D_LEFT)
			redir_d_left(redir->file);
		else if (redir->type == S_RIGHT)
			redir_s_right(redir->file);
		else if (redir->type == D_RIGHT)
			redir_d_right(redir->file);
		redir = redir->next;
	}
}
