/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/29 21:06:46 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

#include <stdio.h>

static int	is_builtin(char *path)
{
	return (!ft_strcmp(path, "echo")
		|| !ft_strcmp(path, "cd")
		|| !ft_strcmp(path, "pwd")
		|| !ft_strcmp(path, "export")
		|| !ft_strcmp(path, "unset")
		|| !ft_strcmp(path, "env")
		|| !ft_strcmp(path, "exit"));
}

static int	exec_builtin(char **tab, char **env)
{
	(void)tab;
	(void)env;
	printf("c'est un builtin\n");
	return (0);
}

static int	exec_arg(t_arg *arg, char **env)
{
	char	**tab;
	int		ret;
	int		status;
	pid_t	pid;

	pid = fork();
	ret = 0;
	if (pid == 0)
	{
		tab = arg_to_tab(arg);
		if (tab)
		{
			if (is_builtin(tab[0]))
				ret = exec_builtin(tab, env);
			else
				ret = execve(tab[0], tab, env);
		}
		clean_tab(&tab);
	}
	wait(&status);
	return (ret);
}

int	exec_ast(t_ast *ast, char **env)
{
	int	ret;

	if (ast == NULL)
		return (0);
	if (ast->type == PIPELINE)
		ret = ft_pipe(ast, env);
	else
		ret = exec_arg(ast->paw1, env);
	return (ret);
}
