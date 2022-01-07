/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/07 16:49:09 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "builtin.h"

static void	exe_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec_ast(ast->paw1, lst_env, status);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		exec_ast(ast->paw2, lst_env, status);
		close(fd[0]);
		waitpid(pid, status, 0);
	}
	exit(*status);
}

void	ft_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exe_pipe(ast, lst_env, status);
	else
		waitpid(pid, status, 0);
}
