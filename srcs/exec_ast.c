/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/21 02:58:20 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
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
	int		status;
	pid_t	pid;
	char	*test;

	test = ft_getenv("PATH=", *lst_env);
	cpath = solve_path(test, tab[0]);
	free(test);
	ret = 0;
	if (access(cpath, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			env = list_to_tab(*lst_env);
			ret = execve(cpath, tab, env);
			if (ret == -1)
				perror(tab[0]);
			clean_tab(&env);
			free(cpath);
			exit(ret);
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}
	else
		perror(tab[0]);
	free(cpath);
	return (ret);
}

int	exec_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		fd_save;

	fd_save = dup(1);
	exec_redir(ast->paw2);
	tab = arg_to_tab(ast->paw1);
	ret = 0;
	if (tab && tab[0] && is_builtin(tab[0]))
		ret = exec_builtin(tab, lst_env);
	else if (tab && tab[0])
		ret = exec_arg_1(tab, lst_env);
	dup2(fd_save, 1);
	clean_tab(&tab);
	return (ret);
}

void	exec_ast(t_ast *ast, t_list **lst_env, int *status)
{
	pid_t	pid;
	t_arg	*test;

	if (ast == NULL)
		return ;
	test = ast->paw1;
	if (ast->type == COMMAND && is_builtin(test->arg))
		*status = exec_arg(ast, lst_env);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (ast->type == PIPELINE)
				ft_pipe(ast, lst_env, status);
			else if (ast->type == COMMAND)
				*status = exec_arg(ast, lst_env);
			exit(*status);
		}
		else
			waitpid(pid, status, 0);
	}
}
