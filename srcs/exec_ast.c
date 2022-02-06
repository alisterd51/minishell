/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 03:38:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "minishell.h"

int	exec_arg(t_ast *ast, t_list **lst_env)
{
	char	**tab;
	int		ret;
	int		fd_save[2];

	fd_save[0] = 0;
	fd_save[1] = 1;
	if (exec_redir(ast->paw2, fd_save) != 0)
		return (-1);
	ret = ft_get_status();
	tab = arg_to_tab(ast->paw1);
	if (tab == NULL)
		perror("minishell: exec_arg");
	if (tab && tab[0] && is_builtin(tab[0]))
		ret = exec_builtin(tab, lst_env, fd_save);
	else if (tab && tab[0])
		ret = exec_arg_1(tab, lst_env, fd_save);
	if (fd_save[0] != 0)
		close(fd_save[0]);
	if (fd_save[1] != 1)
		close(fd_save[1]);
	clean_tab(&tab);
	return (ret);
}

static void	exec_ast_in_pipe(t_ast *ast, t_list **lst_env, int *status)
{
	if (ast->type == PIPELINE)
		ft_pipe(ast, lst_env, status);
	else if (ast->type == COMMAND)
		*status = exec_arg(ast, lst_env);
	clean_env(lst_env);
	clean_colector();
	clean_heredoc(2);
	exit(*status);
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
			exec_ast_in_pipe(ast, lst_env, status);
		else
			waitpid(pid, status, 0);
	}
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
}
