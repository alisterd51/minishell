/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/04 02:22:38 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

static void	exec_arg_2(char **tab, t_list **lst_env, char *cpath, int *fd_save)
{
	char	**env;
	int		ret;

	env = list_to_tab(*lst_env);
	ret = execve(cpath, tab, env);
	if (ret == -1)
		perror(tab[0]);
	clean_env(lst_env);
	clean_tab(&env);
	clean_tab(&tab);
	free(cpath);
	clean_colector();
	(void)fd_save;
	exit(ret);
}

static char	*sub_solve_path(char **tab, t_list **lst_env)
{
	char	*cpath;
	char	*path_value;

	path_value = ft_getenv("PATH=", *lst_env);
	cpath = solve_path(path_value, tab[0]);
	free(path_value);
	if (cpath == NULL)
		perror("minishell: solve_path");
	return (cpath);
}

static int	exec_arg_1(char **tab, t_list **lst_env, int *fd_save)
{
	char	*cpath;
	int		ret;
	int		status;
	pid_t	pid;

	cpath = sub_solve_path(tab, lst_env);
	if (cpath == NULL)
		return (-1);
	ret = 0;
	if (access(cpath, X_OK) == 0)
	{
		pid = fork();
		if (pid == 0)
			exec_arg_2(tab, lst_env, cpath, fd_save);
		else
			waitpid(pid, &status, 0);
	}
	else
		perror(tab[0]);
	free(cpath);
	clean_colector();
	return (ret);
}

int	exec_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		fd_save[2];

	fd_save[0] = dup(0);
	fd_save[1] = dup(1);
	if (exec_redir(ast->paw2) != 0)
		return (1);
	tab = arg_to_tab(ast->paw1);
	if (tab == NULL)
		perror("minishell: exec_arg");
	ret = 0;
	if (tab && tab[0] && is_builtin(tab[0]))
		ret = exec_builtin(tab, lst_env);
	else if (tab && tab[0])
		ret = exec_arg_1(tab, lst_env, fd_save);
	unlink("/tmp/.heredoc");
	dup2(fd_save[0], 0);
	dup2(fd_save[1], 1);
	close(fd_save[0]);
	close(fd_save[1]);
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
	if (ast->type == COMMAND && test && test->arg && is_builtin(test->arg))
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
			clean_env(lst_env);
			clean_colector();
			exit(*status);
		}
		else
			waitpid(pid, status, 0);
	}
}
