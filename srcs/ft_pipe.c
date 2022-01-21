/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/21 00:13:41 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "builtin.h"

static void	intern_child(t_intern_pipe *intern_pipe)
{
	close(intern_pipe->fd[0]);
	dup2(intern_pipe->fd[1], STDOUT_FILENO);
	exec_ast(intern_pipe->ast->paw1, intern_pipe->lst_env, intern_pipe->status);
	close(intern_pipe->fd[1]);
	close(STDOUT_FILENO);
}

static void	intern_parent(t_intern_pipe *intern_pipe)
{
	close(intern_pipe->fd[1]);
	dup2(intern_pipe->fd[0], STDIN_FILENO);
	exec_ast(intern_pipe->ast->paw2, intern_pipe->lst_env, intern_pipe->status);
	close(intern_pipe->fd[0]);
	close(STDIN_FILENO);
	waitpid(intern_pipe->pid, intern_pipe->status, 0);
}

static void	exe_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	int				ret_pipe;
	t_intern_pipe	intern_pipe;

	intern_pipe.ast = ast;
	intern_pipe.lst_env = lst_env;
	intern_pipe.status = status;
	ret_pipe = pipe(intern_pipe.fd);
	if (ret_pipe == 0)
	{
		intern_pipe.pid = fork();
		if (intern_pipe.pid == 0)
			intern_child(&intern_pipe);
		else
			intern_parent(&intern_pipe);
		clean_colector();
		clean_env(intern_pipe.lst_env);
	}
	else
		perror("minishell");
	exit(*intern_pipe.status);
}

void	ft_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	exe_pipe(ast, lst_env, status);
}
