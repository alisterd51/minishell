/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:04:52 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/24 20:19:36 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

#define OUTPUT_END	0
#define INPUT_END	1

static int	ft_pipe1(int *fd, t_ast *ast, t_list **lst_env)
{
	close(fd[INPUT_END]);
	dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[OUTPUT_END]);
	return (exec_ast(ast->paw2, lst_env));
}

static int	ft_pipe2(int *fd, t_ast *ast, t_list **lst_env)
{
	close(fd[OUTPUT_END]);
	dup2(fd[INPUT_END], STDOUT_FILENO);
	close(fd[INPUT_END]);
	return (exec_ast(ast->paw1, lst_env));
}

int	ft_pipe(t_ast *ast, t_list **lst_env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		ret;

	pipe(fd);
	pid1 = fork();
	ret = 0;
	if (pid1 == 0)
		ret = ft_pipe1(fd, ast, lst_env);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			ret = ft_pipe2(fd, ast, lst_env);
		close(fd[OUTPUT_END]);
		close(fd[INPUT_END]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
	return (ret);
}
