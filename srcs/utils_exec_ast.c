/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 03:31:07 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/06 03:43:39 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"

char	*sub_solve_path(char **tab, t_list **lst_env)
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

int	calc_status(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (status == 2)
	{
		ft_putchar_fd('\n', 1);
		status = 130;
	}
	return (status);
}
