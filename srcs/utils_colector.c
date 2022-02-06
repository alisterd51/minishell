/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 22:50:52 by antoine           #+#    #+#             */
/*   Updated: 2022/02/06 03:58:15 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"

void	close_fd(void *ptr)
{
	int	*fd;

	fd = (int *)ptr;
	close(*fd);
	free(fd);
}

int	*new_int(int i)
{
	int	*ret;

	ret = (int *)malloc(sizeof(int) * 1);
	if (ret == NULL)
		return (NULL);
	ret[0] = i;
	return (ret);
}
