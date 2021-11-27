/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:01 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/27 02:01:17 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_special_param(char *param)
{
	return (*param == '*' || *param == '*' || *param == '@' || *param == '#'
		|| *param == '?' || *param == '-' || *param == '$' || *param == '!'
		|| ft_isdigit(*param));
}

int	ft_export(int ac, char **av, t_list **env)
{
	if (ac == 0)
	{
		ft_env(*env);
		return (0);
	}
	while (*av)
	{
		if (is_special_param(*av))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*av, 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		else
			ft_lstadd_back(env, ft_lstnew(ft_strdup(*av)));
		av++;
	}
	return (0);
}
