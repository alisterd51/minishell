/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <anclarma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 12:45:24 by anclarma          #+#    #+#             */
/*   Updated: 2021/11/19 20:01:36 by anclarma         ###   ########.fr       */
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
