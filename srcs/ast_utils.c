/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:38:08 by anclarma          #+#    #+#             */
/*   Updated: 2021/10/12 17:01:14 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static int	argsize(t_arg *arg)
{
	int	ret;

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
	int		size;
	int		i;

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

void	clean_tab(t_arg ***arg)
{
	int	i;

	i = 0;
	while ((*arg)[i])
	{
		free((*arg)[i]);
		(*arg)[i] = NULL;
		i++;
	}
	free(*arg);
	*arg = NULL;
}
