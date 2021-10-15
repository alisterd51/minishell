/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:04:52 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/15 13:02:40 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

#define OUTPUT_END	0
#define INPUT_END	1

static int	ft_pipe1(int *fd, t_ast *ast, char **env)
{
	close(fd[INPUT_END]);
	dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[OUTPUT_END]);
	return (exec_ast(ast->paw2, env));
}

static int	ft_pipe2(int *fd, t_ast *ast, char **env)
{
	close(fd[OUTPUT_END]);
	dup2(fd[INPUT_END], STDIN_FILENO);
	close(fd[INPUT_END]);
	return (exec_ast(ast->paw1, env));
}

int	ft_pipe(t_ast *ast, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		ret;

	pipe(fd);
	pid1 = fork();
	ret = 0;
	if (pid1 == 0)
		ret = ft_pipe1(fd, ast, env);
	else
	{
		pid2 = fork();
		if (pid2 == 0)
			ret = ft_pipe2(fd, ast, env);
		close(fd[OUTPUT_END]);
		close(fd[INPUT_END]);
		waitpid(-1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
	return (ret);
}
