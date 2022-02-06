/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_exec_ast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 03:40:55 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "minishell.h"

static void	exec_arg_3(char **tab, t_list **lst_env, char *cpath, int *fd_save)
{
	char	**env;
	int		ret;

	dup2(fd_save[0], STDIN_FILENO);
	dup2(fd_save[1], STDOUT_FILENO);
	env = list_to_tab(*lst_env);
	ret = execve(cpath, tab, env);
	if (ret == -1)
		perror(tab[0]);
	clean_env(lst_env);
	clean_tab(&env);
	clean_tab(&tab);
	free(cpath);
	clean_colector();
	clean_heredoc(2);
	exit(ret);
}

static int	exec_arg_2(char **tab, t_list **lst_env, char *cpath, int *fd_save)
{
	int		status;
	pid_t	pid;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exec_arg_3(tab, lst_env, cpath, fd_save);
	}
	else
		waitpid(pid, &status, 0);
	signal(SIGINT, handler_int);
	signal(SIGQUIT, SIG_IGN);
	return (status);
}

int	exec_arg_1(char **tab, t_list **lst_env, int *fd_save)
{
	char	*cpath;
	int		status;

	cpath = sub_solve_path(tab, lst_env);
	if (cpath == NULL)
		return (-1);
	status = 0;
	if (access(cpath, X_OK) == 0)
		status = exec_arg_2(tab, lst_env, cpath, fd_save);
	else
	{
		ft_putstr_fd(tab[0], 2);
		ft_putendl_fd(": command not found", 2);
		status = 127;
	}
	free(cpath);
	clean_colector();
	return (calc_status(status));
}
