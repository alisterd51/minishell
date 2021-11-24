/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:01 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/24 16:46:25 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_special_param(char *param)
{
	return (*param == '*'
			|| *param == '*'
			|| *param == '@'
			|| *param == '#'
			|| *param == '?'
			|| *param == '-'
			|| *param == '$'
			|| *param == '!'
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
			ft_putendl_fd("bash: export: `10=a': not a valid identifier", 2);//
		else
			ft_lstadd_back(env, ft_lstnew(ft_strdup(*av)));
		av++;
	}
	return (0);
}
