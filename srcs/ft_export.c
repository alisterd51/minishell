/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:01 by anclarma          #+#    #+#             */
/*   Updated: 2021/09/26 14:40:38 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_export(int ac, char **av, t_list **env)
{
	if (ac == 0)
	{
		ft_env(*env);
		return (0);
	}
	while (*av)
	{
		ft_lstadd_back(env, ft_lstnew(ft_strdup(*av)));
		av++;
	}
	return (0);
}
