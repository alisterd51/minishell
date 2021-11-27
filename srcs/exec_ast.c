/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/27 00:58:59 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "builtin.h"

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

static int	exec_builtin(char **tab, t_list **lst_env)
{
	if (!ft_strcmp(*tab, "echo"))
		return (ft_echo(tablen(tab), tab));
	else if (!ft_strcmp(*tab, "cd"))
		return (ft_cd(tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "pwd"))
		return (ft_pwd(tablen(tab), tab));
	else if (!ft_strcmp(*tab, "export"))
		return (ft_export(tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "unset"))
		return (ft_unset(tablen(tab), tab, lst_env));
	else if (!ft_strcmp(*tab, "env"))
		return (ft_env(*lst_env));
	else if (!ft_strcmp(*tab, "exit"))
		return (ft_exit(tablen(tab), tab, ft_get_status()));
	return (0);
}

static int	exec_arg_1(char **tab, t_list **lst_env)
{
	char	**env;
	char	*cpath;
	int		ret;

	cpath = solve_path(getenv("PATH"), tab[0]);
	env = list_to_tab(*lst_env);
	ret = execve(cpath, tab, env);
	clean_tab(&env);
	free(cpath);
	return (ret);
}

static int	exec_arg(t_arg *arg, t_list **lst_env)
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
				ret = exec_builtin(tab, lst_env);
			else
				ret = exec_arg_1(tab, lst_env);
		}
		clean_tab(&tab);
	}
	wait(&status);
	return (ret);
}

int	exec_ast(t_ast *ast, t_list **lst_env)
{
	int	ret;

	if (ast == NULL)
		return (0);
	if (ast->type == PIPELINE)
		ret = ft_pipe(ast, lst_env);
	else
		ret = exec_arg(ast->paw1, lst_env);
	return (ret);
}
