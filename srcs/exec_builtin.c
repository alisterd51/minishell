/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:13:41 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/29 00:24:41 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin.h"

int	exec_builtin(char **tab, t_list **lst_env)
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
