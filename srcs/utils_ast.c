/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:45:24 by anclarma          #+#    #+#             */
/*   Updated: 2022/02/03 22:20:18 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static size_t	argsize(t_arg *arg)
{
	size_t	ret;

	ret = 0;
	while (arg)
	{
		ret++;
		arg = arg->next;
	}
	return (ret);
}

char	**arg_to_tab(t_arg *arg)
{
	char	**ret;
	size_t	size;
	size_t	i;

	size = argsize(arg);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ret[i] = ft_strdup(arg->arg);
		if (ret[i] == NULL)
		{
			clean_tab(&ret);
			return (NULL);
		}
		arg = arg->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int	tabsize(char **tab)
{
	int	size;

	size = 0;
	if (!tab)
		return (0);
	while (tab[size])
		size++;
	return (size);
}

int	is_redirect(int type)
{
	return (type == S_LEFT || type == S_RIGHT || type == D_LEFT
		|| type == D_RIGHT || type == D_LEFT_EXP);
}
