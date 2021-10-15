/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/15 15:13:18 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <unistd.h>
#include "minishell.h"

static int	exec_arg(t_arg *arg, char **env)
{
	char	**tab;
	int		ret;
	pid_t	pid;

	pid = fork();
	ret = 0;
	if (pid == 0)
	{
		tab = arg_to_tab(arg);
		if (tab)
			ret = execve(*tab, tab, env);
		clean_tab(&tab);
	}
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
