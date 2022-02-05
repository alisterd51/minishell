/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:26:01 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/05 06:46:17 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "builtin.h"

static int	is_special_param(char *param)
{
	return (*param == '*' || *param == '@' || *param == '#' || *param == '?'
		|| *param == '-' || *param == '$' || *param == '!' || *param == '='
		|| ft_isdigit(*param));
}

static int	is_valid_export(char *param)
{
	size_t	i;

	i = 0;
	while (param[i] && param[i] != '=')
		i++;
	if (param[i] == '=')
		return (1);
	return (0);
}

static void	set_key_value(char *str, t_list **env)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = ft_strndup(str, i + 1);
	if (key == NULL)
	{
		perror("ft_export");
		return ;
	}
	value = ft_strdup(str + i + 1);
	if (key == NULL)
	{
		free(key);
		perror("ft_export");
		return ;
	}
	ft_setenv(key, value, env);
	free(key);
	free(value);
}

int	ft_export(int ac, char **av, t_list **env, int *fd)
{
	ac--;
	av++;
	if (ac == 0)
	{
		ft_env(*env, fd);
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
		else if (is_valid_export(*av))
			set_key_value(*av, env);
		av++;
	}
	return (0);
}
