/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:01 by anclarma          #+#    #+#             */
/*   Updated: 2022/01/24 22:27:12 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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
		{
			t_list	*new_node;
			char	*new_content;

			new_content = ft_strdup(*av);
			new_node = ft_lstnew(new_content);
			if (new_content == NULL || new_node == NULL)
			{
				free(new_content);
				free(new_node);
				perror("minishell: export");
				return (1);
			}
			ft_lstadd_back(env, new_node);
		}
		av++;
	}
	return (0);
}
